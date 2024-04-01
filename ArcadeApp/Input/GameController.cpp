
#include "GameController.h"
#include "SDL.h"

GameController::GameController():mMouseMovedAction(nullptr)
{

}

InputAction GameController::GetActionForKey(InputKey key)
{
	for(const auto& buttonAction: mButtonActions)
	{
		if(key == buttonAction.key)
		{
			return buttonAction.action;
		}
	}

	return [](uint32_t, InputState){};
}

void GameController::AddInputActionForKey(const ButtonAction& buttonAction)
{
	mButtonActions.push_back(buttonAction);
}

void GameController::ClearAll()
{
	mButtonActions.clear();
}

bool GameController::IsPressed(InputState state)
{
	return state == SDL_PRESSED;
}

bool GameController::IsReleased(InputState state)
{
	return state == SDL_RELEASED;
}

InputKey GameController::ActionKey()
{
	return static_cast<InputKey>(SDLK_a);
}

InputKey GameController::CancelKey()
{
	return static_cast<InputKey>(SDLK_s);
}

InputKey GameController::LeftKey()
{
	return static_cast<InputKey>(SDLK_LEFT);
}

InputKey GameController::RightKey()
{
	return static_cast<InputKey>(SDLK_RIGHT);
}

InputKey GameController::DownKey()
{
	return static_cast<InputKey>(SDLK_DOWN);
}

InputKey GameController::UpKey()
{
	return static_cast<InputKey>(SDLK_UP);
}


MouseInputAction GameController::GetMouseButtonActionForMouseButton(MouseButton button)
{
	for(const auto& buttonAction: mMouseButtonActions)
	{
		if(button == buttonAction.mouseButton)
		{
			return buttonAction.mouseInputAction;
		}
	}

	return [](InputState state, const MousePosition&pos){};
}

void GameController::AddMouseButtonAction(const MouseButtonAction& mouseButtonAction)
{
	mMouseButtonActions.push_back(mouseButtonAction);
}

MouseButton GameController::LeftMouseButton()
{
	return static_cast<MouseButton>(SDL_BUTTON_LEFT);
}

MouseButton GameController::RightMouseButton()
{
	return static_cast<MouseButton>(SDL_BUTTON_RIGHT);
}
