#include <controllers/player_controller.hpp>

using namespace SpaceInvaders::Controllers;

PlayerController::PlayerController(SpaceInvaders::Game* game) : SpaceInvaders::Controller(game) {

}

PlayerController::~PlayerController() {

}

void PlayerController::Think(void) {
	if (game->GetPlayer()->GetIsFiring() && (game->GetBulletsInFlightCount() < GAME_MAX_BULLETS_IN_FLIGHT)) {
		game->GetPlayerBullets()->at(game->GetBulletsInFlightCount())->SetX(game->GetPlayer()->GetPosition().x() + (game->GetPlayer()->GetSize().width() / 2));
		game->GetPlayerBullets()->at(game->GetBulletsInFlightCount())->SetY(game->GetPlayer()->GetPosition().y() + game->GetPlayer()->GetSize().height());
		game->GetPlayerBullets()->at(game->GetBulletsInFlightCount())->SetDirection(4);
		game->AddBulletsInFlight(1);

		game->GetPlayer()->Reload();
	}

	SpaceInvaders::Controller::Think();
}