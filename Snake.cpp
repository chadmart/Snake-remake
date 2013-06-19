/*!\file Snake.cpp
 * 
 * \brief Represents the infinitely growing Snake
 * 
 * \author Chad Martin
 * 
 * This class represents the infinitely growing snake which is made up of a vector of SnakeBlock pointers.
 */

#include "Snake.h"

/*! \brief Class Constructor - Makes a Snake, one block big appear. 
 * on the screen, and initializes the data members to default values
 * Precondition: New game has started.
 * Postcondition: Snake head appears in the center of the screen.*/
Snake::Snake()
{
	// Setting class variables
	x = 228;y = 350;// centers snake on iphone screen
	snakeBlocks.push_back(new SnakeBlock(x,y,0)); // creates new SnakeBlock at center of screen with head image
	switchBody = 0; // initializes body part image switcher

	growsCount = 0; // initializes grow count
	xDir = 0; // initializes x direction
	yDir = 0; // initializes y direction
}

/*! \brief Class Destructor - Deletes dynamically allocated vector of SnakeBlock pointers.*/
Snake::~Snake() 
{
	for(unsigned int i = 0; i < snakeBlocks.size();i++) // goes through entire SnakeBlock vector
	{
		delete snakeBlocks[i]; // deletes dynamically allocated SnakeBlock
	}
}

/*! \brief Resets the Snake to one block big and in center and sets the data members to default values.
 * Precondition: New game has started.
 * Postcondition: Snake head appears in the center of the screen.*/
void Snake::resetState() 
{
	for(unsigned int i = 1; i < snakeBlocks.size();i++) // goes through entire SnakeBlock vector except the head
	{
		delete snakeBlocks[i]; // deletes dynamically allocated SnakeBlock
	}

	x = 228;y = 350; // centers snake on iphone screen
	snakeBlocks[0]->setPosition(x, y); // moves the snake head to center of screen

	xDir = 0; // resets x direction back to zero
	yDir = 0; // resets y direction back to zero

	growsCount = 0; // resets grow count back to zero
}


/*! \brief Moves the whole Snake right one block and changes image to going 
 * right image, unless the Snake is going left and bigger than 1 SnakeBlock.
 * Precondition: The user press Right arrow or the last valid direction was right.
 * Postcondition: the whole Snake will be moved right one block.
 * \param &wrapAround If true, allows wrap around.*/ 
void Snake::goRight(bool &wrapAround)
{	
	if(xDir==-25 && snakeBlocks.size()>1) // If snake is going left and bigger than 1 SnakeBlock, go left.
	{
		goLeft(wrapAround); // Move snake left one block	
	}
	else
	{
		x+=25; //increment head to future position

		/* Resolving illegal move issues */
		// In order for this code to run the user must enter YES to wraping around during playGame
		if(wrapAround ==TRUE)
			if(x>=428) // if snake head goes off of screen, move it to other side
				{x=28;} // allows wrap around

		xDir = 25; // set x direction to right
		yDir = 0; // set y direction to zero

		snakeBlocks[0]->setImageRight(); // changes Snake head image to the going right image

		snakeBlocks[0]->autoMove(x,y); // moves first block right one

		for(unsigned int i = 1; i < snakeBlocks.size();i++) // goes through the rest of SnakeBlock vector
		{
			// moves all other SnakeBlocks right one block
			snakeBlocks[i]->autoMove( snakeBlocks[i-1]->getxOldPos(), snakeBlocks[i-1]->getyOldPos());
		}
	}
}


/*! \brief Moves the whole Snake left one block and changes image to going 
 * left image, unless the Snake is going right and bigger than 1 SnakeBlock.
 * Precondition: The user press Left arrow or the last valid direction was left.
 * Postcondition: the whole Snake will be moved left one block.
 * \param &wrapAround If true, allows wrap around.*/ 
void Snake::goLeft(bool &wrapAround) 
{
	if(xDir==25 && snakeBlocks.size()>1) // If snake is going right and bigger than 1 SnakeBlock, go right
	{
		goRight(wrapAround); // Move snake left one block	
	}
	else
	{
		x-=25;  // increment head to future position
		
		/* Resolving illegal move issues */
		// In order for this code to run the user must enter YES to wraping around during playGame
		if(wrapAround ==TRUE)
			if(x<28) // if snake head goes off of screen, move it to other side
				{x=403;} // allows wrap around

		xDir = -25; // set x direction to left
		yDir = 0; // set y direction to zero

		snakeBlocks[0]->setImageLeft(); // changes Snake head image to the going right image

		snakeBlocks[0]->autoMove(x,y); // moves first block left one

		for(unsigned int i = 1; i < snakeBlocks.size();i++) // goes through the rest of SnakeBlock vector
		{
			// moves all other blocks left one
			snakeBlocks[i]->autoMove( snakeBlocks[i-1]->getxOldPos(), snakeBlocks[i-1]->getyOldPos());
		}
	}
}

