  Hello player,

  This project is Silly Dying Larry's manual.
  Silly Sying Larry (SDL) is a very fun platformer made with SDL2 developped in
  C language.


  *** Launching ***

  First compile the game with (you need to be at the root of the project):
          42sh$ make
  In order to launch the game, type on your prompt:
          42sh$ ./Silly-Dying-Larry

  You can add in parameters the size of the screen you want to have.

  *** Keys ***
  
  Escape -> go back to previous window / quit the game
  Left Arrow -> move to the left
  Right Arrow -> move to the right
  Up Arrow -> Jump

  *** Menu ***

  When launched, the program opens the menu window.
  This window has three buttons: the first one to play, the second one to put
  fullscreen mode and the third one to quit.
  If the "play" button is selected, another menu is displayed, offering the
  different existing levels.
  In order to navigate through the menu, you can use your mouse or the arrows
  and enter keys.

  *** Movements ***

  Larry can move in three different ways:
    -> Go left (left arrow from keyboard)
    -> Go right (right arrow from keyboard)
    -> Jump (up arrow from keyboard)

  *** Debug ***

  If any freeze occurs, you can press 'Y' to reload the stage.

  *** Goal ***

  The goal of this game is to get to the "Larry V" block without being caught by
  one of the mean guys or getting wet.


  *** Enemies ***

  The enemies are represented by the red angry cubes. If an enemy touches Larry,
  Larry dies.
  Larry has two types of enemies:

  -> Terrestrians:
  This type of enemies can move from left to right and over the grass only.
  If Larry is far, terrestrians will simply move from the left to the right side
  of the grass.
  Else, if Larry is close to terrestrians, they will follow Larry and try to
  catch him.

  -> Floaters:
  Floating enemies simply move from left to right and over the grass area, but
  thet float.


  *** Water ***

  Larry is a good lad, but Larry does not take showers. Don't step into the
  water, otherwise Larry loses.



  *** Clouds ***

  Larry can walk over the clouds!!! You can use this in order to make your game
  easier... Or harder.

  *** Screenshots ***

  ![](menu.png)
  ![](levels.png)
  ![](playing.png)
