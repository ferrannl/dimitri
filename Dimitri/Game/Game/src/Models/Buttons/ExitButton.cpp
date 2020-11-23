#include "ExitButton.h"

Game::Models::Buttons::ExitButton::ExitButton(int x, int y, int z, int height, int width, Game::Enums::StateEnum state, int scene_height, Graphics::Models::Center center) : Game::Models::Button(x, y, z, height, width, state, scene_height, center)
{
}

void Game::Models::Buttons::ExitButton::interact(Controllers::LevelController* ctrl)
{
	exit(0);
}