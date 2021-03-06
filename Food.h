#ifndef FOOD_H
#define FOOD_H

/*!\file Food.h
 * 
 * \brief Represents a Food piece.
 * 
 * \author Chad Martin
 * 
 * The parent of all food pieces. If not inherited, Food represents a red or green Apple Logo.
 */

#include <QImage>
#include <QRect>
#include <stdlib.h> // C Standard General Utilities Library (required for rand() function)

/*! \brief A Food piece
 * The parent of all food pieces. 
 * If not inherited, Food represents a red or green Apple Logo.*/
class Food
{
	// Defining Public Functions (Methods)
  	public:
		/*! \brief Class Constructor - loads first image, moves to random location.
		 * Precondition: A new instance of game was created.
		 * Postcondition: A new piece of food is created with default image.*/
    		Food();
		
		/*! \brief Class Destructor - Does Nothing*/
    		~Food();

		/*! \brief Draws Food in a random location. 
		 * Precondition: The Snake head collided with a piece of Food or Food cheat code key was pressed.
		 * Postcondition: Food is moved to a random location on the screen which is not on top of otherFood.
		 * \param *otherFood The other piece of Food on the screen*/ 
		void moveFood(Food *otherFood);

		/*! \brief Draws Food in a random location.
		 * Precondition: The Snake head collided with a piece of Food or Food cheat code key was pressed.
		 * Postcondition: Food is moved to a random location on the screen which is not on top of otherFood.
		 * \param *otherFood The other piece of Food on the screen.
		 * \param whichFood The integer switch between Food images.*/ 
		void moveFood(Food *otherFood, int whichFood);

		/*! \brief Draws Food in a random location.
		 * Precondition: The Snake head collided with a piece of Food or Food cheat code key was pressed.
		 * Postcondition: Food is moved to a random location on the screen which is not on top of otherFood.
		 * \param whichFood The integer switch between Food images.*/  
		void moveFood(int whichFood);

		/*! \brief Picks a random location to move Food to, but does not move Food.
		 * Precondition: Food needs to be moved to a new location.
		 * Postcondition: New location is picked for Food to move to.*/
		void pickLocation();

		/*! \brief Returns rect of Food.
		 * Precondition: Any collision detection or paint event that involes the Food occured.
		 * Postcondition: The Qrect of the Food is returned.
		 * \return The rect of Food.*/
    		QRect getRect();

		/*! \brief Returns image of Food.
		 * Precondition: Instance of Game called a paint event and the game is started.
		 * Postcondition: The image of the Food will be painted on the screen.
		 * \return Image of Food.*/
    		QImage & getImage();

	protected:

		/*! \brief The x position of Food.*/
		int x;

		/*! \brief The y position of Food.*/
		int y;

		/*! \brief The QImage of Food.*/
    		QImage image;

		/*! \brief The QRect of Food.*/
    		QRect rect;

};

#endif

