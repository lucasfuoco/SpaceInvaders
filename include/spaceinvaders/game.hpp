#pragma once
#include <boost/asio.hpp>
#include <vector>
#include <QtWidgets>
#include <spaceinvaders/color.hpp>
#include <spaceinvaders/sprites/saucers/saucer1.hpp>
#include <spaceinvaders/sprites/saucers/saucer2.hpp>
#include <spaceinvaders/sprites/saucers/saucer3.hpp>
#include <spaceinvaders/sprites/saucer_types.hpp>
#include <spaceinvaders/sprites/saucer.hpp>
#include <spaceinvaders/sprites/player.hpp>
#include <spaceinvaders/sprites/bullets/sharp_bullet.hpp>
#include <spaceinvaders/sprites/bullets/tri_bullet.hpp>
#include <spaceinvaders/sprites/bullets/di_bullet.hpp>
#include <spaceinvaders/sprites/bullet.hpp>
#include <spaceinvaders/sprites/text.hpp>
#include <spaceinvaders/controller.hpp>
#include <spaceinvaders/controllers/saucer_controller.hpp>
#include <spaceinvaders/controllers/player_controller.hpp>
#include <spaceinvaders/controllers/bullet_controller.hpp>
#include <spaceinvaders/sprite.hpp>
#include <spaceinvaders/shaders.hpp>
#include <qopenglext.h>
#include <iostream>

#define GAME_MAX_BULLETS_IN_FLIGHT 80


namespace SpaceInvaders {
	using namespace SpaceInvaders::Sprites;

	class Sprite;
	class Controller;

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

	class Game {
	public:
		Game(Shaders* shaders);
		virtual ~Game();
		void UpdateCommandBuffers(QOpenGLExtraFunctions* openGL);
		void OnGLInitialized(QOpenGLExtraFunctions* openGL);
		void Cleanup(QOpenGLExtraFunctions* openGL);
		void OnWheelEvent(QWheelEvent* wheelEvent);
		void OnKeyEvent(QKeyEvent* keyEvent);
		const Buffer* GetBuffer(void) const;
		const std::vector<SpaceInvaders::Sprites::Saucer*>* GetSaucers(void) const;
		SpaceInvaders::Sprites::Player* GetPlayer(void) const;
		std::vector<SpaceInvaders::Sprites::Bullet*>* GetPlayerBullets(void) const;
		std::vector<SpaceInvaders::Sprites::Bullet*>* GetSaucerBullets(void) const;
		const int GetPlayerBulletsInFlightCount(void) const;
		const int GetSaucerBulletsInFlightCount(void) const;
		void AddPlayerBulletsInFlight(int bulletCount);
		void AddSaucerBulletsInFlight(int bulletCount);
		void RemovePlayerBulletsInFlight(int bulletCount);
		void RemoveSaucerBulletsInFlight(int bulletCount);
		void AddScore(int scoreCount);
		const QSize* GetSaucerMatrix(void) const;
	private:
		void clearBuffer(uint32_t color);

		QOpenGLShaderProgram* spriteShaderProgram;
		std::vector<SpaceInvaders::Sprites::Saucer*>* saucers;
		std::vector<SpaceInvaders::Sprites::Bullet*>* playerBullets;
		std::vector<SpaceInvaders::Sprites::Bullet*>* saucerBullets;
		SpaceInvaders::Sprites::Player* player;
		SpaceInvaders::Sprites::Text* scoreText;
		SpaceInvaders::Sprites::Text* scoreValueText;
		int playerBulletsInFlightCount;
		int saucerBulletsInFlightCount;
		int spriteBufferLocation;
		int score;
		char scoreBuffer[4096];
		Buffer* buffer;
		GLuint texture;
		GLuint vertex;
		std::vector<SpaceInvaders::Controller*> controllers;
		QSize* saucerMatrix;
	};
}