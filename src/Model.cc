#include <Model.h>

#include <Renderer.h>
#include <Texture.h>
#include <Transform.h>

#include <ResourceManager.h>
#include <nlohmann/json.hpp>

#include <fstream>

Model::Model(const std::shared_ptr<Texture>& texture,
             const std::vector<int>& indices,
             const std::vector<SDL_Vertex>& vertices)
  : _texture(texture)
  , _indices(indices)
  , _vertices(vertices)
{
}

Model
Model::LoadFromFile(Renderer& renderer, const char* path)
{
  std::ifstream ifs(path);
  auto js = nlohmann::json::parse(ifs);

  std::shared_ptr<Texture> texture;

  auto& texKey = js.at("texture");
  if (texKey != nullptr) {
    std::string texStr = texKey;
    if (!texStr.empty())
      texture = ResourceManager::Inst().GetTexture(renderer, texStr.c_str());
  }

  std::vector<int> indices;
  std::vector<SDL_Vertex> vertices;

  for (const auto& i : js.at("indices"))
    indices.push_back(i);

  for (const auto& vert : js.at("vertices")) {
    auto& pos = vert.at("position");
    auto& tc = vert.at("uv");
    auto& col = vert.at("color");

    SDL_FPoint position{ pos[0], pos[1] };
    SDL_FPoint tex_coord{ tc[0], tc[1] };
    SDL_Color color{ col[0], col[1], col[2], col[3] };

    SDL_Vertex vertex{ position, color, tex_coord };

    vertices.push_back(vertex);
  }

  return Model(texture, indices, vertices);
}

void
Model::Draw(Renderer& renderer)
{
  auto tex = _texture ? _texture.get()->GetHandle() : nullptr;

  SDL_RenderGeometry(renderer.GetHandle(),
                     tex,
                     _vertices.data(),
                     (int)_vertices.size(),
                     _indices.data(),
                     (int)_indices.size());
}