#include <Engine/Renderer.hh>
#include <Engine/Texture.hh>
#include <Engine/Window.hh>
#include <SDL.h>

Renderer::Renderer(Window& window, std::string_view rendererName, Uint32 flags)
{
  int choosenDriver = -1;

  int numDrivers = SDL_GetNumRenderDrivers();
  for (int i = 0; i < numDrivers; ++i) {
    SDL_RendererInfo info;
    SDL_GetRenderDriverInfo(i, &info);

    if (info.name == rendererName)
      choosenDriver = i;
  }

  m_renderer = SDL_CreateRenderer(window.GetHandle(), choosenDriver, flags);
}

Renderer::Renderer(Renderer&& renderer) noexcept
{
  m_renderer = renderer.m_renderer;
  renderer.m_renderer = nullptr;
}

Renderer::~Renderer()
{
  SDL_DestroyRenderer(m_renderer);
}

void
Renderer::Clear()
{
  SDL_RenderClear(m_renderer);
}

void
Renderer::DrawLines(const SDL_FPoint* points, std::size_t count)
{
  SDL_RenderDrawLinesF(m_renderer, points, static_cast<int>(count));
}

void
Renderer::DrawTriangles(const SDL_Vertex* vertices, std::size_t count)
{
  SDL_RenderGeometry(
    m_renderer, nullptr, vertices, static_cast<int>(count), nullptr, 0);
}

void
Renderer::DrawTriangles(const SDL_Vertex* vertices,
                        std::size_t vertCount,
                        int* indices,
                        std::size_t indexCount)
{
  SDL_RenderGeometry(m_renderer,
                     nullptr,
                     vertices,
                     static_cast<int>(vertCount),
                     indices,
                     static_cast<int>(indexCount));
}

void
Renderer::DrawTriangles(const Texture& texture,
                        const SDL_Vertex* vertices,
                        std::size_t count)
{
  SDL_RenderGeometry(m_renderer,
                     texture.GetHandle(),
                     vertices,
                     static_cast<int>(count),
                     nullptr,
                     0);
}

void
Renderer::DrawTriangles(const Texture& texture,
                        const SDL_Vertex* vertices,
                        std::size_t vertCount,
                        int* indices,
                        std::size_t indexCount)
{
  SDL_RenderGeometry(m_renderer,
                     texture.GetHandle(),
                     vertices,
                     static_cast<int>(vertCount),
                     indices,
                     static_cast<int>(indexCount));
}

SDL_Renderer*
Renderer::GetHandle() const
{
  return m_renderer;
}

void
Renderer::Present()
{
  SDL_RenderPresent(m_renderer);
}

void
Renderer::RenderCopy(const Texture& texture)
{
  SDL_RenderCopy(m_renderer, texture.GetHandle(), nullptr, nullptr);
}

void
Renderer::RenderCopy(const Texture& texture, const SDL_Rect& dst)
{
  SDL_RenderCopy(m_renderer, texture.GetHandle(), nullptr, &dst);
}

void
Renderer::RenderCopy(const Texture& texture,
                     const SDL_Rect& src,
                     const SDL_Rect& dst)
{
  SDL_RenderCopy(m_renderer, texture.GetHandle(), &src, &dst);
}

void
Renderer::SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
  SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
}

Renderer&
Renderer::operator=(Renderer&& renderer) noexcept
{
  std::swap(m_renderer, renderer.m_renderer);
  return *this;
}