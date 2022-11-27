#include <Engine/ImGuiCC.hh>
#include <Engine/Renderer.hh>
#include <Engine/Window.hh>
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_sdlrenderer.h>

ImGuiCC::ImGuiCC(Window& window, Renderer& renderer)
{
  IMGUI_CHECKVERSION();
  m_context = ImGui::CreateContext();

  ImGui::StyleColorsDark();

  ImGui_ImplSDL2_InitForSDLRenderer(window.GetHandle(), renderer.GetHandle());
  ImGui_ImplSDLRenderer_Init(renderer.GetHandle());
}

ImGuiCC::~ImGuiCC()
{
  ImGui_ImplSDLRenderer_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext(m_context);
}

ImGuiContext*
ImGuiCC::GetContext()
{
  return m_context;
}

void
ImGuiCC::Render()
{
  ImGui::Render();
  ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
}

void
ImGuiCC::NewFrame()
{
  ImGui_ImplSDLRenderer_NewFrame();
  ImGui_ImplSDL2_NewFrame();
  ImGui::NewFrame();
}

void
ImGuiCC::ProcessEvent(SDL_Event& event)
{
  ImGui_ImplSDL2_ProcessEvent(&event);
}