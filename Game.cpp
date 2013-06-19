/*!\file Game.cpp
 * 
 * \brief Contians the Snake Game Logic.
 * 
 * \author Chad Martin
 * 
 * This class contains the logic that makes up the Snake Game.
 */


#include "Game.h"
#include <QPainter>
#include <QApplication>

/*! \brief Class Constructor - initializes the data members to default values 
 * and creates dynamically allocated memory.
 * Precondition: Game object has been created.
 * Postcondition: Intro screen 1 is displayed.*/
Game::Game(QWidget *parent)
    : QWidget(parent)
{
	// creates dynamically allocated memory
		snake = NULL;
		food = new Food();
		specialFood = new SpecialFood();
		foodWinner = new FoodWinner();

 	//initializes the data members to default values
		speedDelay = 1000;
		points = 0;
		pointMulti = 1;

		introPrompt1 = TRUE;  
		introPrompt2 = FALSE;

		gameStarted = FALSE;
	  	gameOver = FALSE;
	    	gameWon = FALSE; 
		gameEnded = FALSE;
	  	bSOD = FALSE;

	  	paused = FALSE;  

		changedDir = FALSE; 
		lastDir = ' '; 

		growCount = 0;  
		spawnWinnerCount = 0;

		deathSpawn = FALSE;
		winSpawn = FALSE;

		deathCounter = 0;
		winCounter = 0;	

		doOneTime = TRUE;

		fixCount = FALSE;

		switchFood = 0;
}

/*! \brief Class Destructor - Deletes dynamically allocated objects (specialFood, foodWinner, food, and snake).*/
Game::~Game() 
{
	// Deletes dynamically allocated memory
	delete specialFood;
	delete foodWinner;
	delete food;
	delete snake;
}

/*! \brief Paints the necessary object on the screen.
 * Precondition: a QPaintEvent is called.
 * Postcondition: Necessary objects are painted on the screen.
 * \param *event QT event pointer*/
void Game::paintEvent(QPaintEvent *event)
{
  	QPainter painter(this);

 	//always paints iphone on screen
	painter.drawImage(iphone.getRect(), iphone.getImage());

	if (gameOver) // If gameOver is true
	{
		gameOverScreen(painter); //paint game over screen
  	}
	else if (gameWon) // If gameWon is true
	{
		victoryScreen(painter); //paint victory screen
  	}
  	else if(bSOD) // If bSOD is true, Paint Blue Screen of Death
	{
		//loads Blue Screen of Death image
  		blueScreenImage.load("blueScreenDeath.png"); 
  		blueScreenRect = blueScreenImage.rect();
		blueScreenRect.moveTo(28,150);
		
		//Paints Blue Screen of Death image
		painter.drawImage(blueScreenRect, blueScreenImage);

		//Paints Points on status bar of iphone
		getPoints(painter);

		//resets last direction to nothing
		lastDir = ' ';
		
  	}	
	else if(introPrompt1) // If introPrompt1 is true
	{
		introScreen(painter); //paint intro screen 1 screen
	}
	else if(introPrompt2) // If introPrompt2 is true
	{
		introScreen(painter); //paint intro screen 2 screen
	}
  	else // if has game Started
	{

    		snake->drawSnake(painter); // paint Snake on screen
    		painter.drawImage(food->getRect(), food->getImage()); // paint Food on screen

		if(winSpawn) // If winSpawn is true
		{
			painter.drawImage(foodWinner->getRect(), foodWinner->getImage()); // paint foodWinner on screen
			winCounter++; // increament winCounter

			if(winCounter%100==0) //if winCounter%100==0, then set up variables to stop painting foodWinner
			{
				deathSpawn = FALSE;
				winSpawn = FALSE;
				doOneTime = TRUE;
				spawnWinnerCount = 0;
			}
		}
		else if(deathSpawn) // If deathSpawn is true
		{
			painter.drawImage(specialFood->getRect(), specialFood->getImage()); // paint specialFood on screen
			deathCounter++; // increament deathCounter
			spawnWinnerCount++; // increament spawnWinnerCount

 			//if deathCounter%100==0, then set up variables to stop painting specialFood.
			//if spawnWinnerCount%1000==0, then set up variables to start painting foodWinner.
			if(deathCounter%100==0 || spawnWinnerCount%1000==0)
			{
				deathSpawn = FALSE;
				doOneTime = TRUE;
			}

		}

		//Paints Points on status bar of iphone
		getPoints(painter);
  	}
}

