#pragma once

#include <Texture.h>

#include <memory>
#include <unordered_map>

class ResourceManager
{
public:
  static ResourceManager& Inst()
  {
    static ResourceManager inst;
    return inst;
  }

  std::shared_ptr<Texture> GetTexture(Renderer& renderer, const char* path);

private:
  ResourceManager() = default;
  ~ResourceManager() = default;

  ResourceManager(const ResourceManager&) = delete;
  ResourceManager(ResourceManager&&) = delete;
  ResourceManager& operator=(const ResourceManager&) = delete;
  ResourceManager& operator=(ResourceManager&&) = delete;

  void Purge();

  std::unordered_map<const char*, std::shared_ptr<Texture>> _textures;
};