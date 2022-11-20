#pragma once

#include <Engine/Matrix3.hh>

class SDLppRenderer;
class SDLppTexture;
class Transform;

class Renderable
{
public:
  virtual ~Renderable() = default;

  virtual void Draw(SDLppRenderer& renderer, const Matrix3f& matrix) = 0;
};