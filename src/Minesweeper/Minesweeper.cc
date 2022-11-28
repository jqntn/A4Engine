#include <Minesweeper/Minesweeper.hh>

#include <Engine/CameraComponent.hh>
#include <Engine/GraphicsComponent.hh>
#include <Engine/InputManager.hh>
#include <Engine/ResourceManager.hh>
#include <Engine/Transform.hh>

#include <Engine/CollisionShape.hh>
#include <Engine/RigidBodyComponent.hh>
#include <entt/entt.hpp>
#include <imgui.h>

Minesweeper::Minesweeper(entt::registry& registry)
  : _registry(registry)
{
}

void
Minesweeper::Start()
{
  InputManager::Instance().BindKeyPressed(SDLK_s, "MoveDown");
  InputManager::Instance().BindKeyPressed(SDLK_z, "MoveUp");
  InputManager::Instance().BindKeyPressed(SDLK_q, "MoveLeft");
  InputManager::Instance().BindKeyPressed(SDLK_d, "MoveRight");
  InputManager::Instance().BindKeyPressed(SDLK_DOWN, "MoveDown");
  InputManager::Instance().BindKeyPressed(SDLK_UP, "MoveUp");
  InputManager::Instance().BindKeyPressed(SDLK_LEFT, "MoveLeft");
  InputManager::Instance().BindKeyPressed(SDLK_RIGHT, "MoveRight");

  InputManager::Instance().BindMouseButtonPressed(MouseButton::Left,
                                                  "LeftClick");
  InputManager::Instance().BindMouseButtonPressed(MouseButton::Right,
                                                  "RightClick");

  InputManager::Instance().OnAction("LeftClick", [&](bool isDown) {
    if (isDown && _canClick) {
      if (!_isPopulated) {
        if (Cell::_hoveredCell)
          if (Cell::_hoveredCell->_isHovered) {
            Cell::_hoveredCell->_isReserved = true;
            for (const auto& c : Cell::_hoveredCell->GetAdjacentCells())
              c->_isReserved = true;
            PopulateGrid();
            Cell::_hoveredCell->Unveil();
          }
      } else {
        if (Cell::_hoveredCell)
          if (Cell::_hoveredCell->_isHovered)
            Cell::_hoveredCell->Unveil();
      }
    }
  });
  InputManager::Instance().OnAction("RightClick", [&](bool isDown) {
    if (isDown && _canClick)
      if (Cell::_hoveredCell)
        if (Cell::_hoveredCell->_isHovered)
          Cell::_hoveredCell->Flag();
  });

  entt::entity cam = _registry.create();
  _registry.emplace<Transform>(cam);
  _registry.emplace<CameraComponent>(cam);

  LoadSprites();

  GenGrid();
}

void
Minesweeper::Update(float deltaTime)
{
  for (const auto& cell : _cells)
    cell->Update(deltaTime);
}

void
Minesweeper::Render(float deltaTime)
{
  ImGui::SetNextWindowPos({ 0, 0 });
  ImGui::SetNextWindowSize({ 200, 100 });

  ImGui::Begin("Minesweeper");

  auto str = "Flags Left: " + std::to_string(_flagsLeft);
  ImGui::Text(str.c_str());

  ImGui::Spacing();
  ImGui::Separator();
  ImGui::Spacing();

  if (ImGui::Button("Retry"))
    Retry();

  ImGui::End();

  ImGui::SetNextWindowPos({ 600, 0 });
  ImGui::SetNextWindowSize({ 200, 80 });

  ImGui::Begin("Controls");

  ImGui::Text("Left Click: Unveil");
  ImGui::Text("Right Click: Flag");

  ImGui::End();

  ImGui::SetNextWindowPos({ 0, 740 });
  ImGui::SetNextWindowSize({ 250, 60 });

  ImGui::Begin("Difficulty");

  ImGui::InputFloat("Bomb Prob.", &_bombProba);

  ImGui::End();
}

