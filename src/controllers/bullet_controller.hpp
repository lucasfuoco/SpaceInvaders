#pragma once
#include <iostream>
#include <controller.hpp>
#include <game.hpp>

namespace SpaceInvaders {
	namespace Controllers {
		class BulletController : public SpaceInvaders::Controller {
		public:
			BulletController(SpaceInvaders::Game* game);
			virtual ~BulletController();
			virtual void Think(void) override;
		};
	}
}