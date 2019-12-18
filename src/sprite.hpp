#pragma once
#include <iostream>
#include <color.hpp>
#include <QtWidgets>

namespace SpaceInvaders {
	struct Buffer;

	struct SpriteBuffer {
		QSize size;
		uint8_t* data;
	};

	struct SpriteAnimation {
		bool loop = true;
		int frameCount = 0;
		int frameDuration = 0;
		int time = 0;
		std::vector<SpriteBuffer*> frames;
	};

	class Sprite {
	public:
		Sprite();
		virtual ~Sprite();
		virtual void UpdateSpriteBuffer(SpaceInvaders::Buffer* buffer);
		virtual void Cleanup(QOpenGLExtraFunctions* openGL);
		virtual void ClearData(void);
		void SetX(int x);
		void SetY(int y);
		const QPoint GetPosition(void) const;
		const QSize GetSize(void) const;
	protected:
		virtual void drawSpriteBuffer(SpaceInvaders::Buffer* buffer);
		void setSpriteBuffer(SpriteBuffer* buffer);
		void setColor(uint32_t spriteColor);

		QPoint position;
		SpriteAnimation animation;
	private:
		SpriteBuffer* spriteBuffer;
		uint32_t color;
	};
}