/*! \brief Occurs when ever a timer event is called.
 * Precondition: a QTimerEvent is called.
 * Postcondition: If game is started and the direction has not changed,
 * then the Snake is moved and collsion detection is run (checkCollision is called).
 * Next, changedDir is set to false and QPaintEvent (repaint) is called.
 * \param *event QT event pointer*/
void Game::timerEvent(QTimerEvent *event)
{

	if(gameStarted && !changedDir) // If game is started and the direction has not changed
	{
		snake->autoMove(wrapAround); // moves snake one block in direction it has been going
  		checkCollision(); // checks if Snake collided with anything
	}

	changedDir = FALSE; // sets changedDir to false
  	repaint(); // calls a paint event
}

/*! \brief Carries out the required actions for the specific key.
 * Precondition: a QKeyEvent is called. (a key is pressed)
 * Postcondition: Actions for specified key are carried out.
 * \param *event QT event pointer*/
void Game::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) 
    {
    	case Qt::Key_Left: // Left arrow was pressed
       	{  
		if(bSOD)
		{
			bSOD = FALSE; // set up variable to disable blue screen of death	
			stopGame();  // set up variables to end game and dispaly game over screen
		}
		else if(!introPrompt1 && !introPrompt2) 
		{
			if(paused)
				{pauseGame();} // unpause game

			if(lastDir != 'L' && gameStarted)
			{
				snake->goLeft(wrapAround); // Move snake left one block
				checkCollision(); // Check if snake collided with anything
				changedDir = TRUE; // Set changedDir  to true
				lastDir = 'L'; // Set lastDir to 'L'
  				repaint(); // calls a paint event
			}


		}
       	}
	break;

    	case Qt::Key_Right: // Right arrow was pressed
        { 
		if(bSOD)
		{
			bSOD = FALSE; // set up variable to disable blue screen of death	
			stopGame(); // set up variables to end game and dispaly game over screen
		}
		else if(!introPrompt1 && !introPrompt2)
		{
			if(paused)
				{pauseGame();} // unpause game

			if(lastDir != 'R' && gameStarted)
			{
				snake->goRight(wrapAround); // Move snake right one block
				checkCollision(); // Check if snake collided with anything
				changedDir = TRUE; // Set changedDir  to true
				lastDir = 'R'; // Set lastDir to 'R'
				repaint(); // calls a paint event
			}
		}
        }
        break;

    	case Qt::Key_Up: // Up arrow was pressed
       	{  
		if(bSOD)
		{
			bSOD = FALSE; // set up variable to disable blue screen of death	
			stopGame(); // set up variables to end game and dispaly game over screen
		}
		else if(!introPrompt1 && !introPrompt2)
		{
			if(paused)
				{pauseGame();} // unpause game

			if(lastDir != 'U' && gameStarted)
			{
				snake->goUp(wrapAround); // Move snake Up one block
				checkCollision(); // Check if snake collided with anything
				changedDir = TRUE; // Set changedDir  to true
				lastDir = 'U'; // Set lastDir to 'U'
			  	repaint(); // calls a paint event
			}
		}
       	}
	break;

    	case Qt::Key_Down: // Down arrow was pressed
        {
		if(bSOD)
		{
			bSOD = FALSE; // set up variable to disable blue screen of death	
			stopGame(); // set up variables to end game and dispaly game over screen
		}
	 	else if(!introPrompt1 && !introPrompt2)
		{
			if(paused)
				{pauseGame();} // unpause game

			if(lastDir != 'D' && gameStarted)
			{
				snake->goDown(wrapAround); // Move snake down one block
				checkCollision(); // Check if snake collided with anything
				changedDir = TRUE; // Set changedDir  to true
				lastDir = 'D'; // Set lastDir to 'D'
				repaint(); // calls a paint event
			}
		}
        }
        break;

   	case Qt::Key_P: // 'P' was pressed
        { 
		if(bSOD)
		{
			bSOD = FALSE; // set up variable to disable blue screen of death	
			stopGame(); // set up variables to end game and dispaly game over screen
		}
		else
		{
	          	pauseGame(); // pause/unpause game
		}
        }
        break;

    	case Qt::Key_R: // 'R' was pressed
        { 

		if(introPrompt2) //If intro prompt 2 screen is displayed, go back to intro screen 1
		{
			//sets up variables for intro prompt 1
			introPrompt1 =TRUE;
			introPrompt2 =FALSE;

			repaint();  // calls a paint event
		}
		else if(!introPrompt1)
		{  
			if(bSOD)
			{
				bSOD = FALSE; // set up variable to disable blue screen of death	
				stopGame(); // set up variables to end game and dispaly game over screen
			}
		
			/* Reloving UnPause/Resume/Restart ISSUES */
			if(paused)
			{
				pauseGame(); //unpause game
			}
		
			stopGame(); // set up variables to end game and dispaly game over screen
			
			//sets up variables for intro prompt 1
			introPrompt1 =TRUE;
			gameOver = FALSE;
			gameWon = FALSE;
			gameEnded = FALSE;

			repaint(); // calls a paint event
		}
        }
        break;
	
	// Move the apple
    	case Qt::Key_M: // 'M' was pressed
    	case Qt::Key_A: // 'A' was pressed
	{ 
		if(bSOD)
		{
			bSOD = FALSE; // set up variable to disable blue screen of death	
			stopGame(); // set up variables to end game and dispaly game over screen
		}
		/* Reloving Paused ISSUES */
		else if(paused)
		{
			// do nothing
		}
		else if(gameStarted) //If game has started move the apple and switch food images 
		{
			// Sets up variable to switch food images
			switchFood++;// increments Apple logo switcher
	    		switchFood %= 2; // if Apple logo switch equals 2, set it back to zero

			// Move the apple and making sure the apple is not on top oof any other object
			do{
				if(winSpawn)
					food->moveFood(foodWinner,switchFood);
				else if(deathSpawn)
					food->moveFood(specialFood,switchFood);
				else
		  			food->moveFood(switchFood);

			}while(snake->checkBadFood(food));
		}
        }
        break;

	// Grow the snake, but don't increase points
    	case Qt::Key_G: // 'G' was pressed
        { 
		if(bSOD)
		{
			bSOD = FALSE; // set up variable to disable blue screen of death	
			stopGame(); // set up variables to end game and dispaly game over screen
		}
		/* Reloving Paused ISSUES */
		else if(paused)
		{
			// do nothing
		}
		else if(gameStarted && lastDir != ' ')
		{
 			// grow snake, but don't increase points
			snake->grow();
			growCount++;
		
			// If needed, Fix the growCount
			if(fixCount == TRUE)
			{
				growCount--;
				fixCount = FALSE;
			}
		}
        }
        break;

	// set up variable to paint specialFood and move specialFood (the Windows 8 logo)
    	case Qt::Key_W: // 'W' was pressed
	{ 
		if(bSOD)
		{
			bSOD = FALSE; // set up variable to disable blue screen of death	
			stopGame(); // set up variables to end game and dispaly game over screen
		}
		/* Reloving Paused ISSUES */
		else if(paused)
		{
			// do nothing	
		}
		else if(gameStarted)
		{
			
			// set up variable to paint specialFood
			deathSpawn = TRUE;
			doOneTime = FALSE;
			
			// move specialFood making sure it is not on top oof any other object
			do{
				specialFood->moveFood(food);		  	

			}while(snake->checkBadFood(specialFood));

		}
        }
        break;

	// set up variables to dispaly blue screen of death
   	case Qt::Key_8: // '8' was pressed
        { 
		if(bSOD)
		{
			bSOD = FALSE; // set up variable to disable blue screen of death	
			stopGame(); // set up variables to end game and dispaly game over screen
		}
		/* Reloving Paused ISSUES */
		else if(paused)
		{
			// do nothing
		}
		else if(gameStarted)
		{
			blueScreenDeath(); // set up variables to dispaly blue screen of death
		}
        }
        break;

	// set up variable to paint foodWinner (the Linux logo)
    	case Qt::Key_L: // 'L' was pressed
	{ 
		if(bSOD)
		{
			bSOD = FALSE; // set up variable to disable blue screen of death	
			stopGame(); // set up variables to end game and dispaly game over screen
		}
		/* Reloving Paused ISSUES */
		else if(paused)
		{
			// do nothing
		}
		else if(gameStarted)
		{
			// set up variable to paint foodWinner (the Linux logo)
			spawnWinnerCount = 1000;
			doOneTime = TRUE;
		}
        }
        break;

	// set up variables to dispaly victory screen
    	case Qt::Key_V: // 'V' was pressed
        { 
		if(bSOD)
		{
			bSOD = FALSE; // set up variable to disable blue screen of death	
			stopGame(); // set up variables to end game and dispaly game over screen
		}
		/* Reloving Paused ISSUES */
		else if(paused)
		{
			// do nothing
		}
		else if(gameStarted)
		{
			victory(); // set up variables to dispaly victory screen
		}
        }
        break;

	// During intro screen 2, this enables wrapAround and starts the game
    	case Qt::Key_Y: // 'Y' was pressed
        { 
		if(bSOD)
		{
			bSOD = FALSE; // set up variable to disable blue screen of death	
			stopGame(); // set up variables to end game and dispaly game over screen
		}

		if(introPrompt2)
		{
			wrapAround = TRUE; // enables wrapAround

			// starts the game
			introPrompt2 = FALSE;
			startGame();
		}
        }
        break;

	// During intro screen 2, this disables wrapAround, doubles the points multiplier, and starts the game
    	case Qt::Key_N: // 'N' was pressed
        { 
		if(bSOD)
		{
			bSOD = FALSE; // set up variable to disable blue screen of death	
			stopGame(); // set up variables to end game and dispaly game over screen
		}

		if(introPrompt2)
		{
			wrapAround = FALSE;// disables wrapAround

			// starts the game
			introPrompt2 = FALSE;
			pointMulti = pointMulti*2; // doubles the points multiplier
			startGame();
			
		}
        }
        break;

	// During intro screen 1, this sets up speed delay and points multiplier, 
	// and then it will set up the variable for  intro screen 2
    	case Qt::Key_1: // '1' was pressed
        { 
		if(bSOD)
		{
			bSOD = FALSE; // set up variable to disable blue screen of death	
			stopGame(); // set up variables to end game and dispaly game over screen
		}

		if(introPrompt1)
		{
			// disables intro screen 1
			introPrompt1 = FALSE;

			// sets up speed delay and points multiplier
			pointMulti = 1;
			speedDelay = 200;
			
			// set up the variable for  intro screen 2
			introPrompt2 = TRUE;
			repaint(); // calls a paint event
		}
        }
        break;

	// During intro screen 1, this sets up speed delay and points multiplier, 
	// and then it will set up the variable for  intro screen 2
    	case Qt::Key_2: // '2' was pressed
        { 
		if(bSOD)
		{
			bSOD = FALSE; // set up variable to disable blue screen of death	
			stopGame(); // set up variables to end game and dispaly game over screen
		}

		if(introPrompt1)
		{
			// disables intro screen 1
			introPrompt1 = FALSE;

			// sets up speed delay and points multiplier
			pointMulti = 2;
			speedDelay = 169;

			// set up the variable for  intro screen 2
			introPrompt2 = TRUE;
			repaint(); // calls a paint event
		}
        }
        break;

	// During intro screen 1, this sets up speed delay and points multiplier, 
	// and then it will set up the variable for  intro screen 2
    	case Qt::Key_3: // '3' was pressed
        { 
		if(bSOD)
		{
			bSOD = FALSE; // set up variable to disable blue screen of death	
			stopGame(); // set up variables to end game and dispaly game over screen
		}

		if(introPrompt1)
		{
			// disables intro screen 1
			introPrompt1 = FALSE;

			// sets up speed delay and points multiplier
			pointMulti = 3;
			speedDelay = 138;

			// set up the variable for  intro screen 2
			introPrompt2 = TRUE;
			repaint(); // calls a paint event
		}
        }
        break;

	// During intro screen 1, this sets up speed delay and points multiplier, 
	// and then it will set up the variable for  intro screen 2
    	case Qt::Key_4: // '4' was pressed
        { 
		if(bSOD)
		{
			bSOD = FALSE; // set up variable to disable blue screen of death	
			stopGame(); // set up variables to end game and dispaly game over screen
		}

		if(introPrompt1)
		{
			// disables intro screen 1
			introPrompt1 = FALSE;

			// sets up speed delay and points multiplier
			pointMulti = 4;
			speedDelay = 107;

			// set up the variable for  intro screen 2
			introPrompt2 = TRUE;
			repaint(); // calls a paint event
		}
        }
        break;

	// During intro screen 1, this sets up speed delay and points multiplier, 
	// and then it will set up the variable for  intro screen 2
    	case Qt::Key_5: // '5' was pressed
        { 
		if(bSOD)
		{
			bSOD = FALSE; // set up variable to disable blue screen of death	
			stopGame(); // set up variables to end game and dispaly game over screen
		}

		if(introPrompt1)
		{
			// disables intro screen 1
			introPrompt1 = FALSE;

			// sets up speed delay and points multiplier
			pointMulti = 5;
			speedDelay = 75;

			// set up the variable for  intro screen 2
			introPrompt2 = TRUE;
			repaint(); // calls a paint event
		}
        }
        break;

	// During intro screen 1, this sets up speed delay and points multiplier, 
	// and then it will set up the variable for  intro screen 2
    	case Qt::Key_9: // '9' was pressed
        { 
		if(bSOD)
		{
			bSOD = FALSE; // set up variable to disable blue screen of death	
			stopGame(); // set up variables to end game and dispaly game over screen
		}

		if(introPrompt1)
		{
			// disables intro screen 1
			introPrompt1 = FALSE;

			// sets up speed delay and points multiplier
			pointMulti = 1000;
			speedDelay = 0;

			// set up the variable for  intro screen 2
			introPrompt2 = TRUE;
			repaint(); // calls a paint event
		}
        }
        break;

	// If Victory or Game Over screen, sets up the variables for intro screen 1.
	// If BSOD, then sets up variables to end game and dispaly game over screen.
    	case Qt::Key_Space: // The Space Bar was pressed
        {
		if(bSOD)
		{
			bSOD = FALSE; // set up variable to disable blue screen of death	
			stopGame(); // set up variables to end game and dispaly game over screen
		}
		else if(!introPrompt1 && !introPrompt2 && gameEnded)
		{
			// sets up the variables for  intro screen 1
			introPrompt1 =TRUE;
			gameOver = FALSE;
			gameWon = FALSE;
			gameEnded = FALSE;
			repaint(); // calls a paint event
		}

        }
        break;

	// Exits App
    	case Qt::Key_Escape: // The Esc key was pressed
        {
          	qApp->exit();
        }
        break;

	// During BSOD, sets up variables to end game and dispaly game over screen
    	default: // Any other Key was pressed
	{
		if(bSOD)
		{
			bSOD = FALSE; // set up variable to disable blue screen of death	
			stopGame();  // set up variables to end game and dispaly game over screen
		}
	}

	QWidget::keyPressEvent(event);
    }
}

