#ifndef _PLAYER_H
#define _PLAYER_H

#include "GameObject.h"
using namespace SGEngine;

class Player : public SGGameObject
{
	public:
		Player();
		~Player();

		void Update(float dt);

	private:

};

#endif // !_PLAYER_H
