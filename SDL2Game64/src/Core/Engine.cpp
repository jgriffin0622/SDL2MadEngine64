#include "Engine.h"
#include "..\TextureManager.h"
#include "..\Physics\Transform.h"
#include "..\Characters\Warrior.h"
#include "../Inputs/Input.h"
#include "../Timer/Timer.h"
#include "../Map/MapParser.h"
#include <iostream>
#include "../camera/Camera.h"

Engine* Engine::s_Instance = nullptr;
Warrior* player = nullptr;

bool Engine::Init()
{
	m_IsRunning = false;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_Log("SDL failed to initialize %s", SDL_GetError());
		return false;
	}

	SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
	m_Window = SDL_CreateWindow("MAD Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, window_flags);
	if (m_Window == nullptr) {
		SDL_Log("SDL window failed: %s", SDL_GetError());
		return false;
	}
	
	m_Renderer = SDL_CreateRenderer(m_Window, -1, (SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
	if (m_Renderer == nullptr) {
		SDL_Log("SDL renderer failed: %s", SDL_GetError());
		return false;
	}

	if (!MapParser::GetInstance()->Load()) {
		std::cout<<"map failed to load\n";
	}

	m_LevelMap = MapParser::GetInstance()->GetMap("level1");

	TextureManager::GetInstance()->ParseTextures("assets/textures.xml");
	/*TextureManager::GetInstance()->Load("knight_idle","assets/knight_idle_1x.png");
	TextureManager::GetInstance()->Load("knight_run", "assets/knight_run_1x.png");
	TextureManager::GetInstance()->Load("knight_jump", "assets/knight_jump_1x.png");
	TextureManager::GetInstance()->Load("knight_fall", "assets/knight_fall_1x.png");
	TextureManager::GetInstance()->Load("knight_crouch", "assets/knight_crouch_1x.png");
	TextureManager::GetInstance()->Load("knight_attack", "assets/knight_attack_1x.png");*/

	//x=0,y=0,width=136,height=96 (actually 76)
	/*int tileSize = 32;
	int startX = 0;
	int startY = SCREEN_HEIGHT - 76 - (4*tileSize);
	player = new Warrior(new Properties("knight_idle", startX, startY, 136, 96));*/
	
	player = new Warrior(new Properties("knight_idle", 0, 0, 136, 96));

	Camera::GetInstance()->SetTarget(player->GetOrigin());

	m_IsRunning = true;
	return true;
}

void Engine::Events()
{
	Input::GetInstance()->Listen();
}

void Engine::Update(){
	float dt = Timer::GetInstance()->GetDeltaTime();
	//SDL_Log("%f",dt);
	m_LevelMap->Update();
	Camera::GetInstance()->Update(dt);
	player->Update(dt);
}

void Engine::Render()
{
	SDL_RenderClear(m_Renderer);
//	SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
	SDL_SetRenderDrawColor(m_Renderer, 124, 218, 254, 255);

	m_LevelMap->Render();

	player->Draw();

	SDL_RenderPresent(m_Renderer);
}

bool Engine::Cleanup()
{
	return true;
}

void Engine::Quit()
{
	m_IsRunning = false;
}
