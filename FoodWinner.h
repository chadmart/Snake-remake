#ifndef FOODWINNER_H
#define FOODWINNER_H

/*!\file FoodWinner.h
 * 
 * \brief Represents a FoodWinner piece.
 * 
 * \author Chad Martin
 * 
 * A daughter of the Food class. Represents a Linux Logo.
 * If Snake collides with FoodWinner, a victory screen will occur.
 */

#include "Food.h" //required due to inheritance
#include <QImage>
#include <QRect>

/*! \brief A FoodWinner piece
 * A daughter of the Food class. 
 * Represents a Linux Logo. 
 * If Snake collides with FoodWinner, a victory screen will occur.*/
class FoodWinner : public Food
{
	public:
		/*! Class Constructor - loads first image, moves to random location.
		 * Precondition: A new instance of game was created.
		 * Postcondition: A new piece of food is created with Linux logo image.*/
    		FoodWinner();		

		/*! Class Destructor - Does Nothing*/
    		~FoodWinner();

};

#endif

