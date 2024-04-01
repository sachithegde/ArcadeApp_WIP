
#ifndef INPUT_INPUTCONTROLLER_H_
#define INPUT_INPUTCONTROLLER_H_

#include "InputAction.h"

class GameController;

class InputController
{
public:

	InputController();
	void Init(InputAction quitAction);
	void Update(uint32_t dt);
	void SetGameController(GameController* controller);

private:
	InputAction mQuit;
	GameController* mnoptrCurrentController;
};

#endif 
