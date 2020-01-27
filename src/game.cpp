#include <spaceinvaders/game.hpp>

using namespace SpaceInvaders;

Game::Game(Shaders* shaders) :
	spriteShaderProgram(shaders->GetSprite()),
	saucers(new std::vector<SpaceInvaders::Sprites::Saucer*>()),
	playerBullets(new std::vector<SpaceInvaders::Sprites::Bullet*>()),
	saucerBullets(new std::vector<SpaceInvaders::Sprites::Bullet*>()),
	player(new SpaceInvaders::Sprites::Player()),
	scoreText(new SpaceInvaders::Sprites::Text()),
	scoreValueText(new SpaceInvaders::Sprites::Text()),
	playerBulletsInFlightCount(0),
	saucerBulletsInFlightCount(0),
	spriteBufferLocation(-1),
	score(0),
	scoreBuffer(),
	buffer(new Buffer()),
	texture(),
	vertex(),
	controllers(),
	saucerMatrix(new QSize(11, 5))
{
	buffer->size.setWidth(224);
	buffer->size.setHeight(256);

	for (int yIndex = 0; yIndex < 5; ++yIndex) {
		for (int xIndex = 0; xIndex < 11; ++xIndex) {
			switch (((5 - yIndex) / 2) + 1) {
			case SaucerTypes::Saucer1:
				saucers->push_back(new SpaceInvaders::Sprites::Saucers::Saucer1());
				break;
			case SaucerTypes::Saucer2:
				saucers->push_back(new SpaceInvaders::Sprites::Saucers::Saucer2());
				break;
			case SaucerTypes::Saucer3:
				saucers->push_back(new SpaceInvaders::Sprites::Saucers::Saucer3());
				break;
			default:
				saucers->push_back(new SpaceInvaders::Sprites::Saucers::Saucer1());
				break;
			}
	
			saucers->at(yIndex * 11 + xIndex)->SetX(16 * xIndex + 20);
			saucers->at(yIndex * 11 + xIndex)->SetY(17 * yIndex + 128);
		}
	}

	for (int i = 0; i < GAME_MAX_BULLETS_IN_FLIGHT; i++) {
		playerBullets->push_back(new SpaceInvaders::Sprites::Bullets::SharpBullet());
	}

	for (int i = 0; i < GAME_MAX_BULLETS_IN_FLIGHT; i++) {
		if (i % 2 == 0) {
			saucerBullets->push_back(new SpaceInvaders::Sprites::Bullets::DiBullet());
		}
		else {
			saucerBullets->push_back(new SpaceInvaders::Sprites::Bullets::TriBullet());
		}
	}

	scoreText->SetText("SCORE");
	scoreText->SetX(4);
	scoreText->SetY(buffer->size.height() - scoreText->GetSize().height() - 7);

	sprintf(
		scoreBuffer,
		"%i",
		score
	);
	scoreValueText->SetText(scoreBuffer);
	scoreValueText->SetX(38);
	scoreValueText->SetY(buffer->size.height() - scoreText->GetSize().height() - 7);

	controllers.push_back(new SpaceInvaders::Controllers::BulletController(this));
	controllers.push_back(new SpaceInvaders::Controllers::SaucerController(this));
	controllers.push_back(new SpaceInvaders::Controllers::PlayerController(this));
}

Game::~Game() {
	for (int i = 0; i < saucers->size(); i++) {
		delete saucers->at(i);
	}

	for (int i = 0; i < playerBullets->size(); i++) {
		delete playerBullets->at(i);
	}

	for (int i = 0; i < saucerBullets->size(); i++) {
		delete saucerBullets->at(i);
	}

	for (int i = 0; i < controllers.size(); i++) {
		delete controllers[i];
	}

	delete scoreValueText;
	delete scoreText;
	delete player;
	delete buffer;
	delete playerBullets;
	delete saucerBullets;
	delete saucers;
	delete saucerMatrix;
}

void Game::UpdateCommandBuffers(QOpenGLExtraFunctions* openGL) {
	spriteShaderProgram->bind();

	clearBuffer(Color::GetRGBToUInt32(0, 0, 0));

	// Score text
	scoreText->UpdateSpriteBuffer(buffer);

	// Score value text
	scoreValueText->UpdateSpriteBuffer(buffer);

	// Player
	player->UpdateSpriteBuffer(buffer);

	// Saucers
	for (int i = 0; i < saucers->size(); i++) {	
		saucers->at(i)->UpdateSpriteBuffer(buffer);
	}

	// Player Bullets
	for (int i = 0; i < playerBullets->size(); i++) {
		playerBullets->at(i)->UpdateSpriteBuffer(buffer);
	}

	// Saucer Bullets
	for (int i = 0; i < saucerBullets->size(); i++) {
		saucerBullets->at(i)->UpdateSpriteBuffer(buffer);
	}

	openGL->glTexSubImage2D(
		GL_TEXTURE_2D, 0, 0, 0,
		buffer->size.width(), buffer->size.height(),
		GL_RGBA, GL_UNSIGNED_INT_8_8_8_8,
		buffer->data
	);

	openGL->glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	// Controllers
	for (int i = 0; i < controllers.size(); i++) {
		controllers[i]->Think();
	}

	spriteShaderProgram->release();
}

