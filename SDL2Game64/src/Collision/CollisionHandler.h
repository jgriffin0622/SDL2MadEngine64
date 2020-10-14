#pragma once
#include <SDL.h>
#include <vector>
#include "../Map/GameMap.h"
#include "../Map/TileLayer.h"

class CollisionHandler {
public:
	bool MapCollision(SDL_Rect a);
	bool CheckCollision(SDL_Rect a, SDL_Rect b);

	inline static CollisionHandler* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new CollisionHandler();}
private:
	CollisionHandler();
	TileMap m_CollisionTilemap;
	TileLayer* m_CollisionLayer;
	static CollisionHandler* s_Instance;

};
