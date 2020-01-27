#pragma once
#include <iostream>
#include <spaceinvaders/sprites/saucer.hpp>

namespace SpaceInvaders {
	namespace Sprites {
		namespace Saucers {
			class Saucer3 : public SpaceInvaders::Sprites::Saucer {
			public:
				Saucer3();
				virtual ~Saucer3();
				virtual void ClearData(void) override;
			private:
				SpaceInvaders::SpriteBuffer* buffer1;
				SpaceInvaders::SpriteBuffer* buffer2;
			};
		}
	}
}