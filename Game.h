#ifndef GAME_H
#define GAME_H

/*!\file Game.h
 * 
 * \brief Contians the Snake Game Logic.
 * 
 * \author Chad Martin
 * 
 * This class contains the logic that makes up the Snake Game.
 */

#include "SnakeBlock.h"
#include "Snake.h"
#include "Food.h"
#include "SpecialFood.h"
#include "FoodWinner.h"
#include "iphone.h"
#include <vector> 

#include <QWidget>
#include <QKeyEvent>

/*! \brief The Snake Game Logic.
 * This class contains the logic that makes up the Snake Game.*/
class Game : public QWidget
{
  	Q_OBJECT //Meta-Object Compiler (handles Qt's C++ extensions)

  	public:
		/*! \brief Class Constructor - initializes the data members to default values 
		 * and creates dynamically allocated memory.
		 * Precondition: Game object has been created.
		 * Postcondition: Intro screen 1 is displayed.*/
	    	Game(QWidget *parent = 0);

		/*! \brief Class Destructor - Deletes dynamically allocated objects (specialFood, foodWinner, food, and snake).*/
		~Game();

  	protected:
		/*! \brief Paints the necessary object on the screen.
		 * Precondition: a QPaintEvent is called.
		 * Postcondition: Necessary objects are painted on the screen.
		 * \param *event QT event pointer*/
	    	void paintEvent(QPaintEvent *event);

		/*! \brief Occurs when ever a timer event is called.
		 * Precondition: a QTimerEvent is called.
		 * Postcondition: If game is started and the direction has not changed,
		 * then the Snake is moved and collsion detection is run (checkCollision is called).
		 * Next, changedDir is set to false and QPaintEvent (repaint) is called.
		 * \param *event QT event pointer*/
	    	void timerEvent(QTimerEvent *event);

		/*! \brief Carries out the required actions for the specific key.
		 * Precondition: a QKeyEvent is called. (a key is pressed)
		 * Postcondition: Actions for specified key are carried out.
		 * \param *event QT event pointer*/
	    	void keyPressEvent(QKeyEvent *event);
		
		/*! \brief If game is not started, resets data members to default values,  
		 * deletes Snake, creates a new Snake to default length and position, and moves food.
		 * Precondition: Game is not started and a 'Y' or 'N' was pressed during intro Screen 2.
		 * Postcondition: Game is started and Snake is centered on screen. */
	    	void startGame();
		
		/*! \brief Pauses and Unpauses a started game.
		 * Precondition: Game is started and 'P' is pressed, or Game is paused and 'P' or a directional key is pressed.
		 * Postcondition: If game is started, the game is paused. If game is paused, game is unpaused.*/
	    	void pauseGame();
		
		/*! \brief Stops the game and the timer, sets up variables to paint the gameOverScreen, and calls a paint event.
		 * Precondition: Snake makes an illegal collision or any key is pressed during the Blue Screen of Death.
		 * Postcondition: The paint event will display the gameOverScreen.*/
	    	void stopGame();
		
		/*! \brief Stops the game and the timer, sets up variables to paint the victoryScreen, and calls a paint event.
		 * Precondition: If snake collides with foodWinner, game is started and 'V' is pressed, or growCount == 315.
		 * Postcondition: The paint event will display the victoryScreen.*/
	    	void victory();

		/*! \brief Stops the timer, sets up variables to paint the Blue Screen of Death, sets points to zero,
		 * and calls a paint event.
		 * Precondition: If snake collides with specialFood, or game is started and '8' is pressed.
		 * Postcondition: Points are set to zero and the paint event will display the Blue Screen of Death.*/
		void blueScreenDeath();
		
		/*! \brief The screen that is displayed when a Game Over occurs.
		 * Precondition: Paint event is called and gameOver is true.
		 * Postcondition: gameOverScreen is displayed.		
		 * \param QT Qpainter object reference. */
		void gameOverScreen(QPainter &painter);
		
		/*! \brief The screen that is displayed when a Victory occurs.
		 * Precondition: Paint event is called and gameWon is true.
		 * Postcondition: victoryScreen is displayed.
		 * \param QT Qpainter object reference. */
		void victoryScreen(QPainter &painter);
		
		/*! \brief Paints points on the status bar on the iphone.
		 * Precondition: Paint event is called and either gameStarted or BSOD is true.
		 * Postcondition: Points are displayed on status bar of iphone.
		 * \param QT Qpainter object reference. */
		void getPoints(QPainter &painter);
		
		/*! \brief Paints the intro screens on the screen of the iphone.
		 * Precondition: Paint event is called and either introPrompt1 or introPrompt2 is true.
		 * Postcondition: Either intro screen 1 or intro screen 2 is displayed.
		 * \param QT Qpainter object reference. */
		void introScreen(QPainter &painter);
		
		/*! \brief Carries out actions if snake collided with something.
		 * Precondition: The Snake is moved by a directional key press or a timer event.
		 * Postcondition: Specific action carried out according to what the snake collided with.*/
	    	void checkCollision();
		

  	private:
		/*! \brief The infinitely growing snake.*/
	    	Snake *snake;

		/*! \brief The normal piece of Food, red or green apple logo. If 
		 * the Snake eats this Food, the Snake will grow one SnakeBlock.*/
	    	Food *food;

		/*! \brief The special piece of Food, The Windows 8 logo. If 
		 * the Snake eats this Food, the game will go into a Blue 
		 * Screen of Death Game over in which the user loses all points.
		 * This will spawn every ten grows for 100 paint events.*/
	    	SpecialFood *specialFood;