/*! \brief If game is not started, resets data members to default values,  
 * deletes Snake, creates a new Snake to default length and position, and moves food.
 * Precondition: Game is not started and a 'Y' or 'N' was pressed during intro Screen 2.
 * Postcondition: Game is started and Snake is centered on screen. */
void Game::startGame()
{ 
  	if (!gameStarted) // If game hasn't started
	{
		if(snake)
			{delete snake;} // If snake created, deletes Snake
		snake = new Snake(); // creates a new Snake to default length and position
		
		// Resets data members to default values
			points = 0;
			growCount = 0;
	    		timerId = startTimer(speedDelay);

	    		gameStarted = TRUE;
	    		gameOver = FALSE; 
	    		gameWon = FALSE;
			gameEnded = FALSE; 
	    		bSOD = FALSE; 

			deathSpawn = FALSE;
			deathCounter = 0;
			doOneTime = TRUE;

			spawnWinnerCount = 0;
			winSpawn = FALSE;
			winCounter = 0;

			paused = FALSE;

			fixCount = FALSE;

			switchFood = 0;

			/* Prevents Red Apple logo from spawning twice in a row at the start*/
			// move food (Apple logos) to new location and make sure it is not on top of anything
			do{
				food->moveFood(switchFood);
			}while(snake->checkBadFood(food));
  	}
}

