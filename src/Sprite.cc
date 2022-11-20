#include <Sprite.h>

#include <Matrix3.h>
#include <Renderer.h>
#include <Texture.h>
#include <Transform.h>

Sprite::Sprite(const std::shared_ptr<Texture>& texture)
  : Sprite(texture, texture->GetRect())
{
}

Sprite::Sprite(const std::shared_ptr<Texture>& texture, const SDL_Rect& rect)
  : _texture(texture)
  , _rect(rect)
  , _width(rect.w)
  , _height(rect.h)
{
}

const Vector2&
Sprite::GetOrigin() const
{
  return _origin;
}

int
Sprite::GetWidth() const
{
  return _width;
}

int
Sprite::GetHeight() const
{
  return _height;
}

void
Sprite::SetOrigin(const Vector2& origin)
{
  _origin = origin;
}

void
Sprite::SetRect(SDL_Rect rect)
{
  _rect = rect;
}

void
Sprite::Resize(int width, int height)
{
  _width = width;
  _height = height;
}

void
Sprite::Draw(Renderer& renderer, const Matrix3& matrix)
{
  auto origin = _origin * Vector2((float)_width, (float)_height);

  auto topL = (Vector2(0.f, 0.f) - origin) * matrix;
  auto topR = (Vector2((float)_width, 0.f) - origin) * matrix;
  auto botL = (Vector2(0.f, (float)_height) - origin) * matrix;
  auto botR = (Vector2((float)_width, (float)_height) - origin) * matrix;

  auto texRect = _texture.get()->GetRect();

  float invWidth = 1.f / texRect.w;
  float invHeight = 1.f / texRect.h;

  auto white = SDL_Color{ 255, 255, 255, 255 };

  SDL_Vertex vert[4]{};

  vert[0].color = white;
  vert[0].position = SDL_FPoint{ topL.x, topL.y };
  vert[0].tex_coord = SDL_FPoint{ _rect.x * invWidth, _rect.y * invHeight };

  vert[1].color = white;
  vert[1].position = SDL_FPoint{ topR.x, topR.y };
  vert[1].tex_coord =
    SDL_FPoint{ (_rect.x + _rect.w) * invWidth, _rect.y * invHeight };

  vert[2].color = white;
  vert[2].position = SDL_FPoint{ botL.x, botL.y };
  vert[2].tex_coord =
    SDL_FPoint{ _rect.x * invWidth, (_rect.y + _rect.h) * invHeight };

  vert[3].color = white;
  vert[3].position = SDL_FPoint{ botR.x, botR.y };
  vert[3].tex_coord = SDL_FPoint{ (_rect.x + _rect.w) * invWidth,
                                  (_rect.y + _rect.h) * invHeight };

  int indices[6] = { 0, 1, 2, 2, 1, 3 };

  SDL_RenderGeometry(
    renderer.GetHandle(), _texture.get()->GetHandle(), vert, 4, indices, 6);
}