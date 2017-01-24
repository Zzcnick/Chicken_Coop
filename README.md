# Chicken_Coop: Sarah Yoon (Pd. 10) and Zicheng Zhen (Pd. 4)

## Command Line Set (Part Deux)

### List of Files in Repository
* DESIGN.txt
* README.txt
* DEVLOG.txt
* h.txt - Where scores are saved.
* board.h, board.c
* set.h, set.c
* highscore.h, highscore.c
* setserver.h, setserver.c
* makefile

### Compilation Instructions
* In order to generate the files required for the game, run the following:
  * `$ make`
  * `$ make run`
* When prompted, enter a username.
* In order to navigate the menu, simply type the number of the option you wish to choose.
* You may enter input straight into the command line. 

### Gameplay Basics
* The grid of strings presented to you represent a grid of Set cards.
* The brackets around each - (), [], or {} - represent the card's "shading."
* The card's "number" (number of letters for that card) will either be 1, 2 or 3.
* The card's "shape" is represented by the letter that appears either once, twice or thrice. It will either be O, X, or S.
* The card's "color" will either be red, green, or blue, and the card will be printed in that color in terminal.
* Whenever prompted to enter a set, enter the cards' coordinates in the following format (case-sensitive!): A0 B1 C2
* A Set is defined as follows:
  * For each of the four attributes (shading, number, shape, and color), the three cards are either all the same or all different.
* Input must be given in the form "A0 B1 C2."
* When given the option to either play (1) Single Player or (2) Multi-Player...

#### Single Player
* After running `$ make run`, type '1' and hit enter.
* Each time you enter a set correctly, the time it took you to do so (including failed attempts) is reported and recorded.
* The average time it takes you per Set is your score for the game. Your username and score will be saved in a text file, the contents of which will be printed out for you to see immediately after having finished your game.

#### Multi-Player
* After running `$ make run`, type '2' and hit enter.
  * You will be able to select '1' or '2' in order to choose whether you would like to host a server or join a server.
    * Hosting: Type '1' and enter, and wait for a connection. When a client connects, the game will begin automatically.
    * Joining: Type '2' and enter. You will be prompted to enter an IP address in the form ###.###.###.###. If you would like to connect to a local host, type 127.0.0.1. If a server is available to handle the request, you will join the game and play will begin automatically.
  * Scoring is done in terms of sets found; whoever finds more sets when the deck runs out will have a higher score. This is not logged in the highscore file.
  
### Notes
* Both players may send input simultaneously to the server.
* In order for the parsing to work properly, the input must follow the desginated format of LETTER-NUMBER-SPACE-LETTER-NUMBER-SPACE-LETTER-NUMBER. Each letter will represent the row of a card, and each number will represent the volumn. The order of the cards may be switched around. (i.e. A0 B1 C2 and C2 B1 A0 are both valid.)
* If the parsing is not followed, the scoring mechanism may not work for multiplayer mode.
* Occasionally, when hosting between separate machines, static will appear in the terminal; the cause of this static is unknown. 
* If you are hosting the client locally, trying to join a multiplayer match that is not open may cause the client to crash and be unable to open another connection for several minutes; the cause of this is also unknown.
