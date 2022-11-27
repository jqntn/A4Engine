#pragma once

#include <Engine/Matrix3.hh>
#include <Engine/Vector2.hh>

struct cpSpace;
class Renderer;

class ChipmunkSpace
{
public:
  ChipmunkSpace();
  ChipmunkSpace(const ChipmunkSpace&) = delete;
  ChipmunkSpace(ChipmunkSpace&& space) noexcept;
  ~ChipmunkSpace();

  void DebugDraw(Renderer& renderer, const Matrix3f& cameraInverseTransform);

  cpSpace* GetHandle() const;

  void SetDamping(float damping);
  void SetGravity(const Vector2f& gravity);

  void Step(float deltaTime);

  ChipmunkSpace& operator=(const ChipmunkSpace&) = delete;
  ChipmunkSpace& operator=(ChipmunkSpace&& space) noexcept;

private:
  cpSpace* m_handle;
};