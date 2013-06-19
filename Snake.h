#ifndef SNAKE_H
#define SNAKE_H

/*!\file Snake.h
 * 
 * \brief Represents the infinitely growing Snake
 * 
 * \author Chad Martin
 * 
 * This class represents the infinitely growing snake which is made up of a vector of SnakeBlock pointers.
 */

#include <QImage>
#include <QRect>
#include <QPainter>
#include <vector> //required for the use of vectors
#include "SnakeBlock.h" //required for compostion
#include "Food.h" //required for compostion

/*! \brief The Snake
 * Represents the infinitely growing snake which is made up of a vector of SnakeBlock pointers.*/
class Snake
{
  	public:
		/*! \brief Class Constructor - Makes a Snake, one block big appear. 
		 * on the screen, and initializes the data members to default values
		 * Precondition: New game has started.
		 * Postcondition: Snake head appears in the center of the screen.*/
	    	Snake();

		/*! \brief Class Destructor - Deletes dynamically allocated vector of SnakeBlock pointers.*/
	    	~Snake();

		/*! \brief Resets the Snake to one block big and in center and sets the data members to default values.
		 * Precondition: New game has started.
		 * Postcondition: Snake head appears in the center of the screen.*/
		void resetState();

		/*! \brief Moves the whole Snake right one block and changes image to going 
		 * right image, unless the Snake is going left and bigger than 1 SnakeBlock.
		 * Precondition: The user press Right arrow or the last valid direction was right.
		 * Postcondition: the whole Snake will be moved right one block.
		 * \param &wrapAround If true, allows wrap around.*/ 
		void goRight(bool &wrapAround);

		/*! \brief Moves the whole Snake left one block and changes image to going 
		 * left image, unless the Snake is going right and bigger than 1 SnakeBlock.
		 * Precondition: The user press Left arrow or the last valid direction was left.
		 * Postcondition: the whole Snake will be moved left one block.
		 * \param &wrapAround If true, allows wrap around.*/ 
		void goLeft(bool &wrapAround);

		/*! \brief Moves the whole Snake up one block and changes image to going 
		 * up image, unless the Snake is going down and bigger than 1 SnakeBlock.
		 * Precondition: The user press Up arrow or the last valid direction was up.
		 * Postcondition: the whole Snake will be moved up one block.
		 * \param &wrapAround If true, allows wrap around.*/ 
		void goUp(bool &wrapAround);

		/*! \brief Moves the whole Snake down one block and changes image to going 
		 * down image, unless the Snake is going up and bigger than 1 SnakeBlock.
		 * Precondition: The user press Down arrow or the last valid direction was down.
		 * Postcondition: the whole Snake will be moved down one block.
		 * \param &wrapAround If true, allows wrap around.*/ 
		void goDown(bool &wrapAround);

		/*! \brief Moves the Snake one block in the last valid direction.
		 * Precondition: Timer event occured
		 * Postcondition: The Snake is moved one block in the last valid direction.
		 * \param &wrapAround If true, allows wrap around.*/ 
		void autoMove(bool &wrapAround);

		/*! \brief Adds one SnakeBlock to the end of the Snake.
		 * Precondition: The Snake head collided with a normal piece of food
		 * Postcondition: Adds one SnakeBlock to the end of the Snake.*/ 
		void grow();

		/*! \brief Checks if Food is on top of Snake.
		 * Precondition: A Food object was moved.
		 * Postcondition: Returns True, if food is on top of Snake.
		 * \param *food Food object pointer. It will be used to check if it is on top of the Snake.
		 * \return Whether the Food is on top of the Snake.*/ 
		bool checkBadFood(Food *food);

		/*! \brief Checks if Snake head collided with the Snake body.
		 * Precondition: The Snake moved.
		 * Postcondition: Returns True, if the Snake head collided with the Snake body.
		 * \return Whether the Snake head collided with the Snake body.*/ 
		bool checkCollision();

		/*! \brief Checks if Snake head collided with the wall (off the screen).
		 * Precondition: Wrap around is disabled and the Snake moved.
		 * Postcondition: Returns True, if the Snake head collided with the wall.
		 * \return Whether the Snake head collided the wall.*/ 
		bool hitsWall();

		/*! \brief Paints the entire vector of SnakeBlocks on the screen at its current location.
		 * Precondition: Instance of Game called a paint event and the game is started.
		 * Postcondition: The whole Snake will be painted on the screen.
		 * \param &painter QPainter object created in Game to paint images on screen.*/ 
		void drawSnake(QPainter &painter);

		/*! \brief Returns the Qrect of the Snake head (front of snake).
		 * Precondition: Any collision detection that involes the Snake occured.
		 * Postcondition: The Qrect of the Snake head (front of snake) is returned.
		 * \return Returns Qrect of the Snake head (front of snake).*/ 
		QRect getRect();

  	private:
	   	/*! \brief Vector of SnakeBlock pointers.*/ 
		std::vector<SnakeBlock*> snakeBlocks;
		
		/*Resolves autoMove() issues*/
		/*! \brief Current or future x position of front block (head of snake).*/ 
		int x;
		/*! \brief Current or future y position of front block (head of snake).*/  
		int y; 
		
		/*! \brief Current x direction of Snake.*/  
		int xDir;
		/*! \brief Current y direction of the Snake.*/  
		int yDir;

		/*! \brief Number of times the snake has grown.*/  
		int growsCount;

		/*! \brief Used to switch between Snake body block images.
		 * When 0, SnakeBlock will be blue.
		 * When 1, SnakeBlock will be purple.*/  
		int switchBody;
};

#endif
