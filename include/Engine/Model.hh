#pragma once

#include <Engine/Color.hh>

#include <Engine/Renderable.hh>
#include <Engine/Vector2.hh>
#include <SDL.h>
#include <filesystem>
#include <memory>
#include <nlohmann/json_fwd.hpp>
#include <vector>

class Renderer;
class Texture;
class Transform;

struct ModelVertex
{
  Vector2f pos;
  Vector2f uv;
  Color color;
};

class Model : public Renderable
{
public:
  Model() = default;
  Model(std::shared_ptr<const Texture> texture,
        std::vector<ModelVertex> vertices,
        std::vector<int> indices);
  Model(const Model&) = default;
  Model(Model&&) = default;
  ~Model() = default;

  void Draw(Renderer& renderer, const Matrix3f& matrix) override;

  const std::vector<ModelVertex>& GetVertices() const;

  bool IsValid() const;

  bool SaveToFile(const std::filesystem::path& filepath) const;
  nlohmann::ordered_json SaveToJSon() const;

  Model& operator=(const Model&) = delete;
  Model& operator=(Model&&) = default;

  static Model LoadFromFile(const std::filesystem::path& filepath);
  static Model LoadFromJSon(const nlohmann::json& doc);

private:
  bool SaveToFileRegular(const std::filesystem::path& filepath) const;
  bool SaveToFileCompressed(const std::filesystem::path& filepath) const;
  bool SaveToFileBinary(const std::filesystem::path& filepath) const;

  static Model LoadFromFileRegular(const std::filesystem::path& filepath);
  static Model LoadFromFileCompressed(const std::filesystem::path& filepath);
  static Model LoadFromFileBinary(const std::filesystem::path& filepath);

  std::shared_ptr<const Texture> m_texture;
  std::vector<ModelVertex> m_vertices;
  std::vector<SDL_Vertex> m_sdlVertices;
  std::vector<int> m_indices;
};