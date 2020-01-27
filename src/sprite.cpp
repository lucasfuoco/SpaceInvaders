#include <spaceinvaders/sprite.hpp>
#include <spaceinvaders/game.hpp>

using namespace SpaceInvaders;

Sprite::Sprite() :
	position(),
	color(0),
	animation(),
	spriteBuffer(nullptr)
{

}

Sprite::~Sprite() {

}

void Sprite::UpdateSpriteBuffer(SpaceInvaders::Buffer* buffer) {	
	drawSpriteBuffer(buffer, position.x(), position.y());
}

void Sprite::Cleanup(QOpenGLExtraFunctions* openGL) {
	ClearData();
}

void Sprite::ClearData(void) {
	
}

void Sprite::SetX(int x) {
	if (position.x() != x) {
		position.setX(x);
	}
}

void Sprite::SetY(int y) {
	if (position.y() != y) {
		position.setY(y);
	}
}

void Sprite::SetWidth(int width) {
	if (spriteBuffer->size.width() != width) {
		spriteBuffer->size.setWidth(width);
	}
}

void Sprite::SetHeight(int height) {
	if (spriteBuffer->size.height() != height) {
		spriteBuffer->size.setHeight(height);
	}
}

const QPoint Sprite::GetPosition(void) const {
	return this->position;
}

const QSize Sprite::GetSize(void) const {
	if (!spriteBuffer) {
		return QSize(0, 0);
	}

	return this->spriteBuffer->size;
}

void Sprite::drawSpriteBuffer(SpaceInvaders::Buffer* buffer, int x, int y) {
	for (int xIndex = 0; xIndex < spriteBuffer->size.width(); ++xIndex) {
		for (int yIndex = 0; yIndex < spriteBuffer->size.height(); ++yIndex) {
			if (
				spriteBuffer->data[yIndex * spriteBuffer->size.width() + xIndex] &&
				(spriteBuffer->size.height() - 1 + y - yIndex) < buffer->size.height() &&
				(x + xIndex) < buffer->size.width()
				)
			{
				buffer->data[(spriteBuffer->size.height() - 1 + y - yIndex) * buffer->size.width() + (x + xIndex)] = color;
			}
		}
	}
}

void Sprite::setSpriteBuffer(SpriteBuffer* buffer) {
	spriteBuffer = buffer;
}

SpriteBuffer* Sprite::getSpriteBuffer(void) {
	return spriteBuffer;
}

void Sprite::setColor(uint32_t spriteColor) {
	if (color != spriteColor) {
		color = spriteColor;
	}
}