#pragma once
#include <controller.hpp>
#include <vector>
#include <game.hpp>
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