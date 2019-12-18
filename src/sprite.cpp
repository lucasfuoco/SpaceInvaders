#include <sprite.hpp>
#include <game.hpp>

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
	drawSpriteBuffer(buffer);
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

const QPoint Sprite::GetPosition(void) const {
	return this->position;
}

const QSize Sprite::GetSize(void) const {
	if (!spriteBuffer) {
		return QSize(0, 0);
	}

	return this->spriteBuffer->size;
}

void Sprite::drawSpriteBuffer(SpaceInvaders::Buffer* buffer) {
	for (int xIndex = 0; xIndex < spriteBuffer->size.width(); ++xIndex) {
		for (int yIndex = 0; yIndex < spriteBuffer->size.height(); ++yIndex) {
			if (
				spriteBuffer->data[yIndex * spriteBuffer->size.width() + xIndex] &&
				(spriteBuffer->size.height() - 1 + position.y() - yIndex) < buffer->size.height() &&
				(position.x() + xIndex) < buffer->size.width()
				)
			{
				buffer->data[(spriteBuffer->size.height() - 1 + position.y() - yIndex) * buffer->size.width() + (position.x() + xIndex)] = color;
			}
		}
	}
}

void Sprite::setSpriteBuffer(SpriteBuffer* buffer) {
	spriteBuffer = buffer;
}

void Sprite::setColor(uint32_t spriteColor) {
	if (color != spriteColor) {
		color = spriteColor;
	}
}