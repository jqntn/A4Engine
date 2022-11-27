#pragma once

class Renderer;
class Window;
union SDL_Event;
struct ImGuiContext;

class ImGuiCC
{
public:
  ImGuiCC(Window& window, Renderer& renderer);
  ImGuiCC(const ImGuiCC&) = delete;
  ImGuiCC(ImGuiCC&&) = delete;
  ~ImGuiCC();

  ImGuiContext* GetContext();

  void Render();

  void NewFrame();

  void ProcessEvent(SDL_Event& event);

  ImGuiCC& operator=(const ImGuiCC&) = delete;
  ImGuiCC& operator=(ImGuiCC&&) = delete;

private:
  ImGuiContext* m_context;
};