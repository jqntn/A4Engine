#pragma once

#include <SDL.h>
#include <string_view>

class Texture;
class Window;

class Renderer
{
public:
  Renderer(Window& window,
           std::string_view rendererName = "",
           Uint32 flags = 0);
  Renderer(const Renderer&) = delete;
  Renderer(Renderer&& renderer) noexcept;
  ~Renderer();

  void Clear();

  void DrawLines(const SDL_FPoint* points, std::size_t count);
  void DrawTriangles(const SDL_Vertex* vertices, std::size_t count);
  void DrawTriangles(const SDL_Vertex* vertices,
                     std::size_t vertCount,
                     int* indices,
                     std::size_t indexCount);
  void DrawTriangles(const Texture& texture,
                     const SDL_Vertex* vertices,
                     std::size_t count);
  void DrawTriangles(const Texture& texture,
                     const SDL_Vertex* vertices,
                     std::size_t vertCount,
                     int* indices,
                     std::size_t indexCount);

  SDL_Renderer* GetHandle() const;

  void Present();

  void RenderCopy(const Texture& texture);
  void RenderCopy(const Texture& texture, const SDL_Rect& dst);
  void RenderCopy(const Texture& texture,
                  const SDL_Rect& src,
                  const SDL_Rect& dst);

  void SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

  Renderer& operator=(const Renderer&) = delete;
  Renderer& operator=(Renderer&&) noexcept;

private:
  SDL_Renderer* m_renderer;
};