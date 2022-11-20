#pragma once

#include <Engine/Vector2.hh>

struct VelocityComponent
{
  Vector2f linearVel = Vector2f(0.f, 0.f);
  float angularVel = 0.f;
};