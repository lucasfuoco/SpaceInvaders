#include <game.hpp>

using namespace SpaceInvaders;

Game::Game(Shaders* shaders) :
	spriteShaderProgram(shaders->GetSprite()),
	saucers(new std::vector<SpaceInvaders::Sprites::Saucer*>()),
	playerBullets(new std::vector<SpaceInvaders::Sprites::PlayerBullet*>()),
	player(new SpaceInvaders::Sprites::Player()),
	scoreText(new SpaceInvaders::Sprites::Text()),
	scoreValueText(new SpaceInvaders::Sprites::Text()),
	bulletsInFlightCount(0),
	deathCounters(new std::vector<int>()),
	spriteBufferLocation(-1),
	score(0),
	scoreBuffer(),
	buffer(new Buffer()),
	texture(),
	vertex(),
	controllers()
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
		playerBullets->push_back(new SpaceInvaders::Sprites::PlayerBullet());
	}

	for (int i = 0; i < saucers->size(); i++) {
		deathCounters->push_back(10);
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

	for (int i = 0; i < controllers.size(); i++) {
		delete controllers[i];
	}

	delete deathCounters;
	delete scoreValueText;
	delete scoreText;
	delete player;
	delete buffer;
	delete playerBullets;
	delete saucers;
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
		if (!deathCounters->at(i)) {
			continue;
		}

		saucers->at(i)->UpdateSpriteBuffer(buffer);
	}

	// Bullets
	for (int i = 0; i < playerBullets->size(); i++) {
		playerBullets->at(i)->UpdateSpriteBuffer(buffer);
	}

	openGL->glTexSubImage2D(
		GL_TEXTURE_2D, 0, 0, 0,
		buffer->size.width(), buffer->size.height(),
		GL_RGBA, GL_UNSIGNED_INT_8_8_8_8,
		buffer->data
	);

	openGL->glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


	// Simulate bullets
	for (int bulletIndex = 0; bulletIndex < bulletsInFlightCount;) {
		playerBullets->at(bulletIndex)->SetY(playerBullets->at(bulletIndex)->GetPosition().y() + playerBullets->at(bulletIndex)->GetDirection());
		if (playerBullets->at(bulletIndex)->GetPosition().y() >= buffer->size.height())
		{
			playerBullets->at(bulletIndex)->ResetPosition();
			std::rotate(playerBullets->begin() + bulletIndex, playerBullets->begin() + bulletIndex + 1, playerBullets->end());
			bulletsInFlightCount -= 1;
			continue;
		}

		// Check if saucers are hit
		for (int saucerIndex = 0; saucerIndex < saucers->size(); ++saucerIndex) {
			if (saucers->at(saucerIndex)->GetIsDead()) {
				continue;
			}

			if (getSpritesAreOverlaping(playerBullets->at(bulletIndex), saucers->at(saucerIndex))) {
				score += saucers->at(saucerIndex)->GetDeathPoint();
				sprintf(
					scoreBuffer,
					"%i",
					score
				);
				scoreValueText->SetText(scoreBuffer);

				saucers->at(saucerIndex)->Die();

				playerBullets->at(bulletIndex)->ResetPosition();
				std::rotate(playerBullets->begin() + bulletIndex, playerBullets->begin() + bulletIndex + 1, playerBullets->end());
				bulletsInFlightCount -= 1;
				continue;
			}
		}

		bulletIndex += 1;
	}

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

const std::vector<SpaceInvaders::Sprites::Saucer*>* Game::GetSaucers(void) const {
	return this->saucers;
}

SpaceInvaders::Sprites::Player* Game::GetPlayer(void) const {
	return player;
}

const std::vector<SpaceInvaders::Sprites::PlayerBullet*>* Game::GetPlayerBullets(void) const {
	return this->playerBullets;
}

const int Game::GetBulletsInFlightCount(void) const {
	return this->bulletsInFlightCount;
}

void Game::AddBulletsInFlight(int bulletCount) {
	bulletsInFlightCount += bulletCount;
}

std::vector<int>* Game::GetDeathCounters(void) {
	return this->deathCounters;
}

void Game::clearBuffer(uint32_t color) {
	for (int i = 0; i < buffer->size.width() * buffer->size.height(); ++i) {
		buffer->data[i] = color;
	}
}

bool Game::getSpritesAreOverlaping(
	SpaceInvaders::Sprite* spriteA,
	SpaceInvaders::Sprite* spriteB
)
{
	if (
		(spriteA->GetPosition().x() < (spriteB->GetPosition().x() + spriteB->GetSize().width())) && ((spriteA->GetPosition().x() + spriteA->GetSize().width()) > spriteB->GetPosition().x()) &&
		(spriteA->GetPosition().y() < (spriteB->GetPosition().y() + spriteB->GetSize().height())) && ((spriteA->GetPosition().y() + spriteA->GetSize().height()) > spriteB->GetPosition().y())
	) {
		return true;
	}

	return false;
}