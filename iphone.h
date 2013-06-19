#ifndef IPHONE_H
#define IPHONE_H

/*!\file iphone.h
 * 
 * \brief Contains Iphone image and location.
 * 
 * \author Chad Martin
 * 
 * A Iphone image and location of where to paint.
 */

#include <QImage>
#include <QRect>

/*! \brief A Iphone image and location of where to paint.*/
class Iphone
{
	// Defining Public Functions (Methods)
  	public:
		/*! \brief Class Constructor - loads image, moves to specified location.
		 * Precondition: A new instance of game was created.
		 * Postcondition: A new Iphone image is loaded and ready to be painted.*/
    		Iphone();

		/*! \brief Class Destructor - Does Nothing*/
    		~Iphone();

		/*! \brief Sets the location of the Iphone.
		 * Precondition: A Iphone object was created.
		 * Postcondition: Location is set for the Iphone.*/
		void setPosition();

		/*! \brief Returns rect of Iphone.
		 * Precondition: Instance of Game called a paint event.
		 * Postcondition: The Qrect of the Iphone is returned.
		 * \return The rect of Iphone.*/
    		QRect getRect();

		/*! \brief Returns image of Iphone.
		 * Precondition: Instance of Game called a paint event.
		 * Postcondition: The image of the Iphone will be painted on the screen.
		 * \return Image of Iphone.*/
    		QImage & getImage();

	// Defining Protected Variables 
	protected:

		/*! \brief The QImage of Iphone.*/
    		QImage image;

		/*! \brief The QRect of Iphone.*/
    		QRect rect;

};

#endif

