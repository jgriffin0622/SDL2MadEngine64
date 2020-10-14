#pragma once
#include "Character.h"
#include "../Animation/SpriteAnimation.h"
#include"../Physics/Rigidbody.h"
#include "../Physics/Collider.h"
#include "../Physics/Collider.h"

constexpr float JUMP_TIME = 15.0f;
constexpr float JUMP_FORCE = 10.0f;

constexpr float RUN_FORCE = 4.0f;
constexpr float ATTACK_TIME = 20.0f;

class Warrior :public Character {
public:
	Warrior(Properties* props);
	virtual void Update(float dt);
	virtual void Draw();
	virtual void Clean();

private:
	bool m_IsRunning;
	bool m_IsJumping;
	bool m_IsFalling;
	bool m_IsGrounded;
	bool m_IsCrouching;
	bool m_IsAttacking;

	float m_JumpForce;
	float m_JumpTime;
	float m_AttackTime;

	Collider* m_Collider;
	SpriteAnimation* m_Animation;
	Rigidbody* m_Rigidbody;
	Vector2D m_LastSafePosition;

	void AnimationState();
};