/*! \brief Pauses and Unpauses a started game.
 * Precondition: Game is started and 'P' is pressed, or Game is paused and 'P' or a directional key is pressed.
 * Postcondition: If game is started, the game is paused. If game is paused, game is unpaused.*/
void Game::pauseGame()
{
	if(gameStarted) //if Game is started
  	{
		if (paused) // if paused, resume game
		{
	    		timerId = startTimer(speedDelay); // starts new timer
	    		paused = FALSE;
			lastDir = ' '; //resets last direction to nothing
	  	} 
		else // if game is not paused, pause game
		{
	    		paused = TRUE;
	    		killTimer(timerId); // kills current timer
	   	} 
	}
}

/*! \brief Stops the game and the timer, sets up variables to paint the gameOverScreen, and calls a paint event.
 * Precondition: Snake makes an illegal collision or any key is pressed during the Blue Screen of Death.
 * Postcondition: The paint event will display the gameOverScreen.*/
void Game::stopGame()
{
  	killTimer(timerId); // kills current timer

	// Sets up variables to paint the gameOverScreen
  	gameOver = TRUE;    
  	gameEnded = TRUE;  
  	gameStarted = FALSE;
  	repaint(); // calls a paint event
}

/*! \brief Stops the game and the timer, sets up variables to paint the victoryScreen, and calls a paint event.
 * Precondition: If snake collides with foodWinner, game is started and 'V' is pressed, or growCount == 315.
 * Postcondition: The paint event will display the victoryScreen.*/
