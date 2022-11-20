#include <Engine/Model.hh>
#include <Engine/ResourceManager.hh>
#include <Engine/SDLppSurface.hh>
#include <Engine/SDLppTexture.hh>
#include <stdexcept>

ResourceManager::ResourceManager(SDLppRenderer& renderer)
  : m_renderer(renderer)
{
  if (s_instance != nullptr)
    throw std::runtime_error("only one ResourceManager can be created");

  s_instance = this;
}

ResourceManager::~ResourceManager()
{
  s_instance = nullptr;
}

void
ResourceManager::Clear()
{
  m_missingModel.reset();
  m_missingTexture.reset();
  m_models.clear();
  m_textures.clear();
}

const std::shared_ptr<Model>&
ResourceManager::GetModel(const std::string& modelPath)
{
  auto it = m_models.find(modelPath);
  if (it != m_models.end())
    return it->second;
  Model model = Model::LoadFromFile(modelPath);
  if (!model.IsValid()) {
    if (!m_missingModel)
      m_missingModel = std::make_shared<Model>();

    m_models.emplace(modelPath, m_missingModel);
    return m_missingModel;
  }

  it = m_models.emplace(modelPath, std::make_shared<Model>(std::move(model)))
         .first;
  return it->second;
}

const std::shared_ptr<SDLppTexture>&
ResourceManager::GetTexture(const std::string& texturePath)
{
  auto it = m_textures.find(texturePath);
  if (it != m_textures.end())
    return it->second;
  SDLppSurface surface = SDLppSurface::LoadFromFile(texturePath);
  if (!surface.IsValid()) {
    if (!m_missingTexture) {
      surface = SDLppSurface(64, 64);
      surface.FillRect(SDL_Rect{ 0, 0, 16, 16 }, 255, 0, 255, 255);
      surface.FillRect(SDL_Rect{ 16, 0, 16, 16 }, 0, 0, 0, 255);
      surface.FillRect(SDL_Rect{ 0, 16, 16, 16 }, 0, 0, 0, 255);
      surface.FillRect(SDL_Rect{ 16, 16, 16, 16 }, 255, 0, 255, 255);

      m_missingTexture = std::make_shared<SDLppTexture>(
        SDLppTexture::LoadFromSurface(m_renderer, surface));
    }
    m_textures.emplace(texturePath, m_missingTexture);
    return m_missingTexture;
  }
  std::shared_ptr<SDLppTexture> texture = std::make_shared<SDLppTexture>(
    SDLppTexture::LoadFromSurface(m_renderer, surface));
  it = m_textures.emplace(texturePath, std::move(texture)).first;

  return it->second;
}

void
ResourceManager::Purge()
{
  for (auto it = m_textures.begin(); it != m_textures.end();) {
    if (it->second.use_count() > 1) {
      ++it;
    } else {
      it = m_textures.erase(it);
    }
  }
  for (auto it = m_models.begin(); it != m_models.end();) {
    if (it->second.use_count() > 1)
      ++it;
    else
      it = m_models.erase(it);
  }
}

ResourceManager&
ResourceManager::Instance()
{
  if (s_instance == nullptr)
    throw std::runtime_error("ResourceManager hasn't been instantied");

  return *s_instance;
}

ResourceManager* ResourceManager::s_instance = nullptr;