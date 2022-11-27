#pragma once

#include <SDL.h>
#include <string>

class Renderer;
class Surface;

class Texture
{
public:
  Texture(const Texture&) = delete;
  Texture(Texture&& texture) noexcept;
  ~Texture();

  const std::string& GetFilepath() const;
  SDL_Texture* GetHandle() const;
  SDL_Rect GetRect() const;

  Texture& operator=(const Texture&) = delete;
  Texture& operator=(Texture&&) noexcept;

  static Texture LoadFromFile(Renderer& renderer, const std::string& filepath);
  static Texture LoadFromSurface(Renderer& renderer, const Surface& surface);

private:
  Texture(SDL_Texture* texture, std::string filepath = "");

  SDL_Texture* m_texture;
  std::string m_filepath;
};