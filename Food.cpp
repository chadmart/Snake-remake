/*!\file Food.cpp
 * 
 * \brief Represents a Food piece.
 * 
 * \author Chad Martin
 * 
 * The parent of all food pieces. If not inherited, Food represents a red or green Apple Logo.
 */
#include "Food.h"

/*! \brief Class Constructor - loads first image, moves to random location.
 * Precondition: A new instance of game was created.
 * Postcondition: A new piece of food is created with default image.*/
Food::Food()
{

  	image.load("food1.png");

  	rect = image.rect();

	pickLocation(); //Picks a random location to move Food

	rect.moveTo(x,y); // Moves Food to location
}

/*! \brief Class Destructor - Does Nothing*/
Food::~Food() 
{

}

/*! \brief Draws Food in a random location. 
 * Precondition: The Snake head collided with a piece of Food or Food cheat code key was pressed.
 * Postcondition: Food is moved to a random location on the screen which is not on top of otherFood.
 * \param *otherFood The other piece of Food on the screen.*/ 
void Food::moveFood(Food *otherFood)
{
	do{
		pickLocation(); //Picks a random location to move Food to

		rect.moveTo(x, y); //moves Food to chosen location

	/* Resovles illegal food placement issues */
	}while(rect.intersects(otherFood->getRect())); // NO SANDWICHES ALLOWED!!!!

}

/*! \brief Draws Food in a random location.
 * Precondition: The Snake head collided with a piece of Food or Food cheat code key was pressed.
 * Postcondition: Food is moved to a random location on the screen which is not on top of otherFood.
 * \param *otherFood The other piece of Food on the screen.
 * \param whichFood The integer switch between Food images.*/ 
void Food::moveFood(Food *otherFood, int whichFood)
{
	do{
		pickLocation(); //Picks a random location to move Food to

		//switches between images
		if(whichFood == 0)
		{
	  		image.load("food1.png");
		}
		if(whichFood == 1) 
		{
	  		image.load("food2.png");
		}

		rect.moveTo(x, y); //moves Food to chosen location

	/* Resovles illegal food placement issues */
	}while(rect.intersects(otherFood->getRect()));  // NO SANDWICHES ALLOWED!!!!
}

/*! \brief Draws Food in a random location.
 * Precondition: The Snake head collided with a piece of Food or Food cheat code key was pressed.
 * Postcondition: Food is moved to a random location on the screen which is not on top of otherFood.
 * \param whichFood The integer switch between Food images.*/  
void Food::moveFood(int whichFood)
{

	pickLocation(); //Picks a random location to move Food to
  	
	//switches between images
	if(whichFood == 0)
	{
  		image.load("food1.png");
	}
	if(whichFood == 1) 
	{
  		image.load("food2.png");
	}

	rect.moveTo(x, y);//moves Food to chosen location
}

/*! \brief Picks a random location to move Food to, but does not move Food.
 * Precondition: Food needs to be moved to a new location.
 * Postcondition: New location is picked for Food to move to.*/
void Food::pickLocation()
{
	x = ((rand() % 16)*25)+28; //picks random x position to spawn food
	y = ((rand() % 20)*25)+150; //picks random y position to spawn food
}

/*! \brief Returns rect of Food.
 * Precondition: Any collision detection or paint event that involes the Food occured.
 * Postcondition: The Qrect of the Food is returned.
 * \return The rect of Food.*/
QRect Food::getRect()
{
  return rect;
}

/*! \brief Returns image of Food.
 * Precondition: Instance of Game called a paint event and the game is started.
 * Postcondition: The image of the Food will be painted on the screen.
 * \return Image of Food.*/
QImage & Food::getImage()
{
  return image;
}

