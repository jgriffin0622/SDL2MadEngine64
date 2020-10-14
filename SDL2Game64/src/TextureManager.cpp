#include "TextureManager.h"
#include "Core/Engine.h"
#include "camera/Camera.h"

TextureManager* TextureManager::s_Instance = nullptr;

bool TextureManager::Load(std::string id, std::string filename)
{
	SDL_Surface* surface = IMG_Load(filename.c_str());
	if (surface == nullptr) {
		SDL_Log("SDL surface failed to load: %s", SDL_GetError());
		return false;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), surface);
	if (texture == nullptr) {
		SDL_Log("SDL textture from surface failed: %s", SDL_GetError());
		return false;
	}

	SDL_FreeSurface(surface);

	//m_TextureMap.emplace(id,texture);
	m_TextureMap[id] = texture; 
	return true;
}

bool TextureManager::ParseTextures(std::string source)
{
	TiXmlDocument xml;
	xml.LoadFile(source);
	if (xml.Error()) {
		std::cout << "Textures failed to load "<<source<<'\n';
		return false;
	}

	TiXmlElement* root = xml.RootElement();
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		if (e->Value() == std::string("texture")) {
			std::string id = e->Attribute("id");
			std::string src = e->Attribute("source");
			Load(id, src);
		}
	}
	return true;
}

void TextureManager::Drop(std::string id)
{
	SDL_DestroyTexture(m_TextureMap[id]);
	m_TextureMap.erase(id);
}

void TextureManager::Clean()
{
	std::map<std::string, SDL_Texture*>::iterator it;
	for (it = m_TextureMap.begin(); it != m_TextureMap.end(); it++) {
		SDL_DestroyTexture(it->second);
	}
	m_TextureMap.clear();
	std::cout << "texture map cleaned\n";
}

void TextureManager::Draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = 136;
	srcRect.h = 96;

	destRect.x = x;
	destRect.y = y;
	destRect.w = 136;
	destRect.h = 96;

	SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &destRect, 0, nullptr,flip);

}
void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = width*frame;
	srcRect.y = height*row-1;
	srcRect.w = width;
	srcRect.h = height;
	//	srcRect.w = 136;
//	srcRect.h = 96;

	Vector2D cam = Camera::GetInstance()->GetPosition();

	destRect.x = x - cam.X;
	destRect.y = y;
	destRect.w = width;
	destRect.h = height;

	SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &destRect, 0, nullptr, flip);

}
void TextureManager::DrawTile(std::string tilesetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip)
{
	SDL_Rect srcRect = { tileSize * frame, tileSize * row,tileSize,tileSize };
	Vector2D cam = Camera::GetInstance()->GetPosition();

	SDL_Rect destRect = {x - cam.X,y,tileSize,tileSize};
	SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(),m_TextureMap[tilesetID],&srcRect,&destRect,0,0,flip);
}