void Game::OnGLInitialized(QOpenGLExtraFunctions* openGL) {
	spriteBufferLocation = spriteShaderProgram->uniformLocation("buffer");
	buffer->data = new uint32_t[buffer->size.width() * buffer->size.height()];

	spriteShaderProgram->bind();
	spriteShaderProgram->setUniformValue(spriteBufferLocation, 0);

	clearBuffer(Color::GetRGBToUInt32(0, 0, 0));
	openGL->glActiveTexture(GL_TEXTURE0);
	openGL->glGenTextures(1, &texture);
	openGL->glBindTexture(GL_TEXTURE_2D, texture);
	openGL->glTexImage2D(
		GL_TEXTURE_2D, 0, GL_RGB8, buffer->size.width(), buffer->size.height(), 0,
		GL_RGBA, GL_UNSIGNED_INT_8_8_8_8,
		buffer->data
	);
	openGL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	openGL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	openGL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	openGL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	openGL->glGenVertexArrays(1, &vertex);
	openGL->glBindVertexArray(vertex);

	spriteShaderProgram->release();
}

void Game::Cleanup(QOpenGLExtraFunctions* openGL) {
	player->Cleanup(openGL);

	for (int i = 0; i < saucers->size(); i++) {
		saucers->at(i)->Cleanup(openGL);
	}

	for (int i = 0; i < playerBullets->size(); i++) {
		playerBullets->at(i)->Cleanup(openGL);
	}

	for (int i = 0; i < saucerBullets->size(); i++) {
		saucerBullets->at(i)->Cleanup(openGL);
	}

	openGL->glDeleteTextures(1, &texture);
	openGL->glDeleteVertexArrays(1, &vertex);
	scoreText->ClearData();
	scoreValueText->ClearData();
	buffer->ClearData();
}

void Game::OnWheelEvent(QWheelEvent* wheelEvent) {
	if (wheelEvent->delta() < 0) {
		if (player->GetPosition().x() > 0) {
			player->SetX(player->GetPosition().x() - 6);
		}
	}
	else {
		if ((player->GetPosition().x() + player->GetSize().width()) < buffer->size.width()) {
			player->SetX(player->GetPosition().x() + 6);
		}
	}
}

void Game::OnKeyEvent(QKeyEvent* keyEvent) {
	switch (keyEvent->key()) {
	case Qt::Key_Space:
		player->Fire();
		break;
	default:
		break;
	}
}

const Buffer* Game::GetBuffer(void) const {
	return this->buffer;
}

const std::vector<SpaceInvaders::Sprites::Saucer*>* Game::GetSaucers(void) const {
	return this->saucers;
}

SpaceInvaders::Sprites::Player* Game::GetPlayer(void) const {
	return player;
}

std::vector<SpaceInvaders::Sprites::Bullet*>* Game::GetPlayerBullets(void) const {
	return this->playerBullets;
}

std::vector<SpaceInvaders::Sprites::Bullet*>* Game::GetSaucerBullets(void) const {
	return this->saucerBullets;
}

const int Game::GetPlayerBulletsInFlightCount(void) const {
	return this->playerBulletsInFlightCount;
}

const int Game::GetSaucerBulletsInFlightCount(void) const {
	return this->saucerBulletsInFlightCount;
}

void Game::AddPlayerBulletsInFlight(int bulletCount) {
	playerBulletsInFlightCount += bulletCount;
}

void Game::AddSaucerBulletsInFlight(int bulletCount) {
	saucerBulletsInFlightCount += bulletCount;
}

void Game::RemovePlayerBulletsInFlight(int bulletCount) {
	playerBulletsInFlightCount -= bulletCount;
}

void Game::RemoveSaucerBulletsInFlight(int bulletCount) {
	saucerBulletsInFlightCount -= bulletCount;
}

void Game::AddScore(int scoreCount) {
	score += scoreCount;
	sprintf(
		scoreBuffer,
		"%i",
		score
	);
	scoreValueText->SetText(scoreBuffer);
}

const QSize* Game::GetSaucerMatrix(void) const {
	return this->saucerMatrix;
}

void Game::clearBuffer(uint32_t color) {
	for (int i = 0; i < buffer->size.width() * buffer->size.height(); ++i) {
		buffer->data[i] = color;
	}
}