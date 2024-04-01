#ifndef GAMES_PACMAN_PACMANGAMEUTILS_H_
#define GAMES_PACMAN_PACMANGAMEUTILS_H_


#include "../../Utils/Vec2D.h"
#include <vector>

static const int PACMAN_MOVEMENT_SPEED = 50;
static const int GHOST_MOVEMENT_SPEED = 45;
static const int GHOST_VULNERABLE_MOVEMENT_SPEED = 25;
static const int GHOST_BACK_TO_PEN_SPEED = 100;


enum PacmanMovement
{
	PACMAN_MOVEMENT_NONE = 0,
	PACMAN_MOVEMENT_UP,
	PACMAN_MOVEMENT_LEFT,
	PACMAN_MOVEMENT_DOWN,
	PACMAN_MOVEMENT_RIGHT
};

Vec2D GetMovementVector(PacmanMovement direction);
PacmanMovement GetOppositeDirection(PacmanMovement direction);
std::vector<PacmanMovement> GetPerpendicularMovements(PacmanMovement direction);
std::vector<PacmanMovement> GetOtherDirections(PacmanMovement direction);


#endif 
