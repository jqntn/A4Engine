#pragma once

#include <memory>

class Renderable;

struct GraphicsComponent
{
  std::shared_ptr<Renderable> renderable;
};