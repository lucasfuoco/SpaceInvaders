#pragma once
#include <iostream>
#include <spaceinvaders/controller.hpp>
#include <vector>
#include <spaceinvaders/game.hpp>

namespace SpaceInvaders {
	namespace Controllers {
		class SaucerController : public SpaceInvaders::Controller {
		public:
			SaucerController(SpaceInvaders::Game* game);
			virtual ~SaucerController();
			virtual void Think(void) override;
		};
	}
}