#pragma once
#include <iostream>
#include <sprite.hpp>
#include <color.hpp>

namespace SpaceInvaders {
	namespace Sprites {
		class Player : public SpaceInvaders::Sprite {
		public:
			Player();
			virtual ~Player();
			virtual void UpdateSpriteBuffer(SpaceInvaders::Buffer* buffer) override;
			void Fire(void);
			void Reload(void);
			bool GetIsFiring(void);
			bool GetIsReloading(void);
		private:
			SpaceInvaders::SpriteBuffer* buffer;
			int lifeCount;
			int isFiring;
			int isReloading;
			int reloadDuration;
			int reloadTime;
		};
	}
}