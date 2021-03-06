/*!\file SpecialFood.cpp
 * 
 * \brief Represents a SpecialFood piece.
 * 
 * \author Chad Martin
 * 
 * A daughter of the Food class. Represents a Windows 8 Logo. 
 * If Snake collides with SpecialFood, a special game over will occur (BSOD).
 */

#include "SpecialFood.h"

/*! Class Constructor - loads first image, moves to random location.
 * Precondition: A new instance of game was created.
 * Postcondition: A new piece of food is created with Windows 8 logo image.*/
SpecialFood::SpecialFood():
	Food()
{

  	image.load("windows8.png");

  	rect = image.rect();

	pickLocation(); // Picks a random location to move Food

	rect.moveTo(x,y); // Moves Food to location
}

/*! Class Destructor - Does Nothing*/
SpecialFood::~SpecialFood() 
{
  	
}