void Game::victory()
{
  	killTimer(timerId); // kills current timer

	// Sets up variables to paint the victoryScreen
  	gameWon = TRUE;   
  	gameEnded = TRUE;   
  	gameStarted = FALSE;
  	repaint(); // calls a paint event
}

/*! \brief Stops the timer, sets up variables to paint the Blue Screen of Death, sets points to zero,
 * and calls a paint event.
 * Precondition: If snake collides with specialFood, or game is started and '8' is pressed.
 * Postcondition: Points are set to zero and the paint event will display the Blue Screen of Death.*/
void Game::blueScreenDeath()
{
 	killTimer(timerId);  // kills current timer

	// Sets up variables to paint the Blue Screen of Death
  	bSOD = TRUE; 
  	points = 0;
  	repaint(); // calls a paint event
}

/*! \brief The screen that is displayed when a Game Over occurs.
 * Precondition: Paint event is called and gameOver is true.
 * Postcondition: gameOverScreen is displayed.		
 * \param QT Qpainter object reference. */
void Game::gameOverScreen(QPainter &painter)
{
    	QFont font("Courier", 15, QFont::DemiBold);
	QFontMetrics fm(font);
	int textWidth = fm.width("Game Over");

	painter.setFont(font);
	int h = height();
	int w = width();

	painter.translate(QPoint(w/2, h/2));
	painter.drawText(-textWidth/2, -16, "Game Over");

	int textWidth2 = fm.width("Total Points: " + QString::number(points));
	painter.drawText(-textWidth2/2, 0, "Total Points: " + QString::number(points));

	int textWidth3 = fm.width("Press the Space Bar to Restart!");
	painter.drawText(-textWidth3/2, 16, "Press the Space Bar to Restart!");

	lastDir = ' '; // resets last direction to nothing
}

