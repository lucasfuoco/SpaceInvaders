#pragma once
#include <iostream>
#include <spaceinvaders/sprite.hpp>
#include <spaceinvaders/color.hpp>

namespace SpaceInvaders {
	namespace Sprites {
		class Bullet : public SpaceInvaders::Sprite {
		public:
			Bullet();
			virtual ~Bullet();
			virtual void ClearData(void) override;
			int GetDirection(void);
			void SetDirection(int direction);
			void ResetPosition(void);
		private:
			int direction;
		};
	}
}