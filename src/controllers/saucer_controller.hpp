#pragma once
#include <iostream>
#include <controller.hpp>
#include <vector>
#include <game.hpp>

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