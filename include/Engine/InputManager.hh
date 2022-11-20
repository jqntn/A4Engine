#pragma once

#include <SDL.h>
#include <functional>
#include <string>
#include <unordered_map>

enum class MouseButton
{
  Left,
  Right,
  Middle,
  X1,
  X2
};

class InputManager
{
public:
  InputManager();
  InputManager(const InputManager&) = delete;
  InputManager(InputManager&&) = delete;
  ~InputManager();
  void BindKeyPressed(SDL_KeyCode keyCode, std::string action);
  void BindMouseButtonPressed(MouseButton button, std::string action);
  void BindControllerButton(SDL_GameControllerButton button,
                            std::string action);
  void ClearBindings();
  void HandleEvent(const SDL_Event& event);
  bool IsActive(const std::string& action) const;
  void OnAction(std::string action, std::function<void(bool)> func);

  InputManager& operator=(const InputManager&) = delete;
  InputManager& operator=(InputManager&&) = delete;

  static InputManager& Instance();

private:
  struct ActionData
  {
    std::function<void(bool)> func;
    bool isActive;
  };

  ActionData& GetActionData(const std::string& action);
  void TriggerAction(const std::string& action);
  void ReleaseAction(const std::string& action);

  std::unordered_map<int, std::string> m_mouseButtonToAction;
  std::unordered_map<SDL_GameControllerButton, std::string>
    m_controllerButtonToAction;
  std::unordered_map<SDL_Keycode, std::string> m_keyToAction;
  std::unordered_map<std::string, ActionData> m_actions;

  static InputManager* s_instance;
};