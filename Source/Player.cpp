#include "Player.h"
#include "Input.h"
#include <External/GLFW/glfw3.h>

Player::Player()
{
	
}

void Player::Update(float dt)
{
	if (Input::instance().GetKey(GLFW_KEY_D))
		this->transform.Rotate(SGVector3(0.0f, 10.0f * dt, 0.0f));
	else if (Input::instance().GetKey(GLFW_KEY_A))
		this->transform.Rotate(SGVector3(0.0f, -10.0f * dt, 0.0f));

	if (Input::instance().GetKey(GLFW_KEY_W))
		this->transform.Translate(SGVector3(0.0f, 0.0f, 10.0f * dt));
	else if (Input::instance().GetKey(GLFW_KEY_S))
		this->transform.Translate(SGVector3(0.0f, 0.0f, -10.0f * dt));
}

Player::~Player()
{

}