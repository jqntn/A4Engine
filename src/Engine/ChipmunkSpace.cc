#include <Engine/ChipmunkSpace.hh>
#include <Engine/Renderer.hh>
#include <SDL.h>
#include <algorithm>
#include <chipmunk/chipmunk.h>
#include <vector>

ChipmunkSpace::ChipmunkSpace()
{
  m_handle = cpSpaceNew();
  cpSpaceSetCollisionSlop(m_handle, 0.f);
}

ChipmunkSpace::ChipmunkSpace(ChipmunkSpace&& space) noexcept
{
  m_handle = space.m_handle;
  space.m_handle = nullptr;
}

ChipmunkSpace::~ChipmunkSpace()
{
  if (m_handle)
    cpSpaceFree(m_handle);
}

void
ChipmunkSpace::DebugDraw(Renderer& renderer,
                         const Matrix3f& cameraInverseTransform)
{
  struct DrawData
  {
    Renderer& renderer;
    const Matrix3f& viewMatrix;
  };

  DrawData drawData{ renderer, cameraInverseTransform };

  cpSpaceDebugDrawOptions drawOptions;
  drawOptions.collisionPointColor = cpSpaceDebugColor{ 0.f, 0.f, 1.f, 1.f };
  drawOptions.constraintColor = cpSpaceDebugColor{ 0.f, 1.f, 0.f, 1.f };
  drawOptions.shapeOutlineColor = cpSpaceDebugColor{ 1.f, 0.f, 0.f, 1.f };
  drawOptions.data = &drawData;

  std::underlying_type_t<cpSpaceDebugDrawFlags> drawFlags = 0;
  drawOptions.flags = static_cast<cpSpaceDebugDrawFlags>(
    CP_SPACE_DEBUG_DRAW_SHAPES | CP_SPACE_DEBUG_DRAW_COLLISION_POINTS);
  drawOptions.colorForShape = [](cpShape*, cpDataPointer) {
    return cpSpaceDebugColor{ 1.f, 0.f, 0.f, 1.f };
  };

  drawOptions.drawCircle = [](cpVect pos,
                              cpFloat,
                              cpFloat radius,
                              cpSpaceDebugColor outlineColor,
                              cpSpaceDebugColor,
                              cpDataPointer data) {
    DrawData& drawData = *static_cast<DrawData*>(data);

    std::array<SDL_FPoint, 21> points;
    for (std::size_t i = 0; i < 20; ++i) {
      float angle = 2 * M_PI * i / 20;
      Vector2f finalPos =
        drawData.viewMatrix * Vector2f(pos.x + std::sin(angle) * radius,
                                       pos.y + std::cos(angle) * radius);
      points[i] = { finalPos.x, finalPos.y };
    }
    points[20] = points[0];

    drawData.renderer.SetDrawColor(outlineColor.r * 255,
                                   outlineColor.g * 255,
                                   outlineColor.b * 255,
                                   outlineColor.a * 255);
    drawData.renderer.DrawLines(points.data(), points.size());
  };

  drawOptions.drawDot =
    [](cpFloat size, cpVect pos, cpSpaceDebugColor color, cpDataPointer data) {
      DrawData& drawData = *static_cast<DrawData*>(data);

      Vector2f dotPos =
        drawData.viewMatrix *
        Vector2f(static_cast<float>(pos.x), static_cast<float>(pos.y));
      float s = static_cast<float>(size);

      std::array<SDL_FPoint, 5> points;
      points[0] = { dotPos.x - s, dotPos.y - s };
      points[1] = { dotPos.x + s, dotPos.y - s };
      points[2] = { dotPos.x + s, dotPos.y + s };
      points[3] = { dotPos.x - s, dotPos.y + s };
      points[4] = { dotPos.x - s, dotPos.y - s };

      drawData.renderer.SetDrawColor(
        color.r * 255, color.g * 255, color.b * 255, color.a * 255);
      drawData.renderer.DrawLines(points.data(), points.size());
    };

  drawOptions.drawFatSegment = [](cpVect a,
                                  cpVect b,
                                  cpFloat radius,
                                  cpSpaceDebugColor outlineColor,
                                  cpSpaceDebugColor,
                                  cpDataPointer data) {
    DrawData& drawData = *static_cast<DrawData*>(data);

    Vector2f from = drawData.viewMatrix *
                    Vector2f(static_cast<float>(a.x), static_cast<float>(a.y));
    Vector2f to = drawData.viewMatrix *
                  Vector2f(static_cast<float>(b.x), static_cast<float>(b.y));
    float r = static_cast<float>(radius);

    std::array<SDL_FPoint, 5> points;
    points[0] = { from.x - r, from.y - r };
    points[1] = { to.x + r, to.y - r };
    points[2] = { to.x + r, to.y + r };
    points[3] = { from.x - r, from.y + r };
    points[4] = { from.x - r, from.y - r };

    drawData.renderer.SetDrawColor(outlineColor.r * 255,
                                   outlineColor.g * 255,
                                   outlineColor.b * 255,
                                   outlineColor.a * 255);
    drawData.renderer.DrawLines(points.data(), points.size());
  };

  drawOptions.drawPolygon = [](int vertexCount,
                               const cpVect* vertices,
                               cpFloat,
                               cpSpaceDebugColor outlineColor,
                               cpSpaceDebugColor,
                               cpDataPointer data) {
    DrawData& drawData = *static_cast<DrawData*>(data);

    std::vector<SDL_FPoint> points;
    points.reserve(vertexCount);

    for (int i = 0; i < vertexCount; ++i) {
      Vector2f pos =
        drawData.viewMatrix * Vector2f(static_cast<float>(vertices[i].x),
                                       static_cast<float>(vertices[i].y));
      points.push_back({ pos.x, pos.y });
    }
    points.push_back(points.front());

    drawData.renderer.SetDrawColor(outlineColor.r * 255,
                                   outlineColor.g * 255,
                                   outlineColor.b * 255,
                                   outlineColor.a * 255);
    drawData.renderer.DrawLines(points.data(), points.size());
  };

  drawOptions.drawSegment =
    [](cpVect a, cpVect b, cpSpaceDebugColor color, cpDataPointer data) {
      DrawData& drawData = *static_cast<DrawData*>(data);

      Vector2f from = drawData.viewMatrix * Vector2f(static_cast<float>(a.x),
                                                     static_cast<float>(a.y));
      Vector2f to = drawData.viewMatrix *
                    Vector2f(static_cast<float>(b.x), static_cast<float>(b.y));

      std::array<SDL_FPoint, 2> points;
      points[0] = { from.x, from.y };
      points[1] = { to.x, to.y };

      drawData.renderer.SetDrawColor(
        color.r * 255, color.g * 255, color.b * 255, color.a * 255);
      drawData.renderer.DrawLines(points.data(), points.size());
    };

  cpSpaceDebugDraw(m_handle, &drawOptions);
}

cpSpace*
ChipmunkSpace::GetHandle() const
{
  return m_handle;
}

void
ChipmunkSpace::SetDamping(float damping)
{
  cpSpaceSetDamping(m_handle, damping);
}

void
ChipmunkSpace::SetGravity(const Vector2f& gravity)
{
  cpSpaceSetGravity(m_handle, cpv(gravity.x, gravity.y));
}

void
ChipmunkSpace::Step(float deltaTime)
{
  cpSpaceStep(m_handle, deltaTime);
}

ChipmunkSpace&
ChipmunkSpace::operator=(ChipmunkSpace&& space) noexcept
{
  std::swap(m_handle, space.m_handle);
  return *this;
}