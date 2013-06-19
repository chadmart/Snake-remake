/*!\file main.cpp
 * 
 * \brief Contians Main function which initializes Game object.
 * 
 * \author Chad Martin
 * 
 * This file is used to generate and set up a window for 
 * the game snake to be played in.
 */

#include "Game.h"
#include <QDesktopWidget>
#include <QApplication>

/*! \brief Sets up window size and centers window on screen.
 * Precondition: Program has started.
 * Postcondition: Game window is displayed on center of screen
 * \param &widget A user interface object.*/ 
void center(QWidget &widget)
{
  int x, y;
  int screenWidth;
  int screenHeight;

  int WIDTH = 456; //set window WIDTH to 456 pixels
  int HEIGHT = 773; //set window HEIGHT to 773 pixels
  
  QDesktopWidget *desktop = QApplication::desktop();

  //finds screen dimensions
  screenWidth = desktop->width();
  screenHeight = desktop->height();
 
  // finds screen center
  x = (screenWidth - WIDTH) / 2;
  y = (screenHeight - HEIGHT) / 2;

  //sets up window
  widget.setGeometry(x, y, WIDTH, HEIGHT);
  widget.setFixedSize(WIDTH, HEIGHT);
}


int main(int argc, char *argv[])
{
  // Creates QApplication object
  QApplication app(argc, argv);  
    
  Game window; // Creates a Game instance
  
  window.setWindowTitle("Snake 2.0"); // names Game window
  window.show(); // displaying window on screen
  center(window); // set up window size and center window on screen

  return app.exec();
}

