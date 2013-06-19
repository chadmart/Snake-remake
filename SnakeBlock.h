#ifndef SNAKEBLOCK_H
#define SNAKEBLOCK_H

/*!\file SnakeBlock.h
 * 
 * \brief Represents the SnakeBlock.
 * 
 * \author Chad Martin
 * 
 * This class represents one block of the Snake.
 */

#include <QImage>
#include <QRect>

/*! \brief The SnakeBlock
 * Represents one block of the Snake.*/
class SnakeBlock
{
  public:
	/*! \brief Class Constructor - Creates one SnakeBlock at the given postion
	 * with the specified image and initializes the data members to default values.
	 * Precondition: A new game was created or the Snake is growing bigger.
	 * Postcondition: A new Snakeblock is created and added to the Snake.
	 * \param xCoord x position to place SnakeBlock.
	 * \param yCoord y position to place SnakeBlock.
	 * \param imgSelect Chooses between the different SnakeBlock images.*/ 
	SnakeBlock(int xCoord, int yCoord, int imgSelect);

	/*! \brief Class Destructor - Does Nothing*/
    	~SnakeBlock();

	/*! \brief Moves the SnakeBlock to the given position.
	 * Precondition: A SnakeBlock object needed to be moved or placed on the screen.
	 * Postcondition: The SnakeBlock will be moved to the given position.
	 * \param x The x position to move the SnakeBlock to.
	 * \param y The y position to move the SnakeBlock to.*/
	void setPosition(int x, int y);

	/*! \brief Returns the Current x position of the SnakeBlock.
	 * Precondition: Snake object requested Current x position of SnakeBlock.
	 * Postcondition: Current x position is returned.
	 * \return The Current x position of the SnakeBlock.*/
	int getxPos();

	/*! \brief Returns the Current y position of the SnakeBlock.
	 * Precondition: Snake object requested Current y position of SnakeBlock.
	 * Postcondition: Current y position is returned.
	 * \return The Current y position of the SnakeBlock.*/
	int getyPos();

	/*! \brief Returns the Previous x position of the SnakeBlock.
	 * Precondition: Snake object requested Previous x position of SnakeBlock.
	 * Postcondition: Previous x position is returned.
	 * \return The Previous x position of the SnakeBlock.*/
	int getxOldPos();

	/*! \brief Returns the Previous y position of the SnakeBlock.
	 * Precondition: Snake object requested Previous y position of SnakeBlock.
	 * Postcondition:  Previous y position is returned.
	 * \return The Previous y position of the SnakeBlock.*/
	int getyOldPos();

	/*! \brief Moves the SnakeBlock to the location the SnakeBlock in front of it.
	 * Precondition: SnakeBlock in front of this SnakeBlock was moved.
	 * Postcondition: This SnakeBlock has been moved to the location the SnakeBlock in front of it.
	 * \param pxCoord The previous x position of the SnakeBlock in front of it.
	 * \param pyCoord The previous y position of the SnakeBlock in front of it.*/
	void autoMove(int pxCoord, int pyCoord);

	/*! \brief Checks if SnakeBlock is off the screen (collided with the wall).
	 * Precondition: checkCollision function in game was called and wrap around is disabled.
	 * Postcondition: If True, gameOver will occur.
	 * \return Whether the SnakeBlcok is off the screen (collided with the wall).*/
	bool hitsWall();

	/*! \brief Switches the image of the SnakeBlock (Snake head only) to the going down image.
	 * Precondition: Snake changed direction to going down.
	 * Postcondition: The image of snakeblockdown.png is displayed.*/
	void setImageDown();

	/*! \brief Switches the image of the SnakeBlock (Snake head only) to the going up image.
	 * Precondition: Snake changed direction to going up.
	 * Postcondition: The image of snakeblockup.png is displayed.*/
	void setImageUp();

	/*! \brief Switches the image of the SnakeBlock (Snake head only) to the going left image.
	 * Precondition: Snake changed direction to going left.
	 * Postcondition: The image of snakeblockleft.png is displayed.*/
	void setImageLeft();

	/*! \brief Switches the image of the SnakeBlock (Snake head only) to the going right image.
	 * Precondition: Snake changed direction to going right.
	 * Postcondition: The image of snakeblockright.png is displayed.*/
	void setImageRight();

	/*! \brief Returns the rect of SnakeBlock.
	 * Precondition: Any collision detection or paint event that involes the SnakeBlock occured.
	 * Postcondition: The Qrect of the SnakeBlock is returned.
	 * \return The rect of SnakeBlock.*/
    	QRect getRect();

	/*! \brief Returns the image of the SnakeBlock.
	 * Precondition: Instance of Game called a paint event and the game is started.
	 * Postcondition: The image of the SnakeBlock will be painted on the screen.
	 * \return QImage The image of the SnakeBlock.*/ 
    	QImage & getImage();

  private:

	/*! \brief Current x position of the SnakeBlock.*/ 
	int x;
	/*! \brief Current y position of the SnakeBlock.*/ 
	int y;

	/*! \brief Previous x position of the SnakeBlock.*/
	int px;
	/*! \brief Previous y position of the SnakeBlock.*/
	int py;

	/*! \brief The QImage of SnakeBlock.*/
    	QImage image;

	/*! \brief The QRect of SnakeBlock.*/
    	QRect rect;
};

#endif