void
Minesweeper::LoadSprites()
{
  auto& ss = ResourceManager::Instance().GetTexture("assets/minesweeper.png");

  _oneSpr = LoadSprite(ss, POS_ONE);
  _twoSpr = LoadSprite(ss, POS_TWO);
  _threeSpr = LoadSprite(ss, POS_THREE);
  _fourSpr = LoadSprite(ss, POS_FOUR);
  _fiveSpr = LoadSprite(ss, POS_FIVE);
  _sixSpr = LoadSprite(ss, POS_SIX);
  _sevenSpr = LoadSprite(ss, POS_SEVEN);
  _heightSpr = LoadSprite(ss, POS_HEIGHT);

  _bgSpr = LoadSprite(ss, POS_BG);
  _fgSpr = LoadSprite(ss, POS_FG);

  _flagSpr = LoadSprite(ss, POS_FLAG);
  _bombSpr = LoadSprite(ss, POS_BOMB);
}

void
Minesweeper::GenGrid()
{
  int i{};
  for (auto y = 0; y < GRID_SIZE.y; y++) {
    for (auto x = 0; x < GRID_SIZE.x; x++) {
      auto pos = OFFSET_SCREEN + Vector2f(CELL_SIZE * x, CELL_SIZE * y);

      auto cell =
        std::make_shared<Cell>(_registry, _bgSpr, _fgSpr, _flagSpr, pos);

      cell->_isEmpty = true;
      cell->_index = i;
      cell->_posGrid = { x, y };

      _cells.push_back(cell);

      i++;
    }
  }

  _flagsLeft = 0;

  _canClick = true;
}

void
Minesweeper::PopulateGrid()
{
  _isPopulated = true;

  std::srand(static_cast<unsigned>(std::time(0)));

  std::vector<std::shared_ptr<Cell>> bombCells;

  auto bombs = 0;
  for (const auto& cell : _cells) {
    auto r = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
    if (r < _bombProba) {
      if (!cell->_isReserved) {
        cell->_isEmpty = false;
        cell->_isBomb = true;
        cell->_mainSpr = _bombSpr;
        bombs++;
        bombCells.push_back(cell);
      }
    }
  }

  _flagsLeft = bombs;

  for (const auto& bomb : bombCells) {
    auto ac = bomb->GetAdjacentCells();
    for (const auto& c : ac)
      if (!c->_isBomb)
        c->_bombCount++;
  }

  for (const auto& cell : _cells) {
    switch (cell->_bombCount) {
      case 1:
        cell->_isEmpty = false;
        cell->_mainSpr = _oneSpr;
        break;
      case 2:
        cell->_isEmpty = false;
        cell->_mainSpr = _twoSpr;
        break;
      case 3:
        cell->_isEmpty = false;
        cell->_mainSpr = _threeSpr;
        break;
      case 4:
        cell->_isEmpty = false;
        cell->_mainSpr = _fourSpr;
        break;
      case 5:
        cell->_isEmpty = false;
        cell->_mainSpr = _fiveSpr;
        break;
      case 6:
        cell->_isEmpty = false;
        cell->_mainSpr = _sixSpr;
        break;
      case 7:
        cell->_isEmpty = false;
        cell->_mainSpr = _sevenSpr;
        break;
      case 8:
        cell->_isEmpty = false;
        cell->_mainSpr = _heightSpr;
        break;
    }
  }
}

void
Minesweeper::ClearGrid()
{
  for (const auto& cell : _cells)
    cell->_registry.destroy(cell->_cell);

  _cells.clear();
}

void
Minesweeper::Retry()
{
  _isPopulated = false;

  ClearGrid();
  GenGrid();
}

std::shared_ptr<Sprite>
Minesweeper::LoadSprite(const std::shared_ptr<Texture>& ss, const Vector2i& pos)
{
  auto spr = std::make_shared<Sprite>(ss);

  spr->SetRect({ TILE_SIZE * pos.x, TILE_SIZE * pos.y, TILE_SIZE, TILE_SIZE });
  spr->Resize(CELL_SIZE, CELL_SIZE);

  return spr;
}