		/*! \brief The winning piece of Food, The Linux logo. If 
		 * the Snake eats this Food, the game will go into a Victory 
		 * Screen in which the game ends and a special screen is displayed.
		 * This will spawn after the specialFood has been painted 100 times.
		 * It will be painted for 100 paint events, and then disappear.*/
		FoodWinner *foodWinner;
		
		/*! \brief The Iphone border around the game.*/
		Iphone iphone;


		/*! \brief The unique timer identifier that is returned from startTimer().
		 * It is passed to killTimer(int id) in order to stop the timer.*/
	    	int timerId; 

		/*! \brief The timer delay that controls the speed. It is passed 
		 * to startTimer() in order to start the timer*/
		int speedDelay;

		/*! \brief The number of points the user has accumulated.*/
		unsigned int points;

		/*! \brief The points multiplier, this variable will be 
		 * multiplied with the points that the user earns during each grow.
		 * The User sets this variable during 1st intro screens. */
		unsigned int pointMulti;

		/*! \brief This control what logic is used when the Snake hits the wall.
		 * The User sets this variable during 2nd intro screens. If False, a game 
		 * over will occur when the Snake hits the wall. If True, the Snake will 
		 * wrap around to the other side of the screen when it hits the wall.*/
		bool wrapAround;

		/*! \brief Controls when intro prompt 1 is displayed, and what actions
		 * to take, when intro prompt 1, is displayed during a key press event. */
		bool introPrompt1;

		/*! \brief Controls when intro prompt 2 is displayed, and what actions
		 * to take, when intro prompt 2 is displayed, during a key press event. */
		bool introPrompt2;

		/*! \brief Whether or not the game is started. True when game is
		 * started, otherwise False.*/
	    	bool gameStarted;

		/*! \brief Whether or not a game over has occured. True when a 
		 * game over has occur, otherwise False.
		 * Controls when Game Over Screen is displayed*/
	    	bool gameOver;

		/*! \brief Whether or not a victory (the game has been won) has occured. 
		 * True when a victory has occured, otherwise False.
		 * Controls when Victory Screen is displayed*/
		bool gameWon;

		/*! \brief Whether or not a victory or a game over has occured. 
		 * True when a victory or a game over has occured, otherwise False.
		 * Controls what actions to take during a key press event, when a 
		 * victory or a game over has occured*/
		bool gameEnded;

		/*! \brief Whether or not a Blue screen of death has occured.
		 * True when a Blue screen of death has occured, otherwise False.
		 * Controls when Blue screen of death is displayed, and what actions
		 * to take, when Blue screen of death is displayed, during a key press event.*/
	    	bool bSOD;

		/*! \brief Whether or not the game is paused. 
		 * True when the game is paused, otherwise False.*/
	    	bool paused;

		/*! \brief Whether or not the snake has changed directions before 
		 * the last tiemr event. True when the snake has changed directions 
		 * before the last timer event, otherwise False.*/
		bool changedDir;

		/*! \brief Stores the last valid direction of the Snake.*/
		char lastDir;

		/*! \brief The number of times the snake has grown.
		 * Controls when to start displaying specialFood. Once 
		 * growCount % 10 == 0, specialFood is painted*/
		unsigned int growCount;

		/*! \brief The number of times the special food has been painted. 
		 * Controls when ro start displaying foodWinner. Once 
		 * spawnWinnerCount % 1000 == 0, foodWinner is painted*/
		unsigned int spawnWinnerCount;

		/*! \brief Whether or not the specialFood will be painted.
		 * True when a specialFood will be painted, otherwise False.
		 * Controls when specialFood is displayed, and what actions
		 * to take, when specialFood is displayed, during a key 
		 * press event or during checkCollision.*/
		bool deathSpawn;

		/*! \brief Whether or not the foodWinner will be painted.
		 * True when a foodWinner will be painted, otherwise False.
		 * Controls when foodWinner is displayed, and what actions
		 * to take, when foodWinner is displayed, during a key 
		 * press event or during checkCollision.*/
		bool winSpawn; 

		/*! \brief Increments everytime specialFood is painted.
		 * Controls when to stop displaying specialFood. Once 
		 * deathCounter % 100 == 0, specialFood is no longer painted*/
		int deathCounter;

		/*! \brief Increments everytime foodWinner is painted.
		 * Controls when to stop displaying foodWinner. Once 
		 * winCounter % 100 == 0, foodWinner is no longer painted*/
		int winCounter;

		/*! \brief Controls whether or not to move and 
		 * start displaying foodWinner or specialFood.*/
		bool doOneTime;

		/*! \brief Controls whether or not to fix the grow count, 
		 * depending on the spawn of specialFood.*/
		bool fixCount;

		/*! \brief Controls which apple is to be displayed.
		 * If 0, then green apple is displayed
		 * If 1, then red apple is displayed*/
		int switchFood;
		
		/*! \brief This is the QImage of the screen that will be displayed when the Snake eats a Windows 8 logo.*/
		QImage blueScreenImage; 

		/*! \brief This is the QRect of the screen that will be displayed when the Snake eats a Windows 8 logo.*/
    		QRect blueScreenRect;

		/*! \brief This is the QImage of the screen that will be displayed when the Snake eats a Linux logo.*/
		QImage victoryScreenImage;

		/*! \brief This is the QRect of the screen that will be displayed when the Snake eats a Linux logo.*/
    		QRect victoryScreenRect;
};

#endif


