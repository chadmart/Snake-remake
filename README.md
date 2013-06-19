Snake-remake
============

Snake Remake using QT framework
Purpose/Overview
The program starts out by displaying intro screen 1 which asks the user for a number from 1 to 5 which correlates to the speed of the snake and the points multiplier. 1 is the slowest speed and 5 is the fastest speed. The faster the speed the bigger the points multiplier. 
Next intro screen 2 is displayed, the user is asked if he/she would like to enable wrap around. If wrap around is enabled, the snake is allowed to go through the borders. If wrap around is disabled and the snake hits the borders, it will cause a game over. Also, If wrap around is disabled, the points multiplier is doubled.
After the game options are set, the game starts at 0 points with 2 pieces on the screen. One of the pieces is a SnakeBlock head. This piece is the snake that the user controls with the arrow keys. The other piece is a green Apple logo. This piece is a normal piece of food. When the snake collides with the normal piece of food, the snake will grow 1 block and the points will increase by 7 times the points multiplier. After the collision, the food will spawn in a new random location. Also in the window, there is an iPhone. This is the border around the screen. On the status bar of the iPhone, the points that the user has accumulated are displayed. If the snake head runs over another part of the snake, it will always cause a game over. If wrap around is disabled and the snake hits the border, it will cause a game over. 
Another piece that can spawn is a Windows 8 logo. This piece is a special piece of food. When the snake collides with the special piece of food, the game will go into a blue screen of death. This piece will spawn every ten grows or if ‘W’ is pressed.
Another piece that can spawn is a Linux logo. This piece is the winning piece of food. When the snake collides with the winning piece of food, the game will end and a victory screen will appear. This piece will spawn after the special piece of food is painted in 100 paint events or if ‘L’ is pressed.
When a blue screen of death occurs, the game stops, the users points are set to zero, and a blue screen of death is displayed. After any key is pressed the game moves on to the game over screen.
When a game over occurs, the game stops and the game over screen is displayed. On the game over screen, the words game over, the total number of points, and instructions for the user to play again are displayed. If the user presses the Space bar, the game starts over and intro screen 1 is displayed.
When a victory occurs, the game stops and the victory screen is displayed. On the victory screen, the words victory, the total number of points, and instructions for the user to play again are displayed. If the user presses the Space bar, the game starts over and intro screen 1 is displayed.
If the user presses ESC at any time during the program, the program will quit.
Requirements
Entertain the user through playing the game. Find the Linux logo and eat it to win the game.
Instructions
In order to compile this program,
  •  extract files from ChadMart_HW2.zip
  •	navigate to the `/HW2/ directory
  •	enter “qmake -project” in terminal
  •	enter “qmake” in terminal
  •	enter “make” in terminal

In order to run this program,
  •	enter “./hw2” in terminal

Program library dependencies
  •	QT library
    o	<QDesktopWidget>
    o	<QApplication>
    o	<QWidget>
    o	<QKeyEvent>
    o	<QImage>
    o	<QRect>
    o	<QPainter>
  •	C Standard General Utilities Library
    o	<stdlib.h>
  •	vector Library
    o	<vector>
Classes
  •	Game
    o	Refer to …/hw2/html/classGame.html
  •	Snake
    o	Refer to …/hw2/html/classSnake.html
  •	SnakeBlock
    o	Refer to …/hw2/html/classSnakeBlock.html
  •	Food
    o	Refer to …/hw2/html/classFood.html
  •	SpecialFood (daughter class of  Food)
    o	Refer to …/hw2/html/classSpecialFood.html
  •	FoodWinner (daughter class of  Food)
    o	Refer to …/hw2/html/classFoodWinner.html
  •	Iphone
    o	Refer to /hw2/html/classIphone.html
Global Data/Functions
  •	Global Functions
    o	void center (QWidget &widget)
      	Sets up window size and centers window on screen.
      	Precondition: Program has started.
      	Postcondition: Game window is displayed on center of screen.
High-level Architecture
When the program starts, the QT window is initialized and the basic window settings are set such as the size of the window. Then Game is launched. Next, the required objects are created from the following classes: Snake, Food, SpecialFood, WinningFood, and iPhone. When an object of the Snake class is created, a vector of SnakeBlock objects is created. After that, the paint event is called which displays intro screen 1. The user is asked to select the speed which will set the timer delay and the points multiplier. Once the user makes a selection, another paint event is called which displays intro screen 2. During intro screen 2, the user is asked to whether to enable or disable wrap around which will set wraparound to TRUE or FALSE. Once the user makes a selection, startGame is called which starts the timer, resets data members to default values, deletes Snake, creates a new Snake dynamically, and moves food using moveFood and checkBadFood methods of the Food class. Then, another paint event is called which displays the game play screen.
	Now, the game begins. Once the user presses an arrow key, the snake begins to move by the autoMove method of the Snake class and collision detection occurs after each time the snake moves by the checkCollision method of the game class. If during checkCollision the snake makes an illegal collision, then the gameOver function is called and the game either restarts or the program terminates. If during checkCollision the snake collides with an Apple logo, the snake grows 1 SnakeBlock using snake->grow and points are added to points. If during checkCollision the snake collides with a Windows 8 logo, the blueScreenDeath function is called which displays the bsod. If during checkCollision the snake collides with a Linux logo, the victory screen is displayed using the victory function. If the user presses ‘P’, pauseGame function is called and game is paused.
If the user presses ESC at any time, qApp->exit function is called and program is terminated.
If the user presses ‘R’ at any time, stopGame function is called, introPrompt1 is set to true, and intro screen 1 is displayed.

User Interface
Universal Controls
  •	Esc key is pressed
    o	Exits app
  •	'R' key is pressed
    o	Game is reset
    o	Intro Screen 1 is displayed
    
Intro Screen 1
 
Intro Screen 1 Controls
  •	'1' key is pressed
    o	pointMulti = 1;
    o	speedDelay = 200;
    o	Intro Screen 2 is displayed
  •	'2' key is pressed
    o	pointMulti = 2;
    o	speedDelay = 169;
    o	Intro Screen 2 is displayed
  •	'3' key is pressed
    o	pointMulti = 3;
    o	speedDelay = 138;
    o	Intro Screen 2 is displayed
  •	'4' key is pressed
    o	pointMulti = 4;
    o	speedDelay = 107;
    o	Intro Screen 2 is displayed
  •	'5' key is pressed
    o	pointMulti = 5;
    o	speedDelay = 75;
    o	Intro Screen 2 is displayed
  •	'9' key is pressed
    o	pointMulti = 1000;
    o	speedDelay = 0;
    o	Intro Screen 2 is displayed
    
Intro Screen 2
 
Intro Screen 2 Controls
  •	'Y' key is pressed
    o	wrapAround = TRUE;
    o	Game is started
  •	'N' key is pressed
    o	wrapAround = FALSE;
    o	Game is started
    
Game Over Screen
 
Game Over Screen Controls
  •	Space bar
    o	Intro Screen 1 is displayed
    
Victory Screen
 
Victory Screen Controls
  •	Space bar is pressed
    o	Intro Screen 1 is displayed

Blue Screen of Death
 
Blue Screen of Death Controls
  •	Any key is pressed, expect 'R' or ESC
    o	Game Over Screen is displayed

Game Play Screen
 
Game Play Controls
  •	Normal Game Play Controls
    o	Right arrow key is pressed
      	Snake moves right
    o	Left arrow key is pressed
      	Snake moves left
    o	Up arrow key is pressed
      	Snake moves up
    o	Down arrow key is pressed
      	Snake moves down
    o	'P' key is pressed
      	Pauses game (Snake stops moving)
  •	Paused Game Play Controls
    o	Right arrow key is pressed
      	Game resumes
      	Snake moves right
    o	Left arrow key is pressed
      	Game resumes
      	Snake moves left
    o	Up arrow key is pressed
      	Game resumes
      	Snake moves up
    o	Down arrow key is pressed
      	Game resumes
      	Snake moves down
    o	'P' key is pressed
      	Game resumes
      	Snake moves in the last direction
  •	Cheat Codes (Only active during Normal Game Play)
    o	'M' key or 'A' key is pressed
      	switches food images
      	Moves the apple
    o	'G' key is pressed
      	Grows snake, but doesn't increase points
    o	'W' key is pressed
      	Moves specialFood (the Windows 8 logo)
      	Paints specialFood
    o	'8' key is pressed
      	Displays blue screen of death
      	Causes BSOD Game Over
    o	'L' key is pressed
      	Moves foodWinner (the Linux logo)
      	Paints foodWinner
    o	'V' key is pressed
      	Displays Victory screen
      	Causes Victory 
