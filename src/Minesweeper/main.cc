#include <Minesweeper/Minesweeper.hh>

#include <Engine/AnimationSystem.hh>
#include <Engine/CameraComponent.hh>
#include <Engine/ImGuiCC.hh>
#include <Engine/InputManager.hh>
#include <Engine/OpenALCC.hh>
#include <Engine/PhysicsSystem.hh>
#include <Engine/RenderSystem.hh>
#include <Engine/Renderer.hh>
#include <Engine/ResourceManager.hh>
#include <Engine/SDLCC.hh>
#include <Engine/Transform.hh>
#include <Engine/VelocitySystem.hh>
#include <Engine/Window.hh>

#include <Windows.h>

#include <entt/entt.hpp>
#include <fmt/core.h>
#include <imgui.h>

int
WinMain(HINSTANCE, HINSTANCE, PSTR, INT)
{
  SetProcessDPIAware();

  auto registry = entt::registry();

  auto sdl = SDLCC();
  auto openAL = OpenALCC();
  auto inputManager = InputManager();
  auto window = Window("Minesweeper", 800, 800);
  auto renderer = Renderer(window);
  auto imgui = ImGuiCC(window, renderer);
  auto resourceManager = ResourceManager(renderer);

  renderer.SetDrawColor(100, 150, 100, 250);

  ImGui::SetCurrentContext(imgui.GetContext());

  auto renderSystem = RenderSystem(renderer, registry);
  auto physicsSystem = PhysicsSystem(registry);

  physicsSystem.SetGravity({ 0, 981 });
  physicsSystem.SetDamping(.5f);

  auto isRunning = true;
  auto event = SDL_Event();
  auto then = SDL_GetPerformanceCounter();

  auto minesweeper = Minesweeper(registry);

  minesweeper.Start();

  while (isRunning) {
    if (SDLCC::PollEvent(&event)) {
      if (event.type == SDL_QUIT)
        isRunning = false;
      InputManager::Instance().HandleEvent(event);
      imgui.ProcessEvent(event);
    }

    auto now = SDL_GetPerformanceCounter();
    auto deltaTime = (float)(now - then) / SDL_GetPerformanceFrequency();
    then = now;

    minesweeper.Update(deltaTime);

    renderer.Clear();
    imgui.NewFrame();

    minesweeper.Render(deltaTime);

    renderSystem.Update(deltaTime);
    physicsSystem.Update(deltaTime);

    imgui.Render();
    renderer.Present();
  }
}