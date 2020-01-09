#pragma once
#include <iostream>
#include <sprites/bullet.hpp>
#include <color.hpp>

namespace SpaceInvaders {
	namespace Sprites {
		namespace Bullets {
			class DiBullet : public SpaceInvaders::Sprites::Bullet {
			public:
				DiBullet();
				virtual ~DiBullet();
				virtual void ClearData(void) override;
				virtual void UpdateSpriteBuffer(SpaceInvaders::Buffer* buffer) override;
			private:
				SpaceInvaders::SpriteBuffer* buffer1;
				SpaceInvaders::SpriteBuffer* buffer2;
			};
		}
	}
}