
#include "ArcadeScene.h"
#include "../Graphics/Screen.h"
#include "../Input/GameController.h"//gamecontroller
#include <iostream>
#include "../App/App.h"
#include "GameScene.h"
#include "../Games/BreakOut/BreakOut.h"
#include "NotImplementedScene.h"
#include "../Scenes/Pacman/PacmanStartScene.h"

ArcadeScene::ArcadeScene():ButtonOptionsScene({ "Break Out!", "Pac-man"}, Color::Cyan())
{

}

void ArcadeScene::Init()
{

	std::vector<Button::ButtonAction> actions;

	

	actions.push_back([this]{
		App::Singleton().PushScene(GetScene(BREAK_OUT));
	});

	

	actions.push_back([this]{
		App::Singleton().PushScene(GetScene(PACMAN));
	});

	SetButtonActions(actions);

	ButtonOptionsScene::Init();
}

void ArcadeScene::Update(uint32_t dt)
{
}

void ArcadeScene::Draw(Screen& theScreen)
{
	ButtonOptionsScene::Draw(theScreen);
}

const std::string& ArcadeScene::GetSceneName() const
{
	static std::string sceneName = "Arcade";
	return sceneName;
}


std::unique_ptr<Scene> ArcadeScene::GetScene(eGame game)
{
	switch(game)
	{
		case TETRIS:
		{

		}
		break;

		case BREAK_OUT:
		{
			std::unique_ptr<BreakOut> breakoutGame = std::make_unique<BreakOut>();

			std::unique_ptr<GameScene> breakoutScene = std::make_unique<GameScene>(std::move(breakoutGame));

			return breakoutScene;
		}
		break;

		case ASTEROIDS:
		{

		}
		break;

		case PACMAN:
		{
			return std::make_unique<PacmanStartScene>();
		}
		break;
	}

	std::unique_ptr<Scene> notImplementedScene = std::make_unique<NotImplementedScene>();

	return notImplementedScene;
}
