#pragma once
#include <iostream>
#include <spaceinvaders/sprite.hpp>
#include <spaceinvaders/color.hpp>

namespace SpaceInvaders {
	namespace Sprites {
		class Text : public SpaceInvaders::Sprite {
		public:
			Text();
			virtual ~Text();
			virtual void ClearData(void) override;
			virtual void UpdateSpriteBuffer(SpaceInvaders::Buffer* buffer) override;
			virtual void SetText(const char* text);
		protected:
			virtual void drawTextBuffer(SpaceInvaders::Buffer* buffer, const char* text);
		private:
			SpaceInvaders::SpriteBuffer* labelBuffer;
			SpaceInvaders::SpriteBuffer* spriteBuffer;
			const char* label;
			int stride;
		};
	}
}