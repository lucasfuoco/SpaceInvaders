#include <sprites/bullets/sharp_bullet.hpp>

using namespace SpaceInvaders::Sprites::Bullets;

SharpBullet::SharpBullet() : SpaceInvaders::Sprites::Bullet(),
	buffer(new SpaceInvaders::SpriteBuffer())
{
	buffer->size.setWidth(1);
	buffer->size.setHeight(3);
	buffer->data = new uint8_t[3]
	{
		1, // @
		1, // @
		1  // @
	};

	position.setX(1000);
	position.setY(1000);

	setColor(Color::GetRGBToUInt32(255, 244, 182));
	setSpriteBuffer(buffer);
}

SharpBullet::~SharpBullet() {
	delete buffer;
}

void SharpBullet::ClearData(void) {
	if (buffer) {
		delete[] buffer->data;
		buffer->data = nullptr;
	}
}