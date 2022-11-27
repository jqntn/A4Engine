#pragma once

#include <Minesweeper/Cell.hh>

#include <Engine/Sprite.hh>
#include <Engine/Texture.hh>
#include <Engine/Vector2.hh>

#include <entt/entity/fwd.hpp>

#include <vector>

class Minesweeper
{
public:
  Minesweeper(entt::registry& registry);

  virtual ~Minesweeper() = default;

  void Start();
  void Update(float deltaTime);
  void Render(float deltaTime);

  inline static int _flagsLeft{};

  inline static std::vector<std::shared_ptr<Cell>> _cells;

private:
  const int TILE_SIZE = 16;
  const int CELL_SIZE = 32;

  const Vector2f OFFSET_SCREEN = { 150, 150 };

  const Vector2i GRID_SIZE = { 16, 16 };

  const Vector2i POS_ONE = { 0, 1 };
  const Vector2i POS_TWO = { 1, 1 };
  const Vector2i POS_THREE = { 2, 1 };
  const Vector2i POS_FOUR = { 3, 1 };
  const Vector2i POS_FIVE = { 4, 1 };
  const Vector2i POS_SIX = { 5, 1 };
  const Vector2i POS_SEVEN = { 6, 1 };
  const Vector2i POS_HEIGHT = { 7, 1 };

  const Vector2i POS_BG = { 1, 0 };
  const Vector2i POS_FG = { 0, 0 };

  const Vector2i POS_FLAG = { 2, 0 };
  const Vector2i POS_BOMB = { 6, 0 };

  entt::registry& _registry;

  std::shared_ptr<Sprite> _oneSpr;
  std::shared_ptr<Sprite> _twoSpr;
  std::shared_ptr<Sprite> _threeSpr;
  std::shared_ptr<Sprite> _fourSpr;
  std::shared_ptr<Sprite> _fiveSpr;
  std::shared_ptr<Sprite> _sixSpr;
  std::shared_ptr<Sprite> _sevenSpr;
  std::shared_ptr<Sprite> _heightSpr;

  std::shared_ptr<Sprite> _bgSpr;
  std::shared_ptr<Sprite> _fgSpr;

  std::shared_ptr<Sprite> _flagSpr;
  std::shared_ptr<Sprite> _bombSpr;

  bool _isPopulated{};
  float _bombProba = .1f;

  void LoadSprites();
  void GenGrid();
  void PopulateGrid();
  void ClearGrid();
  void Retry();

  std::shared_ptr<Sprite> LoadSprite(const std::shared_ptr<Texture>& ss,
                                     const Vector2i& pos);
};