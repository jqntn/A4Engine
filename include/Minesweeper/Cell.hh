#pragma once

#include <Engine/GraphicsComponent.hh>
#include <Engine/Sound.hh>
#include <Engine/Sprite.hh>
#include <Engine/Vector2.hh>

#include <entt/entity/fwd.hpp>

#include <vector>

struct Cell
{
  Cell(entt::registry& registry,
       std::shared_ptr<Sprite> mainSpr,
       const std::shared_ptr<Sprite>& fgSpr,
       const std::shared_ptr<Sprite>& flagSpr,
       const Vector2f& pos);
  virtual ~Cell();

  void Update(float deltaTime);

  void Unveil();
  void Flag();

  std::vector<std::shared_ptr<Cell>> GetAdjacentCells();

  void SetSprite(const std::shared_ptr<Sprite>& spr);

  const int CELL_SIZE = 32;

  inline static Cell* _hoveredCell;

  bool _isReserved{};

  bool _isEmpty{};
  bool _isBomb{};

  bool _isHovered{};
  bool _isFlagged{};
  bool _isUnveiled{};

  int _index{};
  int _bombCount{};

  Vector2i _posGrid{};

  std::shared_ptr<Sprite> _mainSpr;
  const std::shared_ptr<Sprite>& _fgSpr;
  const std::shared_ptr<Sprite>& _flagSpr;

  std::shared_ptr<Sound> _minecraft_click;
  std::shared_ptr<Sound> _vineboom;
  std::shared_ptr<Sound> _tacobell;

  entt::registry& _registry;

  entt::entity _cell;

  Transform& _cellTra;
  GraphicsComponent& _cellGC;
};