#pragma once
#include <iostream>
#include <spaceinvaders/sprites/bullet.hpp>
#include <spaceinvaders/color.hpp>

namespace SpaceInvaders {
	namespace Sprites {
		namespace Bullets {
			class SharpBullet : public SpaceInvaders::Sprites::Bullet {
			public:
				SharpBullet();
				virtual ~SharpBullet();
				virtual void ClearData(void) override;
			private:
				SpaceInvaders::SpriteBuffer* buffer;
			};
		}
	}
}