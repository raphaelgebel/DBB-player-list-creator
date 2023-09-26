# DBB-player-list-creator
Creates a player list with the required information for DBB basketball games.

# About the project
### Context/Background:
As a basketball coach at the DBB amateur level, you have to hand in a player list to the scorekeeper before a game. This list must contain the required player information such as the TA-/MMB-Nr. (an important three-digit number on the player's pass), the name of the player and the jersey number.
### Problem solving:
I wrote this program in order to avoid having to create such a list manually for each game.

# How it works
The program allows you to select from all of your own players those who will play in a particular match (The list of all your players is stored in the file 'Player_Lists/Playerlist_Input.txt'). Then the program automatically creates a corresponding list of players and stores it in the file 'Player_Lists/Playerlist_Output.txt'. (I didn't include the jersey numbers in the program, because they are not fixed, but are assigned every time before the match).

# Example with made up player information
![screenshot player list example](https://github.com/raphaelgebel/DBB-player-list-creator/assets/98976609/6191fd2f-ba67-4a93-8c1d-e1fce0419b4a)

Result stored in the file 'Player_Lists/Playerlist_Output.txt':
![Screenshot 2023-09-26 080646](https://github.com/raphaelgebel/DBB-player-list-creator/assets/98976609/415cdc1f-3550-4f59-9ae5-254d8275a30f)

# Specification of the input-file
For the program to work, the input-file must be created according to the following specifications:
- The first word in a line represents the last name.
- The second word in a line represents the first name.
- The third character sequence represents the so called 'TA-/MMB-Nr.'.
- Between each of these three character sequences there must be exactly one blank character.

# Concepts from C that I have implemented
- Structures
- Pointer arithmetic
- File Handling
- Dynamic Memory Allocation
- Singly Linked Lists
