#include <game.hpp>

using namespace SpaceInvaders;

Game::Game(Shaders* shaders) :
	spriteShaderProgram(shaders->GetSprite()),
	saucers(),
	playerBullets(),
	player(new SpaceInvaders::Sprites::Player()),
	scoreText(new SpaceInvaders::Sprites::Text()),
	scoreValueText(new SpaceInvaders::Sprites::Text()),
	saucerCount(55),
	bulletsInFlightCount(0),
	deathCounters(),
	spriteBufferLocation(-1),
	score(0),
	scoreBuffer(),
	buffer(new Buffer()),
	texture(),
	vertex()
{
	buffer->size.setWidth(224);
	buffer->size.setHeight(256);

	for (int yIndex = 0; yIndex < 5; ++yIndex) {
		for (int xIndex = 0; xIndex < 11; ++xIndex) {
			switch (((5 - yIndex) / 2) + 1) {
			case SaucerTypes::Saucer1:
				saucers.push_back(new SpaceInvaders::Sprites::Saucers::Saucer1());
				break;
			case SaucerTypes::Saucer2:
				saucers.push_back(new SpaceInvaders::Sprites::Saucers::Saucer2());
				break;
			case SaucerTypes::Saucer3:
				saucers.push_back(new SpaceInvaders::Sprites::Saucers::Saucer3());
				break;
			default:
				saucers.push_back(new SpaceInvaders::Sprites::Saucers::Saucer1());
				break;
			}
	
			saucers[yIndex * 11 + xIndex]->SetX(16 * xIndex + 20);
			saucers[yIndex * 11 + xIndex]->SetY(17 * yIndex + 128);
		}
	}

	for (int i = 0; i < GAME_MAX_BULLETS_IN_FLIGHT; i++) {
		playerBullets.push_back(new SpaceInvaders::Sprites::PlayerBullet());
	}

	for (int i = 0; i < saucerCount; i++) {
		deathCounters.push_back(10);
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
}

Game::~Game() {
	for (int i = 0; i < saucers.size(); i++) {
		delete saucers[i];
	}

	for (int i = 0; i < playerBullets.size(); i++) {
		delete playerBullets[i];
	}

	delete scoreValueText;
	delete scoreText;
	delete player;
	delete buffer;
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
	for (int i = 0; i < saucers.size(); i++) {
		if (!deathCounters[i]) {
			continue;
		}

		saucers[i]->UpdateSpriteBuffer(buffer);
	}

	// Bullets
	for (int i = 0; i < playerBullets.size(); i++) {
		playerBullets[i]->UpdateSpriteBuffer(buffer);
	}

	openGL->glTexSubImage2D(
		GL_TEXTURE_2D, 0, 0, 0,
		buffer->size.width(), buffer->size.height(),
		GL_RGBA, GL_UNSIGNED_INT_8_8_8_8,
		buffer->data
	);

	openGL->glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	// Simulate saucers
	for (int saucerIndex = 0; saucerIndex < saucerCount; ++saucerIndex) {
		if (saucers[saucerIndex]->GetIsDead() && deathCounters[saucerIndex]) {
			deathCounters[saucerIndex] -= 1;
		}
	}

	// Simulate bullets
	for (int bulletIndex = 0; bulletIndex < bulletsInFlightCount;) {
		playerBullets[bulletIndex]->SetY(playerBullets[bulletIndex]->GetPosition().y() + playerBullets[bulletIndex]->GetDirection());
		if (playerBullets[bulletIndex]->GetPosition().y() >= buffer->size.height())
		{
			playerBullets[bulletIndex]->ResetPosition();
			std::rotate(playerBullets.begin() + bulletIndex, playerBullets.begin() + bulletIndex + 1, playerBullets.end());
			bulletsInFlightCount -= 1;
			continue;
		}

		// Check if saucers are hit
		for (int saucerIndex = 0; saucerIndex < saucerCount; ++saucerIndex) {
			if (saucers[saucerIndex]->GetIsDead()) {
				continue;
			}

			if (getSpritesAreOverlaping(playerBullets[bulletIndex], saucers[saucerIndex])) {
				score += saucers[saucerIndex]->GetDeathPoint();
				sprintf(
					scoreBuffer,
					"%i",
					score
				);
				scoreValueText->SetText(scoreBuffer);

				saucers[saucerIndex]->Die();

				playerBullets[bulletIndex]->ResetPosition();
				std::rotate(playerBullets.begin() + bulletIndex, playerBullets.begin() + bulletIndex + 1, playerBullets.end());
				bulletsInFlightCount -= 1;
				continue;
			}
		}

		bulletIndex += 1;
	}

	// Process events
	if (player->GetIsFiring() && (bulletsInFlightCount < GAME_MAX_BULLETS_IN_FLIGHT)) {
  		playerBullets[bulletsInFlightCount]->SetX(player->GetPosition().x() + (player->GetSize().width() / 2));
		playerBullets[bulletsInFlightCount]->SetY(player->GetPosition().y() + player->GetSize().height());
		playerBullets[bulletsInFlightCount]->SetDirection(4);
		bulletsInFlightCount += 1;

		player->Reload();
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
	for (int i = 0; i < saucers.size(); i++) {
		saucers[i]->Cleanup(openGL);
	}

	for (int i = 0; i < playerBullets.size(); i++) {
		playerBullets[i]->Cleanup(openGL);
	}

	openGL->glDeleteTextures(1, &texture);
	openGL->glDeleteVertexArrays(1, &vertex);
	buffer->ClearData();
}

void Game::OnWheelEvent(QWheelEvent* wheelEvent) {
	if (wheelEvent->delta() < 0) {
		if (player->GetPosition().x() > 0) {
			player->SetX(player->GetPosition().x() - 5);
		}
	}
	else {
		if ((player->GetPosition().x() + player->GetSize().width()) < buffer->size.width()) {
			player->SetX(player->GetPosition().x() + 5);
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