#include <Components.h>
#include <InputManager.h>
#include <Matrix3.h>
#include <Model.h>
#include <PhysicsSystem.h>
#include <Renderer.h>
#include <ResourceManager.h>
#include <SDLPP.h>
#include <Sprite.h>
#include <Systems.h>
#include <Texture.h>
#include <Transform.h>
#include <Vector2.h>
#include <Window.h>

#include <chipmunk/chipmunk.h>
#include <entt/entt.hpp>
#include <fmt/core.h>
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_sdlrenderer.h>

#include <Windows.h>

#include <Shapes.h>
#include <iostream>

#define LOG(_) std::cout << _ << std::endl;

entt::entity
Create256Box(entt::registry& registry, Renderer& renderer)
{
  auto tex =
    ResourceManager::Inst().GetTexture(renderer, "assets/karmeliet.jpg");

  Sprite box(tex);
  box.Resize(256, 256);

  auto entity = registry.create();
  registry.emplace<Sprite>(entity, std::move(box));
  registry.emplace<Transform>(entity);

  return entity;
}

int
main()
{
  // Matrix
  float a[3][3]({ 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 });
  std::array<std::array<float, 3>, 3> b = { {
    { 5, 8, 2 },
    { 8, 3, 1 },
    { 5, 3, 9 },
  } };

  Matrix3 m0(a);
  Matrix3 m1(b);
  Matrix3 m2({ { { 5, 8, 2 }, { 8, 3, 1 }, { 5, 3, 9 } } });
  m0.Print();
  fmt::print("\n{}\n", m0(1, 1));
  m0(1, 1) = 0;
  fmt::print("{}\n", m0(1, 1));

  auto d = Matrix3::Determinant(m2.GetDataAsVector());
  fmt::print("\n{}\n", d);

  auto i = m2.Inverse();
  fmt::print("\n");
  i.Print();

  Vector2 vec(3, 7);
  fmt::print("\n");
  (vec * m2).Print();

  Vector2 vecTra(1, 0);
  auto traMat = Matrix3::Translate(Vector2(5, 3));
  fmt::print("\n");
  (vecTra * traMat).Print();

  Vector2 vecRot(1, 4);
  auto rotMat = Matrix3::Rotate(90);
  fmt::print("\n");
  (vecRot * rotMat).Print();

  Vector2 vecSca(2, 1);
  auto scaMat = Matrix3::Scale(Vector2(.5f, 2));
  fmt::print("\n");
  (vecSca * scaMat).Print();

  // return std::getchar();

  SetProcessDPIAware();

  // Setup
  SDLPP sdl;
  Window window("A4Engine", 1280, 720, SDL_RENDERER_PRESENTVSYNC);
  Renderer renderer(window);
  renderer.SetDrawColor(127, 0, 127, 255);

  // ImGui Setup
  ImGui::CreateContext();
  ImGui_ImplSDL2_InitForSDLRenderer(window.GetHandle(), renderer.GetHandle());
  ImGui_ImplSDLRenderer_Init(renderer.GetHandle());

  // ResourceManager & Sprite Anim Test
  auto tex = ResourceManager::Inst().GetTexture(renderer, "assets/runner.png");
  Sprite sprite(tex, SDL_Rect{ 0, 0, 32, 32 });
  sprite.Resize(256, 256);

  // Model Test
  auto house = Model::LoadFromFile(renderer, "assets/house.model");

  // Anim Timer
  auto frameIndex = 0, frameCount = 5;
  auto timer = 0.f;

  // Transform & Vector2 Test
  Transform transform;

  transform.SetPosition(Vector2(42, -6));
  transform.SetRotation(-270);
  transform.SetScale(Vector2(.5f, 2));

  transform.TransformPoint(Vector2(0, 0));
  transform.TransformPoint(Vector2(10, 0));
  transform.TransformPoint(Vector2(0, 10));
  transform.TransformPoint(Vector2(21, -3));

  transform.SetScale(Vector2(-.5f, -2));
  auto v = transform.TransformPoint(Vector2(-42, -42));
  // LOG(v.x)
  // LOG(v.y)

  Transform parent;
  parent.SetPosition(Vector2(512, 232));

  Transform child;
  child.SetPosition(Vector2(100, 100));

  // ECS
  entt::registry registry;

  entt::entity camera = registry.create();
  auto& camera_Transform = registry.emplace<Transform>(camera);
  camera_Transform.SetPosition(Vector2(-512, -232));
  registry.emplace<CameraComponent>(camera);

  entt::entity entity0 = registry.create();
  {
    auto& entity0_Transform = registry.emplace<Transform>(entity0);

    auto& entity0_Velocity = registry.emplace<VelocityComponent>(entity0);
    entity0_Velocity.x = 100;

    auto& entity0_Sprite =
      registry.emplace<Sprite>(entity0, tex, SDL_Rect{ 0, 0, 32, 32 });
    entity0_Sprite.Resize(256, 256);
  }

  // Physics
  auto box = Create256Box(registry, renderer);

  auto space = cpSpaceNew();
  cpSpaceSetGravity(space, { 0, 981 });
  cpSpaceSetDamping(space, .5f);

  auto boxBody = cpBodyNew(100, cpMomentForBox(100, 256, 256));
  cpSpaceAddBody(space, boxBody);
  cpBodySetAngle(boxBody, 15 * Rad2Deg);

  auto boxShape = cpBoxShapeNew(boxBody, 256, 256, 0);
  cpShapeGetCenterOfGravity(boxShape);
  cpSpaceAddShape(space, boxShape);

  auto floorBody = cpBodyNewStatic();
  auto floorShape =
    cpSegmentShapeNew(floorBody, cpv(-1000, 400), cpv(1000, 400), 0);
  cpSpaceAddShape(space, floorShape);

  float physicsStep = 1.f / 50;
  float physicsAccum = 0;

  // Physics - ECS
  auto texx =
    ResourceManager::Inst().GetTexture(renderer, "assets/karmeliet.jpg");
  Sprite boxx(texx);
  boxx.Resize(100, 100);

  PhysicsSystem physicsSystem(registry);

  entt::entity ent = registry.create();
  auto& entSprite = registry.emplace<Sprite>(ent, std::move(boxx));
  auto& entPhysics = registry.emplace<RigidBodyComponent>(ent, 100);
  auto& entTransform = registry.emplace<Transform>(ent);

  entPhysics.SetPos(Vector2(500, -100));

  auto sha = std::make_shared<BoxShape>(100, 100);
  entPhysics.AddShape(sha.get(), physicsSystem.GetSpace());

  InputManager::Inst().BindKeyPressed(SDL_KeyCode::SDLK_SPACE, "Force");
  InputManager::Inst().OnAction("Force", [&](bool pressed) {
    if (pressed) {
      cpBodyApplyImpulseAtWorldPoint(
        boxBody, cpv(0, -1000 * 50), cpBodyGetPosition(boxBody));
    }
  });

  // InputManager Test
  // InputManager::Inst().BindKeyPressed(SDLK_SPACE, "Close");
  // InputManager::Inst().BindMouseButtonPressed(SDL_BUTTON_RIGHT, "Close");
  InputManager::Inst().OnAction("Close", [&](bool) { window.Close(); });

  InputManager::Inst().BindKeyPressed(SDLK_z, "MoveUp");
  InputManager::Inst().BindKeyPressed(SDLK_s, "MoveDown");
  InputManager::Inst().BindKeyPressed(SDLK_q, "MoveLeft");
  InputManager::Inst().BindKeyPressed(SDLK_d, "MoveRight");

  // Time Counter
  auto then = SDL_GetPerformanceCounter();

  while (window.IsOpen()) {
    if (sdl.PollEvent()) {
      ImGui_ImplSDL2_ProcessEvent(&sdl.GetEvent());
      InputManager::Inst().HandleEvent(sdl.GetEvent());
      if (sdl.GetEvent().type == SDL_QUIT)
        window.Close();
    }

    // Time Counter
    auto now = SDL_GetPerformanceCounter();
    auto deltaTime = (float)(now - then) / SDL_GetPerformanceFrequency();
    then = now;

    // Anim Timer
    timer += deltaTime;
    if (timer > .1f) {
      timer -= .1f;
      frameIndex++;
      if (frameIndex >= frameCount)
        frameIndex = 0;
      sprite.SetRect({ frameIndex * 32, 0, 32, 32 });
    }

    // InputManager Test
    if (InputManager::Inst().IsActive("MoveUp"))
      LOG("MoveUp");
    if (InputManager::Inst().IsActive("MoveDown"))
      LOG("MoveDown");
    if (InputManager::Inst().IsActive("MoveLeft"))
      LOG("MoveLeft");
    if (InputManager::Inst().IsActive("MoveRight"))
      LOG("MoveRight");

    renderer.Clear();

    // Physics
    {
      physicsAccum += deltaTime;
      while (physicsAccum >= physicsStep) {
        cpSpaceStep(space, physicsStep);
        physicsAccum -= physicsStep;
      }

      auto pos = cpBodyGetPosition(boxBody);
      auto rot = cpBodyGetAngle(boxBody) * Rad2Deg;
      registry.get<Transform>(box).SetPosition(
        Vector2((float)pos.x, (float)pos.y));
      registry.get<Transform>(box).SetRotation((float)rot);
    }

    // Render Sprite
    // sprite.Draw(renderer, parent);
    // sprite.Draw(renderer, child);

    // Render Model
    // house.Draw(renderer);

    // ECS
    Systems::RenderSystem(registry, renderer);
    Systems::VelocitySystem(registry, deltaTime);

    // Physics - ECS
    physicsSystem.Update(deltaTime);

    // ImGui Render
    ImGui_ImplSDL2_NewFrame();
    ImGui_ImplSDLRenderer_NewFrame();
    ImGui::NewFrame();

    // Camera Controls
    ImGui::Begin("Camera");

    auto& pos = camera_Transform.GetPosition();
    float posPtr[2] = { pos.x, pos.y };
    auto& scale = camera_Transform.GetScale();
    float scalePtr[2] = { scale.x, scale.y };
    auto rot = camera_Transform.GetRotation();

    if (ImGui::SliderFloat2("Position", posPtr, -1000, 1000))
      camera_Transform.SetPosition(Vector2(posPtr[0], posPtr[1]));
    if (ImGui::SliderFloat2("Scale", scalePtr, .1f, 5))
      camera_Transform.SetScale(Vector2(scalePtr[0], scalePtr[1]));
    if (ImGui::SliderFloat("Rotation", &rot, -180, 180))
      camera_Transform.SetRotation(rot);

    ImGui::End();

    // ImGui::ShowDemoWindow();

    ImGui::Render();
    ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());

    renderer.Present();
  }

  cpSpaceRemoveShape(space, boxShape);
  cpShapeFree(boxShape);

  cpSpaceRemoveBody(space, boxBody);
  cpBodyFree(boxBody);

  cpSpaceFree(space);
}