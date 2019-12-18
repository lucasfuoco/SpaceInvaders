#pragma once
#include <iostream>
#include <vector>
#include <QtWidgets>
#include <color.hpp>
#include <sprites/saucers/saucer1.hpp>
#include <sprites/saucers/saucer2.hpp>
#include <sprites/saucers/saucer3.hpp>
#include <sprites/saucer.hpp>
#include <sprites/player.hpp>
#include <sprites/bullet.hpp>
#include <sprite.hpp>
#include <shaders.hpp>

#define GAME_MAX_BULLETS_IN_FLIGHT 128

namespace SpaceInvaders {
	class Sprite;

	struct Buffer {
		QSize size = QSize();
		uint32_t* data;

		void ClearData(void) {
			if (data) {
				delete[] data;
				data = nullptr;
			}
		}
	};

	enum SaucerTypes {
		Saucer1 = 0,
		Saucer2 = 1,
		Saucer3 = 2
	};

	class Game {
	public:
		Game(Shaders* shaders);
		virtual ~Game();
		void UpdateCommandBuffers(QOpenGLExtraFunctions* openGL);
		void OnGLInitialized(QOpenGLExtraFunctions* openGL);
		void Cleanup(QOpenGLExtraFunctions* openGL);
		void OnWheelEvent(QWheelEvent* wheelEvent);
		void OnKeyEvent(QKeyEvent* keyEvent);
	private:
		void clearBuffer(uint32_t color);
		bool getSpritesAreOverlaping(
			SpaceInvaders::Sprite* spriteA,
			SpaceInvaders::Sprite* spriteB
		);

		QOpenGLShaderProgram* spriteShaderProgram;
		std::vector<SpaceInvaders::Sprites::Saucer*> saucers;
		std::vector<SpaceInvaders::Sprites::Bullet*> bullets;
		SpaceInvaders::Sprites::Player* player;
		int saucerCount;
		int bulletsInFlightCount;
		std::vector<int> deathCounters;
		int spriteBufferLocation;
		Buffer* buffer;
		GLuint texture;
		GLuint vertex;
	};
}