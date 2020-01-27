#pragma once
#include <spaceinvaders/controller.hpp>
#include <vector>
#include <spaceinvaders/game.hpp>
#include <iostream>

namespace SpaceInvaders {
	namespace Controllers {
		class PlayerController : public SpaceInvaders::Controller {
		public:
			PlayerController(SpaceInvaders::Game* game);
			virtual ~PlayerController();
			virtual void Think(void) override;
		};
	}
}