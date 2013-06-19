/*!\file SnakeBlock.cpp
 * 
 * \brief Represents the SnakeBlock.
 * 
 * \author Chad Martin
 * 
 * This class represents one block of the Snake.
 */

#include "SnakeBlock.h"

/*! \brief Class Constructor - Creates one SnakeBlock at the given postion
 * with the specified image and initializes the data members to default values.
 * Precondition: A new game was created or the Snake is growing bigger.
 * Postcondition: A new Snakeblock is created and added to the Snake.
 * \param xCoord x position to place SnakeBlock.
 * \param yCoord y position to place SnakeBlock.
 * \param imgSelect Chooses between the different SnakeBlock images.*/ 
SnakeBlock::SnakeBlock(int xCoord, int yCoord, int imgSelect)
{
	// Setting class variables	
	x = xCoord; // Initializes x coordinate to requested coordinate
	y = yCoord; // Initializes y coordinate to requested coordinate
	px = x; // Initializes px coordinate to x coordinate
	py = y; // Initializes yx coordinate to y coordinate
	
	// Selects and loads requested image
	if(imgSelect == 0)
	{
  		image.load("snakeblockleft.png");
	}
	if(imgSelect == 1) 
	{
  		image.load("snakeblock1.png");
	}
	if(imgSelect == 2) 
	{
  		image.load("snakeblock2.png");
	}

  	rect = image.rect();
  	rect.translate(x, y); //moves SnakeBlock to requested position
}

/*! \brief Class Destructor - Does Nothing*/
SnakeBlock::~SnakeBlock() 
{
  
}

/*! \brief Moves the SnakeBlock to the given position.
 * Precondition: A SnakeBlock object needed to be moved or placed on the screen.
 * Postcondition: The SnakeBlock will be moved to the given position.
 * \param x The x position to move the SnakeBlock to.
 * \param y The y position to move the SnakeBlock to.*/
void SnakeBlock::setPosition(int xCoord, int yCoord)
{
	rect.moveTo(xCoord, yCoord); // The SnakeBlock will be moved to the given position
}

/*! \brief Returns the Current x position of the SnakeBlock.
 * Precondition: Snake object requested Current x position of SnakeBlock.
 * Postcondition: Current x position is returned.
 * \return The Current x position of the SnakeBlock.*/
int SnakeBlock::getxPos()
{
	return x;
}

/*! \brief Returns the Current y position of the SnakeBlock.
 * Precondition: Snake object requested Current y position of SnakeBlock.
 * Postcondition: Current y position is returned.
 * \return The Current y position of the SnakeBlock.*/
int SnakeBlock::getyPos()
{
	return y;
}
		
/*! \brief Returns the Previous x position of the SnakeBlock.
 * Precondition: Snake object requested Previous x position of SnakeBlock.
 * Postcondition: Previous x position is returned.
 * \return The Previous x position of the SnakeBlock.*/
int SnakeBlock::getxOldPos() 
{
	return px;
}


/*! \brief Returns the Previous y position of the SnakeBlock.
 * Precondition: Snake object requested Previous y position of SnakeBlock.
 * Postcondition:  Previous y position is returned.
 * \return The Previous y position of the SnakeBlock.*/
int SnakeBlock::getyOldPos()
{
	return py;
}

/*! \brief Moves the SnakeBlock to the location the SnakeBlock in front of it.
 * Precondition: SnakeBlock in front of this SnakeBlock was moved.
 * Postcondition: This SnakeBlock has been moved to the location the SnakeBlock in front of it.
 * \param pxCoord The previous x position of the SnakeBlock in front of it.
 * \param pyCoord The previous y position of the SnakeBlock in front of it.*/
void SnakeBlock::autoMove(int pxCoord, int pyCoord)
{
	/*Stores old coordinates in place holder*/
	px = x;
	py = y;

	/*Assigns new coordinate values*/	
	x = pxCoord;
	y = pyCoord;

	setPosition(x, y); // Moves the SnakeBlock to the given position
}

/*! \brief Checks if SnakeBlock is off the screen (collided with the wall).
 * Precondition: checkCollision function in game was called and wrap around is disabled.
 * Postcondition: If True, gameOver will occur.
 * \return Whether the SnakeBlcok is off the screen (collided with the wall).*/
bool SnakeBlock::hitsWall()
{
	if (rect.right() > 428) // If SnakeBlock goes past right border
	{
	  	return TRUE;
	}
	else if (rect.left() < 28) // If SnakeBlock goes past left border
	{
	    	return TRUE;
	}
	else if (rect.top() < 150) // If SnakeBlock goes past upper border
	{
	   	return TRUE;
	}
	else if (rect.bottom() > 650) // If SnakeBlock goes past bottom border
	{
	    	return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*! \brief Switches the image of the SnakeBlock (Snake head only) to the going down image.
 * Precondition: Snake changed direction to going down.
 * Postcondition: The image of snakeblockdown.png is displayed.*/
void SnakeBlock::setImageDown()
{
	image.load("snakeblockdown.png");
}

/*! \brief Switches the image of the SnakeBlock (Snake head only) to the going up image.
 * Precondition: Snake changed direction to going up.
 * Postcondition: The image of snakeblockup.png is displayed.*/
void SnakeBlock::setImageUp()
{
	image.load("snakeblockup.png");
}

/*! \brief Switches the image of the SnakeBlock (Snake head only) to the going left image.
 * Precondition: Snake changed direction to going left.
 * Postcondition: The image of snakeblockleft.png is displayed.*/
void SnakeBlock::setImageLeft()
{
	image.load("snakeblockleft.png");
}

/*! \brief Switches the image of the SnakeBlock (Snake head only) to the going right image.
 * Precondition: Snake changed direction to going right.
 * Postcondition: The image of snakeblockright.png is displayed.*/
void SnakeBlock::setImageRight()
{
	image.load("snakeblockright.png");
}

/*! \brief Returns the rect of SnakeBlock.
 * Precondition: Any collision detection or paint event that involes the SnakeBlock occured.
 * Postcondition: The Qrect of the SnakeBlock is returned.
 * \return The rect of SnakeBlock.*/
QRect SnakeBlock::getRect()
{
  return rect;
}

/*! \brief Returns the image of the SnakeBlock.
 * Precondition: Instance of Game called a paint event and the game is started.
 * Postcondition: The image of the SnakeBlock will be painted on the screen.
 * \return QImage The image of the SnakeBlock.*/ 
QImage & SnakeBlock::getImage()
{
  return image;
}
