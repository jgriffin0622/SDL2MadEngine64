#pragma once
#include <SDL.h>
#include "../Map/GameMap.h"

constexpr auto SCREEN_WIDTH = 960;;
constexpr auto SCREEN_HEIGHT = 640;;
constexpr auto MAP_WIDTH = 1920;;

class Engine {
public:
	static Engine* GetInstance() {
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new Engine();
	}

	bool Init();
	void Events();
	void Update();
	void Render();

	bool Cleanup();
	void Quit();

	inline GameMap* GetMap() { return m_LevelMap; }
	inline bool IsRunning() { return m_IsRunning; };
	inline SDL_Renderer* GetRenderer() {return m_Renderer;};

private:
	Engine() {
	};
	~Engine() {
	};

	static Engine* s_Instance;
	bool m_IsRunning;
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	GameMap* m_LevelMap;
};
