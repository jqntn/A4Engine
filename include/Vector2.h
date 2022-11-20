#pragma once

class Matrix3;

class Vector2
{
public:
  Vector2(float x, float y);

  Vector2() = default;
  ~Vector2() = default;

  Vector2(const Vector2&) = default;
  Vector2(Vector2&&) = default;
  Vector2& operator=(const Vector2&) = default;
  Vector2& operator=(Vector2&&) = default;

  Vector2& operator-=(const Vector2& other);
  Vector2& operator+=(const Vector2& other);
  Vector2 operator+(const Vector2& other) const;
  Vector2 operator-(const Vector2& other) const;

  Vector2& operator/=(const Vector2& other);
  Vector2 operator/(const Vector2& other) const;
  Vector2& operator*=(const Vector2& other);
  Vector2 operator*(const Vector2& other) const;

  Vector2& operator/=(float f);
  Vector2& operator*=(float f);
  Vector2 operator/(float f) const;
  Vector2 operator*(float f) const;

  Vector2 operator*(const Matrix3& matrix) const;

  void Print() const;

  float x{}, y{};
};
