#pragma once

#include <array>
#include <vector>

class Vector2;

class Matrix3
{
public:
  Matrix3(std::array<std::array<float, 3>, 3> data);
  Matrix3(float data[3][3]);

  Matrix3() = default;
  ~Matrix3() = default;

  Matrix3(const Matrix3&) = default;
  Matrix3(Matrix3&&) = default;
  Matrix3& operator=(const Matrix3&) = default;
  Matrix3& operator=(Matrix3&&) = default;

  const int& GetRows() const;
  const int& GetCols() const;
  const std::array<std::array<float, 3>, 3>& GetData() const;
  std::vector<std::vector<float>> GetDataAsVector() const;

  void Print() const;

  float& operator()(int row, int col);
  const float& operator()(int row, int col) const;

  Matrix3 operator/(float value) const;
  Matrix3 operator*(float value) const;
  Matrix3 operator/(const Matrix3& other) const;
  Matrix3 operator*(const Matrix3& other) const;
  Vector2 operator*(const Vector2& vector) const;

  Matrix3 Transpose() const;
  Matrix3 Inverse() const;
  Matrix3 Adjugate() const;
  Matrix3 CofactorMatrix() const;
  float Cofactor(int row, int col) const;
  float GetMinor(int row, int col) const;

  static Matrix3 Identity();

  static float Determinant(std::vector<std::vector<float>> matrix);
  static std::vector<std::vector<float>>
  Submatrix(const std::vector<std::vector<float>>& matrix, int row, int col);

  static Matrix3 Translate(Vector2 position);
  static Matrix3 Rotate(float angle);
  static Matrix3 Scale(Vector2 scale);

  static Matrix3 SRT(Vector2 scale, float angle, Vector2 position);
  static Matrix3 TRS(Vector2 position, float angle, Vector2 scale);

private:
  int _rows = 3;
  int _cols = 3;

  std::array<std::array<float, 3>, 3> _data{};
};