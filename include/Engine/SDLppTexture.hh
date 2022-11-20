#pragma once

#include <SDL.h>
#include <string>

class SDLppRenderer;
class SDLppSurface;

class SDLppTexture
{
public:
  SDLppTexture(const SDLppTexture&) = delete;
  SDLppTexture(SDLppTexture&& texture) noexcept;
  ~SDLppTexture();

  const std::string& GetFilepath() const;
  SDL_Texture* GetHandle() const;
  SDL_Rect GetRect() const;

  SDLppTexture& operator=(const SDLppTexture&) = delete;
  SDLppTexture& operator=(SDLppTexture&&) noexcept;

  static SDLppTexture LoadFromFile(SDLppRenderer& renderer,
                                   const std::string& filepath);
  static SDLppTexture LoadFromSurface(SDLppRenderer& renderer,
                                      const SDLppSurface& surface);

private:
  SDLppTexture(SDL_Texture* texture, std::string filepath = "");

  SDL_Texture* m_texture;
  std::string m_filepath;
};