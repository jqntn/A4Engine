#include <ResourceManager.h>

std::shared_ptr<Texture>
ResourceManager::GetTexture(Renderer& renderer, const char* path)
{
  if (!_textures.contains(path)) {
    auto tex = Texture::LoadFromFile(renderer, path);
    auto texPtr = std::make_shared<Texture>(std::move(tex));

    _textures.emplace(path, std::move(texPtr));
  }

  return _textures.at(path);
}

void
ResourceManager::Purge()
{
  for (const auto& [key, value] : _textures)
    if (value.use_count() <= 1)
      _textures.erase(key);
}