#include <Matrix3.h>

#include <Transform.h>
#include <Vector2.h>

#include <algorithm>
#include <cmath>
#include <fmt/core.h>
#include <numbers>
#include <stdexcept>

Matrix3::Matrix3(std::array<std::array<float, 3>, 3> data)
  : _data(data)
{
}

Matrix3::Matrix3(float data[3][3])
{
  std::copy(&data[0][0], &data[0][0] + 3 * 3, &_data[0][0]);
}

const int&
Matrix3::GetRows() const
{
  return _rows;
}

const int&
Matrix3::GetCols() const
{
  return _cols;
}

const std::array<std::array<float, 3>, 3>&
Matrix3::GetData() const
{
  return _data;
}

std::vector<std::vector<float>>
Matrix3::GetDataAsVector() const
{
  std::vector<std::vector<float>> result(_data.size(),
                                         std::vector<float>(_data.size(), 0));

  for (auto i = 0; i < _data.size(); i++)
    for (auto j = 0; j < _data[0].size(); j++)
      result[i][j] = _data[i][j];

  return result;
}

void
Matrix3::Print() const
{
  for (auto row = 0; row < _rows; row++)
    for (auto col = 0; col < _cols; col++)
      fmt::print("[{}][{}]: {}\n", row, col, _data[row][col]);
}

float&
Matrix3::operator()(int row, int col)
{
  return _data[row][col];
}

const float&
Matrix3::operator()(int row, int col) const
{
  return _data[row][col];
}

Matrix3
Matrix3::operator/(float value) const
{
  Matrix3 result(_data);

  for (auto row = 0; row < _rows; row++)
    for (auto col = 0; col < _cols; col++)
      result(row, col) = operator()(row, col) / value;

  return result;
}

Matrix3
Matrix3::operator*(float value) const
{
  Matrix3 result(_data);

  for (auto row = 0; row < _rows; row++)
    for (auto col = 0; col < _cols; col++)
      result(row, col) = operator()(row, col) * value;

  return result;
}

Matrix3
Matrix3::operator/(const Matrix3& other) const
{
  Matrix3 result(_data);

  for (auto i = 0; i < result._rows; i++) {
    for (auto j = 0; j < result._cols; j++) {
      auto tmp = 0.f;
      for (auto k = 0; k < _cols; k++)
        tmp += operator()(i, k) / other(k, j);
      result(i, j) = tmp;
    }
  }

  return result;
}

Matrix3
Matrix3::operator*(const Matrix3& other) const
{
  Matrix3 result(_data);

  for (auto i = 0; i < result._rows; i++) {
    for (auto j = 0; j < result._cols; j++) {
      auto tmp = 0.f;
      for (auto k = 0; k < _cols; k++)
        tmp += operator()(i, k) * other(k, j);
      result(i, j) = tmp;
    }
  }

  return result;
}

Vector2
Matrix3::operator*(const Vector2& vector) const
{
  float vIn[3] = { vector.x, vector.y, 1 };
  float vOut[3]{};

  for (auto i = 0; i < 3; i++)
    for (auto j = 0; j < 3; j++)
      vOut[i] += _data[i][j] * vIn[j];

  return Vector2(vOut[0], vOut[1]);
}

Matrix3
Matrix3::Identity()
{
  Matrix3 result;

  for (auto i = 0; i < 3; i++)
    result(i, i) = 1;

  return result;
}

std::vector<std::vector<float>>
Matrix3::Submatrix(const std::vector<std::vector<float>>& matrix,
                   int row,
                   int col)
{
  auto rows = matrix.size();
  auto cols = matrix[0].size();

  std::vector<std::vector<float>> result(rows - 1,
                                         std::vector<float>(cols - 1));

  auto subi = 0;
  for (auto i = 0; i < rows; i++) {
    auto subj = 0;
    if (i == row)
      continue;
    for (auto j = 0; j < cols; j++) {
      if (j == col)
        continue;
      result[subi][subj] = matrix[i][j];
      subj++;
    }
    subi++;
  }

  return result;
}

float
Matrix3::Determinant(std::vector<std::vector<float>> matrix)
{
  auto rows = matrix.size();
  auto d = 0.f;

  if (rows == 2)
    return matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
  else
    for (auto col = 0; col < rows; col++)
      d += (float)std::pow(-1, col) * matrix[0][col] *
           Determinant(Submatrix(matrix, 0, col));

  return d;
}

Matrix3
Matrix3::Transpose() const
{
  Matrix3 result(_data);

  for (auto row = 0; row < _rows; row++)
    for (auto col = 0; col < _cols; col++)
      result(row, col) = operator()(col, row);

  return result;
}

Matrix3
Matrix3::Inverse() const
{
  auto d = Determinant(GetDataAsVector());
  if (d == 0)
    throw std::runtime_error("Matrix is singular.");
  return Adjugate() / d;
}

Matrix3
Matrix3::Adjugate() const
{
  return CofactorMatrix().Transpose();
}

Matrix3
Matrix3::CofactorMatrix() const
{
  Matrix3 result(_data);

  for (auto row = 0; row < _rows; row++)
    for (auto col = 0; col < _cols; col++)
      result(row, col) = Cofactor(row, col);

  return result;
}

float
Matrix3::Cofactor(int row, int col) const
{
  auto minor = 0.f;
  minor = GetMinor(row, col);
  return (row + col) % 2 == 0 ? minor : -minor;
}

float
Matrix3::GetMinor(int row, int col) const
{
  return Determinant(Submatrix(GetDataAsVector(), row, col));
}

Matrix3
Matrix3::Translate(Vector2 position)
{
  return Matrix3({ {
    { 1, 0, position.x },
    { 0, 1, position.y },
    { 0, 0, 1 },
  } });
}

Matrix3
Matrix3::Rotate(float angle)
{
  auto a = angle * Deg2Rad;
  auto cos = std::cos(a);
  auto sin = std::sin(a);

  return Matrix3({ {
    { cos, -sin, 0 },
    { sin, cos, 0 },
    { 0, 0, 1 },
  } });
}

Matrix3
Matrix3::Scale(Vector2 scale)
{
  return Matrix3({ {
    { scale.x, 0, 0 },
    { 0, scale.y, 0 },
    { 0, 0, 1 },
  } });
}

Matrix3
Matrix3::SRT(Vector2 scale, float angle, Vector2 position)
{
  return Matrix3::Scale(scale) * Matrix3::Rotate(angle) *
         Matrix3::Translate(position);
}

Matrix3
Matrix3::TRS(Vector2 position, float angle, Vector2 scale)
{
  return Matrix3::Translate(position) * Matrix3::Rotate(angle) *
         Matrix3::Scale(scale);
}