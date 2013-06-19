#ifndef SPECIALFOOD_H
#define SPECIALFOOD_H

/*!\file SpecialFood.h
 * 
 * \brief Represents a SpecialFood piece.
 * 
 * \author Chad Martin
 * 
 * A daughter of the Food class. Represents a Windows 8 Logo. 
 * If Snake collides with SpecialFood, a special game over will occur (BSOD).
 */

#include "Food.h" //required due to inheritance
#include <QImage>
#include <QRect>

/*! \brief A SpecialFood piece
 * A daughter of the Food class. 
 * Represents a Windows 8 Logo. 
 * If Snake collides with SpecialFood, a special game over will occur (BSOD).*/
class SpecialFood : public Food
{
	public:
		/*! Class Constructor - loads first image, moves to random location.
		 * Precondition: A new instance of game was created.
		 * Postcondition: A new piece of food is created with Windows 8 logo image.*/
    		SpecialFood();

		/*! Class Destructor - Does Nothing*/
    		~SpecialFood();

};

#endif

