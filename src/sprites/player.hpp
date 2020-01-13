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
			bool GetIsDead(void);
			void Die(void);
			void Respawn(void);
			const int GetDeathFrameCount(void) const;
			void DecrementDeathFrameCount(int frame);
		private:
			SpaceInvaders::SpriteBuffer* buffer;
			SpaceInvaders::SpriteBuffer* deathBuffer;
			int lifeCount;
			int isFiring;
			int isReloading;
			int reloadDuration;
			int reloadTime;
			bool isDead;
			int deathFrameCount;
		};
	}
}