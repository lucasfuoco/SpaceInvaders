#pragma once
#include <spaceinvaders/controller.hpp>
#include <spaceinvaders/game.hpp>
#include <spaceinvaders/sprite.hpp>
#include <iostream>

namespace SpaceInvaders {
	namespace Controllers {
		class BulletController : public SpaceInvaders::Controller {
		public:
			BulletController(SpaceInvaders::Game* game);
			virtual ~BulletController();
			virtual void Think(void) override;
		private:
			bool getSpritesAreOverlaping(
				SpaceInvaders::Sprite* spriteA,
				SpaceInvaders::Sprite* spriteB
			);
		};
	}
}