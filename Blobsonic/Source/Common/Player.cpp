#include "stdafx.h"
#include "Player.h"

Component::Player::Player()
{
	m_fMoveSpeed = 100.0f;
	m_fTurnSpeed = 100.0f;
}

void Component::Player::setMoveSpeed(float newSpeed)
{
	m_fMoveSpeed = newSpeed;
}

void Component::Player::setTurnSpeed(float newTurnSpeed)
{
	m_fTurnSpeed = newTurnSpeed;
}

float Component::Player::getMoveSpeed()
{
	return m_fMoveSpeed;
}

float Component::Player::getTurnSpeed()
{
	return m_fTurnSpeed;
}
