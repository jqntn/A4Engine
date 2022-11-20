#pragma once

#include <SDL.h>

#include <functional>
#include <string>
#include <unordered_map>

class InputManager
{
public:
  static InputManager& Inst()
  {
    static InputManager inst;
    return inst;
  }

  void BindGamepadButtonPressed(SDL_GameControllerButton button,
                                std::string action);
  void BindMouseButtonPressed(Uint8 button, std::string action);
  void BindKeyPressed(SDL_KeyCode key, std::string action);

  void OnAction(std::string action, std::function<void(bool)> func);
  bool IsActive(const std::string& action) const;

  void HandleEvent(const SDL_Event& event);

  void ClearBindings();

private:
  InputManager() = default;
  ~InputManager() = default;

  InputManager(const InputManager&) = delete;
  InputManager(InputManager&&) = delete;
  InputManager& operator=(const InputManager&) = delete;
  InputManager& operator=(InputManager&&) = delete;

  struct ActionData
  {
    std::function<void(bool)> func;
    bool isActive{};
  };

  ActionData& GetActionData(const std::string& action);

  void TriggerAction(const std::string& action);
  void ReleaseAction(const std::string& action);

  std::unordered_map<SDL_GameControllerButton, std::string>
    _boundGamepadButtons;
  std::unordered_map<Uint8, std::string> _boundMouseButtons;
  std::unordered_map<SDL_Keycode, std::string> _boundKeys;
  std::unordered_map<std::string, ActionData> _actions;
};