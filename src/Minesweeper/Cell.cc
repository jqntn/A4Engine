#include <Minesweeper/Cell.hh>

#include <Minesweeper/Minesweeper.hh>

#include <Engine/InputManager.hh>
#include <Engine/ResourceManager.hh>
#include <Engine/RigidBodyComponent.hh>
#include <Engine/Transform.hh>

#include <entt/entt.hpp>

Cell::Cell(entt::registry& registry,
           std::shared_ptr<Sprite> mainSpr,
           const std::shared_ptr<Sprite>& fgSpr,
           const std::shared_ptr<Sprite>& flagSpr,
           const Vector2f& pos)
  : _mainSpr(mainSpr)
  , _fgSpr(fgSpr)
  , _flagSpr(flagSpr)
  , _registry(registry)
  , _cell(_registry.create())
  , _cellTra(_registry.emplace<Transform>(_cell))
  , _cellGC(_registry.emplace<GraphicsComponent>(_cell, fgSpr))
{
  _cellTra.SetPosition(pos);

  _minecraft_click =
    ResourceManager::Instance().GetSound("assets/minecraft_click.wav");
  _vineboom = ResourceManager::Instance().GetSound("assets/vineboom.wav");
  _tacobell = ResourceManager::Instance().GetSound("assets/tacobell.wav");

  alSourcef(_vineboom->GetSource(), AL_GAIN, .1f);
  alSourcef(_tacobell->GetSource(), AL_GAIN, .1f);
}

void
Cell::Update(float deltaTime)
{
  int x, y;
  SDL_GetMouseState(&x, &y);

  auto mousePos = Vector2i(x, y);

  auto& pos = _cellTra.GetPosition();

  if (mousePos.x >= pos.x && mousePos.x < pos.x + CELL_SIZE &&
      mousePos.y >= pos.y && mousePos.y < pos.y + CELL_SIZE) {
    _isHovered = true;
    _hoveredCell = this;
  } else
    _isHovered = false;

  if (_needToExplode) {
    _timeToExplode -= deltaTime;
    if (_timeToExplode < 0) {
      for (const auto& cell : Minesweeper::_cells) {
        shape = std::make_shared<CircleShape>(CELL_SIZE * 3);
        auto& rb = _registry.emplace<RigidBodyComponent>(cell->_cell, 1);
        rb.AddShape(std::move(shape));
        rb.TeleportTo(cell->_cellTra.GetPosition());
        cell->_needToExplode = false;
      }
    }
  }
}

void
Cell::Unveil()
{
  if (_isFlagged)
    return;

  if (_isUnveiled)
    return;

  _isUnveiled = true;

  SetSprite(_mainSpr);

  if (_isBomb) {
    _vineboom->Play();

    Minesweeper::_canClick = false;

    for (const auto& cell : Minesweeper::_cells)
      cell->_needToExplode = true;
  }

  if (_isEmpty)
    for (const auto& cell : GetAdjacentCells())
      cell->Unveil();
}

void
Cell::Flag()
{
  if (_isUnveiled)
    return;

  _isFlagged ^= true;

  if (_isFlagged) {
    if (Minesweeper::_flagsLeft > 0) {
      SetSprite(_flagSpr);
      _tacobell->Play();
      Minesweeper::_flagsLeft--;
    } else
      _isFlagged = false;
  } else {
    SetSprite(_fgSpr);
    Minesweeper::_flagsLeft++;
  }
}

std::vector<std::shared_ptr<Cell>>
Cell::GetAdjacentCells()
{
  std::vector<std::shared_ptr<Cell>> adjacents;

  std::shared_ptr<Cell> down;
  std::shared_ptr<Cell> up;
  std::shared_ptr<Cell> left;
  std::shared_ptr<Cell> right;
  std::shared_ptr<Cell> botleft;
  std::shared_ptr<Cell> botRight;
  std::shared_ptr<Cell> topleft;
  std::shared_ptr<Cell> topRight;

  for (const auto& cell : Minesweeper::_cells) {
    if (cell->_posGrid.x == _posGrid.x)
      if (cell->_posGrid.y == _posGrid.y + 1)
        down = cell;

    if (cell->_posGrid.x == _posGrid.x)
      if (cell->_posGrid.y == _posGrid.y - 1)
        up = cell;

    if (cell->_posGrid.x == _posGrid.x - 1)
      if (cell->_posGrid.y == _posGrid.y)
        left = cell;

    if (cell->_posGrid.x == _posGrid.x + 1)
      if (cell->_posGrid.y == _posGrid.y)
        right = cell;

    if (cell->_posGrid.x == _posGrid.x - 1)
      if (cell->_posGrid.y == _posGrid.y + 1)
        botleft = cell;

    if (cell->_posGrid.x == _posGrid.x + 1)
      if (cell->_posGrid.y == _posGrid.y + 1)
        botRight = cell;

    if (cell->_posGrid.x == _posGrid.x - 1)
      if (cell->_posGrid.y == _posGrid.y - 1)
        topleft = cell;

    if (cell->_posGrid.x == _posGrid.x + 1)
      if (cell->_posGrid.y == _posGrid.y - 1)
        topRight = cell;
  }

  if (down)
    adjacents.push_back(down);
  if (up)
    adjacents.push_back(up);
  if (left)
    adjacents.push_back(left);
  if (right)
    adjacents.push_back(right);
  if (botleft)
    adjacents.push_back(botleft);
  if (botRight)
    adjacents.push_back(botRight);
  if (topleft)
    adjacents.push_back(topleft);
  if (topRight)
    adjacents.push_back(topRight);

  return adjacents;
}

void
Cell::SetSprite(const std::shared_ptr<Sprite>& spr)
{
  _cellGC.renderable = spr;
}