/*! \brief The screen that is displayed when a Victory occurs.
 * Precondition: Paint event is called and gameWon is true.
 * Postcondition: victoryScreen is displayed.
 * \param QT Qpainter object reference. */
void Game::victoryScreen(QPainter &painter)
{
	victoryScreenImage.load("victoryScreen.png");
	victoryScreenRect = victoryScreenImage.rect();
	victoryScreenRect.moveTo(28,150);

	painter.drawImage(victoryScreenRect, victoryScreenImage);

    	QFont font("Courier", 15, QFont::DemiBold);
	QFontMetrics fm(font);
	int textWidth = fm.width("Victory!!!");

	QPen pen;
	pen.setColor(Qt::white);
	painter.setPen(pen);
		
	painter.setFont(font);
	int w = width();

	painter.translate(QPoint(w/2, 150+64+32));
	painter.drawText(-textWidth/2, -32, "Victory!!!");

	int textWidth1 = fm.width("You have installed Linux!!!" );
	painter.drawText(-textWidth1/2, -16, "You have installed Linux!!!");

	int textWidth2 = fm.width("Total Points: " + QString::number(points));
	painter.drawText(-textWidth2/2, 0, "Total Points: " + QString::number(points));

	int textWidth3 = fm.width("Press the Space Bar to Restart!");
	painter.drawText(-textWidth3/2, 16, "Press the Space Bar to Restart!");

	lastDir = ' '; //resets last direction to nothing
}

