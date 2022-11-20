#include <InputManager.h>

void
InputManager::BindGamepadButtonPressed(SDL_GameControllerButton button,
                                       std::string action)
{
  if (!action.empty())
    _boundGamepadButtons[button] = std::move(action);
  else
    _boundGamepadButtons.erase(button);
}

void
InputManager::BindMouseButtonPressed(Uint8 button, std::string action)
{
  if (!action.empty())
    _boundMouseButtons[button] = std::move(action);
  else
    _boundMouseButtons.erase(button);
}

void
InputManager::BindKeyPressed(SDL_KeyCode keyCode, std::string action)
{
  if (!action.empty())
    _boundKeys[keyCode] = std::move(action);
  else
    _boundKeys.erase(keyCode);
}

void
InputManager::OnAction(std::string action, std::function<void(bool)> func)
{
  GetActionData(action).func = std::move(func);
}

bool
InputManager::IsActive(const std::string& action) const
{
  auto it = _actions.find(action);

  if (it == _actions.end())
    return false;

  return it->second.isActive;
}

void
InputManager::HandleEvent(const SDL_Event& event)
{
  switch (event.type) {
    case SDL_CONTROLLERBUTTONDOWN: {
      auto it = _boundGamepadButtons.find(
        static_cast<SDL_GameControllerButton>(event.cbutton.button));
      if (it != _boundGamepadButtons.end())
        TriggerAction(it->second);
    } break;

    case SDL_CONTROLLERBUTTONUP: {
      auto it = _boundGamepadButtons.find(
        static_cast<SDL_GameControllerButton>(event.cbutton.button));
      if (it != _boundGamepadButtons.end())
        ReleaseAction(it->second);
    } break;

    case SDL_MOUSEBUTTONDOWN: {
      auto it = _boundMouseButtons.find(event.button.button);
      if (it != _boundMouseButtons.end())
        TriggerAction(it->second);
    } break;

    case SDL_MOUSEBUTTONUP: {
      auto it = _boundMouseButtons.find(event.button.button);
      if (it != _boundMouseButtons.end())
        ReleaseAction(it->second);
    } break;

    case SDL_KEYDOWN: {
      auto it = _boundKeys.find(event.key.keysym.sym);
      if (it != _boundKeys.end())
        TriggerAction(it->second);
    } break;

    case SDL_KEYUP: {
      auto it = _boundKeys.find(event.key.keysym.sym);
      if (it != _boundKeys.end())
        ReleaseAction(it->second);
    } break;
  }
}

void
InputManager::ClearBindings()
{
  _boundGamepadButtons.clear();
  _boundMouseButtons.clear();
  _boundKeys.clear();
}

InputManager::ActionData&
InputManager::GetActionData(const std::string& action)
{
  auto it = _actions.find(action);

  if (it != _actions.end())
    return it->second;

  auto& actionData = _actions[action];
  actionData.isActive = false;

  return actionData;
}

void
InputManager::TriggerAction(const std::string& action)
{
  auto& actionData = GetActionData(action);
  actionData.isActive = true;
  if (actionData.func)
    actionData.func(true);
}

void
InputManager::ReleaseAction(const std::string& action)
{
  auto& actionData = GetActionData(action);
  actionData.isActive = false;
  if (actionData.func)
    actionData.func(false);
}