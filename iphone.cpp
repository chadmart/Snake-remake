/*!\file iphone.cpp
 * 
 * \brief Contains Iphone image and location.
 * 
 * \author Chad Martin
 * 
 * A Iphone image and location of where to paint.
 */

#include "iphone.h"

/*! \brief Class Constructor - loads image, moves to specified location.
 * Precondition: A new instance of game was created.
 * Postcondition: A new Iphone image is loaded and ready to be painted.*/
Iphone::Iphone()
{

  	image.load("iphoneFrame.png");

  	rect = image.rect();

	setPosition(); // Sets the location of the Iphone
}

/*! \brief Class Destructor - Does Nothing*/
Iphone::~Iphone() 
{

}

/*! \brief Sets the location of the Iphone.
 * Precondition: A Iphone object was created.
 * Postcondition: Location is set for the Iphone.*/
void Iphone::setPosition() 
{
  rect.moveTo(0,0); // moves the iphone to the upper right corner of the screen
}

/*! \brief Returns rect of Iphone.
 * Precondition: Instance of Game called a paint event.
 * Postcondition: The Qrect of the Iphone is returned.
 * \return The rect of Iphone.*/
QRect Iphone::getRect()
{
  return rect; //returns The rect of Iphone
}

/*! \brief Returns image of Iphone.
 * Precondition: Instance of Game called a paint event.
 * Postcondition: The image of the Iphone will be painted on the screen.
 * \return Image of Iphone.*/
QImage & Iphone::getImage()
{
  return image; //return Image of Iphone
}

