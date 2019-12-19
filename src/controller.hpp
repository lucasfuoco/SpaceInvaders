#pragma once
#include <iostream>

namespace SpaceInvaders {
	class Game;

	class Controller {
	public:
		Controller(SpaceInvaders::Game* _game);
		virtual ~Controller();
		virtual void Think(void);
	protected:
		SpaceInvaders::Game* game;
	};
}