#pragma once
#include <iostream>
#include <sprite.hpp>

namespace SpaceInvaders {
	class Game;

	namespace Sprites {
		class Saucer : public SpaceInvaders::Sprite {
		public:
			Saucer();
			virtual ~Saucer();
			virtual void ClearData(void) override;
			virtual void UpdateSpriteBuffer(SpaceInvaders::Buffer* buffer) override;
			void Die(void);
			bool GetIsDead(void);
			int GetDeathPoint(void);
			bool GetSpriteInFieldOfView(const SpaceInvaders::Sprite* sprite);
			void Fire(void);
			void Reload(void);
			bool GetIsFiring(void);
			bool GetIsReloading(void);
			bool GetCanFire(SpaceInvaders::Game* game, int index);
			const int GetDeathFrameCount(void) const;
			void DecrementDeathFrameCount(int frame);
		protected:
			void setDeathPoint(int point);
			void setReloadDuration(int duration);

			SpaceInvaders::SpriteBuffer* deathBuffer;
		private:
			bool isDead;
			int deathPoint;
			int isFiring;
			int isReloading;
			int reloadDuration;
			int reloadTime;
			int deathFrameCount;
		};
	}
}