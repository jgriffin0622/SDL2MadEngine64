#include "Warrior.h"
#include "..\TextureManager.h"
#include <SDL.h>
#include "../Inputs/Input.h"
#include "../Collision/CollisionHandler.h"
#include "../Core/Engine.h"

Warrior::Warrior(Properties* props):Character(props)
{
	m_JumpTime = JUMP_TIME;
	m_JumpForce = JUMP_FORCE;
	m_AttackTime = ATTACK_TIME;

	m_Collider = new Collider();
	m_Collider->SetBuffer(60, 20, 0, 0);

	m_Rigidbody = new Rigidbody();
	m_Rigidbody->SetGravity(5.0f);

	m_Animation = new SpriteAnimation();
	//textureid tag, sprite row, frames, animation speed
	m_Animation->SetProps(m_TextureId, 0, 6, 100);
}

void Warrior::Update(float dt){
	m_IsRunning = false;
	m_IsCrouching = false;
	m_Rigidbody->UnsetForce();

	if (Input::GetInstance()->GetAxisKey(HORIZONTAL)== FORWARD && !m_IsAttacking) {
		m_Rigidbody->ApplyForceX(FORWARD*RUN_FORCE);
		m_Flip = SDL_FLIP_NONE;
		m_IsRunning = true;
		//m_Animation->SetProps("knight_run", 0, 8, 100);

	}

		if (Input::GetInstance()->GetAxisKey(HORIZONTAL) == BACKWARD && !m_IsAttacking) {
			m_Rigidbody->ApplyForceX(BACKWARD * RUN_FORCE);
			m_Flip = SDL_FLIP_HORIZONTAL;
			m_IsRunning = true;
			//m_Animation->SetProps("knight_run", 0, 8, 100);
			}

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S)) {
		m_Rigidbody->UnsetForce();
		m_IsCrouching = true;
//		m_Animation->SetProps("knight_run", 0, 8, 100,SDL_FLIP_NONE);
	}
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_K)) {
		m_Rigidbody->UnsetForce();
		m_IsAttacking = true;
		//		m_Animation->SetProps("knight_run", 0, 8, 100,SDL_FLIP_NONE);
	}

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W) && m_IsGrounded){
		m_IsJumping = true;
		m_IsGrounded = false;
		m_Rigidbody->ApplyForceY(m_JumpForce * UPWARD);
//		m_Animation->SetProps("knight_jump", 0, 4, 100, SDL_FLIP_NONE);
	}

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W) && m_IsJumping && m_JumpTime > 0) {
		m_JumpTime -= dt;
		m_Rigidbody->ApplyForceY(m_JumpForce * UPWARD);
	}
	else {
		m_IsJumping = false;
		m_JumpTime = JUMP_TIME;
	}

	if (m_Rigidbody->Velocity().Y > 0 && !m_IsGrounded){
		m_IsFalling = true;
		}
	else {
		m_IsFalling = false;
	}

	if (m_IsAttacking && m_AttackTime > 0) {
		m_AttackTime -= dt;
	}
	else {
		m_IsAttacking = false;
		m_AttackTime = ATTACK_TIME;
	}


	m_Rigidbody->update(dt);
	m_LastSafePosition.X = m_Transform->X;
	m_Transform->X += m_Rigidbody->Position().X;
	m_Collider->Set(m_Transform->X, m_Transform->Y, 96, 96);

	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
		m_Transform->X = m_LastSafePosition.X;
	}
	//keep on screen
	if (m_Transform->X <= 0 || m_Transform->X+m_Width>MAP_WIDTH) {
		m_Transform->X = m_LastSafePosition.X;
	}

	m_Rigidbody->update(dt);
	m_LastSafePosition.Y = m_Transform->Y;
	m_Transform->Y += m_Rigidbody->Position().Y;
	m_Collider->Set(m_Transform->X, m_Transform->Y, 96, 96);
	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
		m_Transform->Y = m_LastSafePosition.Y;
		m_IsGrounded = true;
	}
	else {
		m_IsGrounded = false;
//		m_Transform->TranslateY(m_Rigidbody->Position().Y);
	}


//	m_Frame = (SDL_GetTicks() / m_AnimSpeed) % m_FrameCount;
//	m_Rigidbody->update(1.0);
//	m_Rigidbody->update(dt);



//	m_Transform->TranslateX(m_Rigidbody->Position().X);

	m_Origin->X = m_Transform->X + m_Width / 2;
	m_Origin->Y = m_Transform->Y + m_Height / 2;
	AnimationState();
	m_Animation->Update(dt);
}

void Warrior::Draw()
{
//	TextureManager::GetInstance()->DrawFrame(m_TextureId, m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Row, m_Frame);
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height,1,1,m_Flip);
}

void Warrior::Clean()
{
	TextureManager::GetInstance()->Drop(m_TextureId);
}

void Warrior::AnimationState()
{
	m_Animation->SetProps("knight_idle", 0, 6, 100);

	if (m_IsRunning) {
		m_Animation->SetProps("knight_run", 0, 8, 100);
	}
	if (m_IsCrouching) {
		m_Animation->SetProps("knight_crouch", 0, 6, 200);
	}
	if (m_IsJumping) {
		m_Animation->SetProps("knight_jump", 0, 2, 200);
	}
	if (m_IsFalling) {
		m_Animation->SetProps("knight_fall", 0, 2, 350);
	}
	if (m_IsAttacking) {
		m_Animation->SetProps("knight_attack", 0, 14, 80);
	}

}
