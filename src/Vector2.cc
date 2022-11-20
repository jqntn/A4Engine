#include <Vector2.h>

#include <Matrix3.h>

#include <fmt/core.h>

Vector2::Vector2(float x, float y)
  : x(x)
  , y(y)
{
}

Vector2&
Vector2::operator-=(const Vector2& other)
{
  x -= other.x;
  y -= other.y;
  return *this;
}

Vector2&
Vector2::operator+=(const Vector2& other)
{
  x += other.x;
  y += other.y;
  return *this;
}

Vector2
Vector2::operator-(const Vector2& other) const
{
  return Vector2(*this) -= other;
}

Vector2
Vector2::operator+(const Vector2& other) const
{
  return Vector2(*this) += other;
}

Vector2&
Vector2::operator/=(const Vector2& other)
{
  x /= other.x;
  y /= other.y;
  return *this;
}

Vector2
Vector2::operator/(const Vector2& other) const
{
  return Vector2(*this) /= other;
}

Vector2&
Vector2::operator*=(const Vector2& other)
{
  x *= other.x;
  y *= other.y;
  return *this;
}

Vector2
Vector2::operator*(const Vector2& other) const
{
  return Vector2(*this) *= other;
}

Vector2&
Vector2::operator/=(float f)
{
  x /= f;
  y /= f;
  return *this;
}

Vector2&
Vector2::operator*=(float f)
{
  x *= f;
  y *= f;
  return *this;
}

Vector2
Vector2::operator/(float f) const
{
  return Vector2(*this) /= f;
}

Vector2
Vector2::operator*(float f) const
{
  return Vector2(*this) *= f;
}

void
Vector2::Print() const
{
  fmt::print("{}, {}\n", x, y);
}

Vector2
Vector2::operator*(const Matrix3& matrix) const
{
  float vIn[3] = { x, y, 1 };
  float vOut[3]{};

  for (auto i = 0; i < 3; i++)
    for (auto j = 0; j < 3; j++)
      vOut[i] += matrix(i, j) * vIn[j];

  return Vector2(vOut[0], vOut[1]);
}