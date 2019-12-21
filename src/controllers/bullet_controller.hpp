#pragma once
#include <iostream>
#include <controller.hpp>
#include <game.hpp>
#include <sprite.hpp>

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