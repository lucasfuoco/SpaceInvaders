#pragma once
#include <iostream>
#include <sprite.hpp>

namespace SpaceInvaders {
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
		protected:
			virtual void think(void);
			void setDeathPoint(int point);

			SpaceInvaders::SpriteBuffer* deathBuffer;
		private:
			bool isDead;
			int deathPoint;
		};
	}
}