#pragma once

#include <Engine/Matrix3.hh>

class Renderer;
class Texture;
class Transform;

class Renderable
{
public:
  virtual ~Renderable() = default;

  virtual void Draw(Renderer& renderer, const Matrix3f& matrix) = 0;
};