/*! \brief Moves the whole Snake up one block and changes image to going 
 * up image, unless the Snake is going down and bigger than 1 SnakeBlock.
 * Precondition: The user press Up arrow or the last valid direction was up.
 * Postcondition: the whole Snake will be moved up one block.
 * \param &wrapAround If true, allows wrap around.*/ 
void Snake::goUp(bool &wrapAround)
{
	if(yDir==25 && snakeBlocks.size()>1) // If snake is going down and bigger than 1 SnakeBlock, go down
	{
		goDown(wrapAround); // Move snake down one block	
	}
	else
	{	
		y-=25; // increment head to future position

		/* Resolving illegal move issues */
		// In order for this code to run the user must enter YES to wraping around during playGame
		if(wrapAround ==TRUE) 
			if(y<150) // if snake head goes off of screen, move it to other side
				{y=625;}//allows wrap around

		xDir = 0; // set x direction to zero
		yDir = -25; // set y direction to up

		snakeBlocks[0]->setImageUp(); // changes Snake head image to the going up image

		snakeBlocks[0]->autoMove(x,y); // moves first block up one

		for(unsigned int i = 1; i < snakeBlocks.size();i++) // goes through the rest of SnakeBlock vector
		{
			// moves all other blocks up one
			snakeBlocks[i]->autoMove( snakeBlocks[i-1]->getxOldPos(), snakeBlocks[i-1]->getyOldPos());
		}
	}
}

/*! \brief Moves the whole Snake down one block and changes image to going 
 * down image, unless the Snake is going up and bigger than 1 SnakeBlock.
 * Precondition: The user press Down arrow or the last valid direction was down.
 * Postcondition: the whole Snake will be moved down one block.
 * \param &wrapAround If true, allows wrap around.*/ 
void Snake::goDown(bool &wrapAround)
{
	if(yDir==-25 && snakeBlocks.size()>1) // If snake is going up and bigger than 1 SnakeBlock, go up
	{
		goUp(wrapAround); // Move snake up one block		
	}
	else
	{
		y+=25; // increment head to future position

		/* Resolving illegal move issues */
		// In order for this code to run the user must enter YES to wraping around during playGame
		if(wrapAround ==TRUE)
			if(y>=650) // if snake head goes off of screen, move it to other side
				{y=150;}//allows wrap around

		xDir = 0; // set x direction to zero
		yDir = 25; // set y direction to down
		
		snakeBlocks[0]->setImageDown(); // changes Snake head image to the going down image

		snakeBlocks[0]->autoMove(x,y); //moves first block down one

		for(unsigned int i = 1; i < snakeBlocks.size();i++) // changes Snake head image to the going up image
		{
			// moves all other blocks up one
			snakeBlocks[i]->autoMove( snakeBlocks[i-1]->getxOldPos(), snakeBlocks[i-1]->getyOldPos());
		}
	}
}

/*! \brief Moves the Snake one block in the last valid direction.
 * Precondition: Timer event occured
 * Postcondition: The Snake is moved one block in the last valid direction.
 * \param &wrapAround If true, allows wrap around.*/ 
void Snake::autoMove(bool &wrapAround)
{
	if(xDir > 0) // if going right,
		goRight(wrapAround); // go right
	if(xDir < 0) // if going left,
		goLeft(wrapAround); // go left
	if(yDir > 0) // if going down
		goDown(wrapAround); // go down
	if(yDir < 0) // if going up
		goUp(wrapAround); // go up
}

/*! \brief Adds one SnakeBlock to the end of the Snake.
 * Precondition: The Snake head collided with a normal piece of food
 * Postcondition: Adds one SnakeBlock to the end of the Snake.*/ 
