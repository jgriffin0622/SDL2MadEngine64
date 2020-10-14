#pragma once

constexpr int TARGET_FPS = 60;
constexpr float TARGET_DELTATIME = 1.5f;

class Timer {
public:
	inline static Timer* GetInstance() {
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new Timer();
	}
	void Tick();
	inline float GetDeltaTime() {
		return m_DeltaTime;
	}
private:

	Timer() { 
		m_DeltaTime = TARGET_DELTATIME;
	}
	
	static Timer* s_Instance;
	float m_DeltaTime;
	float m_LastTime;
};
