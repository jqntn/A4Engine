#pragma once

#include <SDL.h>

#include <memory>
#include <string>
#include <vector>

class Renderer;
class Texture;
class Transform;

class Model
{
public:
  Model(const std::shared_ptr<Texture>& texture,
        const std::vector<int>& indices,
        const std::vector<SDL_Vertex>& vertices);

  Model() = default;

  Model(const Model&) = default;
  Model(Model&&) = default;
  Model& operator=(const Model&) = default;
  Model& operator=(Model&&) = default;
  ~Model() = default;

  static Model LoadFromFile(Renderer& renderer, const char* path);

  void Draw(Renderer& renderer);

private:
  std::shared_ptr<Texture> _texture;
  std::vector<int> _indices;
  std::vector<SDL_Vertex> _vertices;
};