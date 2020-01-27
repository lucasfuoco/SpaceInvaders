#pragma once
#include <iostream>
#include <spaceinvaders/sprites/saucer.hpp>

namespace SpaceInvaders {
	namespace Sprites {
		namespace Saucers {
			class Saucer2 : public SpaceInvaders::Sprites::Saucer {
			public:
				Saucer2();
				virtual ~Saucer2();
				virtual void ClearData(void) override;
			private:
				SpaceInvaders::SpriteBuffer* buffer1;
				SpaceInvaders::SpriteBuffer* buffer2;
			};
		}
	}
}