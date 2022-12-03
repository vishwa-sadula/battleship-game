# BATTLESHIP GAME
A console based 2-player game made using c++.

### Game Objective
The objective of Battleship is to try and sink all the other player's ships before they sink all your ships. All the 
other player's ships are somewhere on his/her board. You try and hit them by calling out the
coordinates of one of the squares on the board. The other player also tries to hit your ships by calling
out coordinates. Neither you nor the other player can see the other's board so you must try to guess
where they are.

### Planning Phase
Each player places the 5 ships somewhere on their board. The ships can only be placed vertically or
horizontally. Diagonal placement is not allowed. Ships cannot hang off the board, nor can they be placed
one over another.
Once the guessing begins, the players may not move the ships.
The 5 ships are: Aircraft carrier (occupies 5 spaces), Battleship (4 spaces), Destroyer (3 spaces), Corvette
(2 spaces) and Frigate (1 space)

### Guessing Phase
Players take turns guessing by calling out the coordinates. The opponent responds with "hit" or "miss"
as appropriate. The grids get updated as: "H" for hit, "*" for miss. 

_For example, if you call out F6 and your opponent does not have any ship located at F6, your opponent will respond
with "miss". And the grid will be updated with * at F6._

When all the squares that one of your ships occupies have been hit, the ship will be "hit and sunk" and represented with "S".
As soon as all of one player's ships have been sunk, the game ends.

### Your grid will look something like below:

```
   A B C D E F G H I J
 1 . . . . . . . . . .
 2 A . . . . . . . . D
 
 3 A . . . . . . . . D
 
 4 A . . . . . . . . D
 
 5 A . . . . . . . . D
 
 6 A B B B . . . . . .
 
 7 . . . . . . . . . .
 
 8 . . . . . . . E . .
 
 9 C C . . . . . . . .
 
 10 . . . . . . . . . .
 
```
