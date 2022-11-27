#pragma once

#include <memory>
#include <string>
#include <unordered_map>

class Model;
class Renderer;
class Texture;
class Sound;

class ResourceManager
{
public:
  ResourceManager(Renderer& renderer);
  ResourceManager(const ResourceManager&) = delete;
  ResourceManager(ResourceManager&&) = delete;
  ~ResourceManager();

  void Clear();

  const std::shared_ptr<Model>& GetModel(const std::string& texturePath);
  const std::shared_ptr<Texture>& GetTexture(const std::string& texturePath);
  const std::shared_ptr<Sound>& GetSound(const std::string& soundPath);

  void Purge();

  static ResourceManager& Instance();

  ResourceManager& operator=(const ResourceManager&) = delete;
  ResourceManager& operator=(ResourceManager&&) = delete;

private:
  std::shared_ptr<Model> m_missingModel;
  std::shared_ptr<Texture> m_missingTexture;

  std::unordered_map<std::string, std::shared_ptr<Model>> m_models;
  std::unordered_map<std::string, std::shared_ptr<Texture>> m_textures;
  std::unordered_map<std::string, std::shared_ptr<Sound>> _sounds;

  Renderer& m_renderer;

  static ResourceManager* s_instance;
};