void Snake::grow()
{
	// Setting varibales for location of last block before grow (tail of snake)
	int lxPos = snakeBlocks[snakeBlocks.size()-1]->getxPos();
	int lyPos = snakeBlocks[snakeBlocks.size()-1]->getyPos();

	/* Resolves movement/growth issues*/
	// if Snake just a head (one block big), calculates position of new 
	// Snakeblock at end of Snake on the opposite side of the direction 
	// the head is going
	if(snakeBlocks.size()<=1) 
	{
		if(yDir<0) // if going up
			lyPos+=25; // add one block below

		if(yDir>0) // if going down
			lyPos-=25; // add one block above

		if(xDir<0) // if going left
			lxPos+=25; // add one block right

		if(xDir>0) // if going right
			lxPos-=25; // add one block left
	}
	else
	{	
		// Setting varibales for location of 2nd to last block before grow
		int l2xPos = snakeBlocks[snakeBlocks.size()-2]->getxPos();
		int l2yPos = snakeBlocks[snakeBlocks.size()-2]->getyPos();

		// Calculates the direction to add the block 
		if(lyPos - l2yPos == -25)	
		{
			lyPos-=25; // add one block above
		}
		if(lyPos - l2yPos == 25) 
		{
			lyPos+=25; // add one block below
		}
		if(lxPos - l2xPos == -25)
		{
			lxPos-=25; // add one block left
		}
		if(lxPos - l2xPos == 25)
		{
			lxPos+=25; // add one block right
		}
	}

  	switchBody++; // increments Snakeblock body part switcher
    	switchBody %= 2; // if body part switch equals 2, set it back to zero

	// adds a SnakeBlock onto the snake at the calculated position 
	snakeBlocks.push_back(new SnakeBlock(lxPos,lyPos, switchBody+1));

	// increment the number of grows by 1
	growsCount++;
}

/*! \brief Checks if Food is on top of Snake.
 * Precondition: A Food object was moved.
 * Postcondition: Returns True, if food is on top of Snake.
 * \param *food Food object pointer. It will be used to check if it is on top of the Snake.
 * \return Whether the Food is on top of the Snake.*/ 
bool Snake::checkBadFood(Food *food)
{
	
	for(unsigned int i = 0; i < snakeBlocks.size(); i++) // goes through entire SnakeBlock vector
	{
		if((food->getRect()).intersects(snakeBlocks[i]->getRect())) // checks if food spawned on each SnakeBlock
		{
			return TRUE; // returns true, if food spawned on a SnakeBlock
		}
	}

	return FALSE; // returns false, if food did not spawned on any of the SnakeBlocks
}

/*! \brief Checks if Snake head collided with the Snake body.
 * Precondition: The Snake moved.
 * Postcondition: Returns True, if the Snake head collided with the Snake body.
 * \return Whether the Snake head collided with the Snake body.*/ 
bool Snake::checkCollision()
{
	for(unsigned int i = 1; i < snakeBlocks.size(); i++) // goes through entire SnakeBlock vector
	{

		//checks if front block (snake head) collides this any of the other blocks (rest of the snake)
		if((snakeBlocks[0]->getRect()).intersects(snakeBlocks[i]->getRect()))
		{
			return TRUE; // returns true, if the Snake head collided with the Snake body
		}

	}
	
	return FALSE;  // returns false, if the Snake head did NOT collide with the Snake body
}


/*! \brief Checks if Snake head collided with the wall (off the screen).
 * Precondition: Wrap around is disabled and the Snake moved.
 * Postcondition: Returns True, if the Snake head collided with the wall.
 * \return Whether the Snake head collided the wall.*/ 
bool Snake::hitsWall()
{
	if(snakeBlocks[0]->hitsWall()) // if Snake head is off screen
	{
		return TRUE; //return true, if Snake head is off of screen
	}
	
	return FALSE;  //return false, if Snake head is NOT off of screen
}

/*! \brief Paints the entire vector of SnakeBlocks on the screen at its current location.
 * Precondition: Instance of Game called a paint event and the game is started.
 * Postcondition: The whole Snake will be painted on the screen.
 * \param &painter QPainter object created in Game to paint images on screen.*/ 
void Snake::drawSnake(QPainter &painter)
{
	for(unsigned int i = 0; i < snakeBlocks.size();i++) // goes through entire SnakeBlock vector
	{
 		//paints each SnakeBlock on the screen
		painter.drawImage(snakeBlocks[i]->getRect(), snakeBlocks[i]->getImage());
	}
}

/*! \brief Returns the Qrect of the Snake head (front of snake).
 * Precondition: Any collision detection that involes the Snake occured.
 * Postcondition: The Qrect of the Snake head (front of snake) is returned.
 * \return Returns Qrect of the Snake head (front of snake).*/ 
QRect Snake::getRect()
{
	return snakeBlocks[0]->getRect(); // Returns Qrect of the Snake head 
}
