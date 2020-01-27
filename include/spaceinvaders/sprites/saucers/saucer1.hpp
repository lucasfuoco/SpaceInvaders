#pragma once
#include <iostream>
#include <spaceinvaders/sprites/saucer.hpp>

namespace SpaceInvaders {
	namespace Sprites {
		namespace Saucers {
			class Saucer1 : public SpaceInvaders::Sprites::Saucer {
			public:
				Saucer1();
				virtual ~Saucer1();
				virtual void ClearData(void) override;
			private:
				SpaceInvaders::SpriteBuffer* buffer1;
				SpaceInvaders::SpriteBuffer* buffer2;
			};
		}
	}
}