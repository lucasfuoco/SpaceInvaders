#pragma once
#include <iostream>
#include <sprite.hpp>
#include <color.hpp>

namespace SpaceInvaders {
	namespace Sprites {
		class PlayerBullet : public SpaceInvaders::Sprite {
		public:
			PlayerBullet();
			virtual ~PlayerBullet();
			virtual void ClearData(void) override;
			int GetDirection(void);
			void SetDirection(int direction);
			void ResetPosition(void);
		private:
			SpaceInvaders::SpriteBuffer* buffer;
			int direction;
		};
	}
}