/*! \brief Paints points on the status bar on the iphone.
 * Precondition: Paint event is called and either gameStarted or BSOD is true.
 * Postcondition: Points are displayed on status bar of iphone.
 * \param QT Qpainter object reference. */
void Game::getPoints(QPainter &painter)
{
	QFont font("Courier", 15, QFont::DemiBold);
	QFontMetrics fm(font);
	int textWidth = fm.width("Points: " + QString::number(points));

	painter.setFont(font);
	int w = width();

	painter.translate(QPoint(w/2, 145));
	painter.drawText(-textWidth/2, 0, "Points: " + QString::number(points));
}

/*! \brief Paints the intro screens on the screen of the iphone.
 * Precondition: Paint event is called and either introPrompt1 or introPrompt2 is true.
 * Postcondition: Either intro screen 1 or intro screen 2 is displayed.
 * \param QT Qpainter object reference. */
void Game::introScreen(QPainter &painter)
{
	//Paints intro screen 1 on the screen of the iphone.
	if(introPrompt1)
	{
	    	QFont font("Courier", 14, QFont::DemiBold);
    		QFontMetrics fm(font);
    		int textWidth = fm.width("Let's Play Snake!!!");

    		painter.setFont(font);
    		int h = height();
    		int w = width();

    		painter.translate(QPoint(w/2, h/2));
    		painter.drawText(-textWidth/2, -16, "Let's Play Snake!!!");

		int textWidth2 = fm.width("Select the Speed.");
    		painter.drawText(-textWidth2/2, 0, "Select the Speed!");

		int textWidth3 = fm.width("Enter a number from 1 to 5.");
    		painter.drawText(-textWidth3/2, 16, "Enter a number from 1 to 5:");

		int textWidth4 = fm.width("1 (Slowest) and 5 (Fastest)");
    		painter.drawText(-textWidth4/2, 32, "1 (Slowest) and 5 (Fastest)");

		lastDir = ' '; //resets last direction to nothing
	}
	//Paints intro screen 2 on the screen of the iphone.
	else if(introPrompt2)
	{
	    	QFont font("Courier", 14, QFont::DemiBold);
    		QFontMetrics fm(font);
    		int textWidth = fm.width("Let's Play Snake!!!");

    		painter.setFont(font);
    		int h = height();
    		int w = width();

    		painter.translate(QPoint(w/2, h/2));
    		painter.drawText(-textWidth/2, -16, "Let's Play Snake!!!");

		int textWidth2 = fm.width("Enable Wrap Around???");
    		painter.drawText(-textWidth2/2, 0, "Enable Wrap Around???");

		int textWidth3 = fm.width("Press 'Y' for Yes and 'N' for No.");
    		painter.drawText(-textWidth3/2, 16, "Press 'Y' for Yes and 'N' for No.");

		lastDir = ' '; //resets last direction to nothing
	}

}

/*! \brief Carries out actions if snake collided with something.
 * Precondition: The Snake is moved by a directional key press or a timer event.
 * Postcondition: Specific action carried out according to what the snake collided with.*/
void Game::checkCollision()
{
	/* Prevents game from crashing at when the snake is bigger than 318 SnakeBlocks */
	// If snake takes up 98% of screen, then VICTORY!!!
	if(growCount == 315)
		{victory();}

	if(winSpawn)
	{
		//If Snake collides with foodWinner (Linux logo), end game and set up victory screen
		if ((foodWinner->getRect()).intersects(snake->getRect())) 
		{
			victory();
		}
	}
	else if(deathSpawn)
	{
		//If Snake collides with specialFood (Windows 8 logo), kill timer and set up the Blue screen of death
		if ((specialFood->getRect()).intersects(snake->getRect())) 
		{
			blueScreenDeath();
		}
	}
	

	if(spawnWinnerCount % 1000 == 0 && spawnWinnerCount != 0 && doOneTime)
	{
		// set up variables to paint foodWinner (Linux logo)
		deathSpawn = FALSE;
		winSpawn = TRUE;
		doOneTime = FALSE;

		// move foodWinner (Linux logo) to new location and make sure it is not on top of anything
		do{
			foodWinner->moveFood(food);		  	

		}while(snake->checkBadFood(foodWinner));
	}
	else if(growCount%10==0 && growCount != 0 && doOneTime)
	{
		// set up variables to paint specialFood (Windows 8 logo)
		deathSpawn = TRUE;
		doOneTime = FALSE;

		/* Resolving specialFood respawn issues */
		growCount++; //Prevents respawn of specialFood, if snake hasn't grown again after 100 paints
		fixCount = TRUE; //fixs growCount next grow

		// move specialFood (Windows 8 logo) to new location and make sure it is not on top of anything
		do{
			specialFood->moveFood(food);		  	

		}while(snake->checkBadFood(specialFood));
	}

	// If snake collides with food (Apple logos), then switch food images, move food, grow snake, and increase points
	if ((food->getRect()).intersects(snake->getRect())) 
	{   	
		// Sets up variable to switch food images
		switchFood++;// increments Apple logo switcher
	    	switchFood %= 2; // if Apple logo switch equals 2, set it back to zero

		// move food (Apple logos) to new location and make sure it is not on top of anything
		do{
			if(winSpawn)
				food->moveFood(foodWinner,switchFood);
			else if(deathSpawn)
				food->moveFood(specialFood,switchFood);
			else
	  			food->moveFood(switchFood);

		}while(snake->checkBadFood(food));

		// Grows snake
		snake->grow();
		growCount++; // increases grow count
		
		/* Resolving specialFood respawn issues */
		// Fixes growCount if it was incremented earlier 
		if(fixCount == TRUE) 
		{
			growCount--;
			fixCount = FALSE;
		}

		// Increases points
		points += 7*pointMulti;
	}

	// If snake head (front of snake) collides with the rest of 
	// the snake, stop the game and display the Game Over screen.
	if(snake->checkCollision()) 
		{stopGame();}

	// If wrapAround is disabled and the snake head (front of snake) 
	// goes off screen, stop the game and display the Game Over screen.
	if(wrapAround == FALSE)	
	{
		if(snake->hitsWall())
			{stopGame();}
	}
}
