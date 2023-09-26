// The program allows you to select from a list of players those who will participate in a specific game. Afterwards, the program will automatically create a corresponding list of players

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100
#define MAX_NAME_LENGTH 25
#define TA_MMB_NR_LENGTH 3

typedef struct Player
{
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];
    int taMmbNr[TA_MMB_NR_LENGTH];
} Player;

// Prints the passed string to the console
void printString(char *string)
{
    for(int i = 0; i < strlen(string); i++)
    {
        printf("%c", string[i]);
    }
}

// Clears the passed string
void clearString(char *string)
{
    for(int i = 0; i < strlen(string); i++)
    {
        string[i] = 0;
    }
}

// Extracts the player information from the passed line and assigns it to the passed player
void extractPlayerFromLine(char *line, Player *playerPointer)
{
    // 'charsWithinLineCounter' is used to iterate through the String 'line'
    int charsWithinLineCounter = 0;
    // 'charsWithinWordCounter' is used to iterate over the individual words within 'line'
    int charsWithinWordCounter = 0;

    // Extract the first word from 'line' and assign it to 'firstName' from the player (By specification of the input-file, the first word represents the first name of the player)
    while(line[charsWithinLineCounter] != ' ')
    {
        playerPointer->firstName[charsWithinWordCounter++] = line[charsWithinLineCounter++];
    }
    playerPointer->firstName[charsWithinWordCounter] = '\0';

    // Skip the whitespace character and reset 'charCounter' to 0
    charsWithinLineCounter++;
    charsWithinWordCounter = 0;

    // Extract the second word from 'line' and assign it to 'lastName' from the player (By specification of the input-file, the second word represents the first name of the player)
    while(line[charsWithinLineCounter] != ' ')
    {
        playerPointer->lastName[charsWithinWordCounter++] = line[charsWithinLineCounter++];
    }
    playerPointer->lastName[charsWithinWordCounter] = '\0';

    // Skip the whitespace character
    charsWithinLineCounter++;

    // Extract the TA-/MMB-Nr. from 'line' and assign it to the player
    for(charsWithinWordCounter = 0; charsWithinWordCounter < TA_MMB_NR_LENGTH; charsWithinWordCounter++)
    {
        playerPointer->taMmbNr[charsWithinWordCounter] = line[charsWithinLineCounter++] - '0';
    }
}

typedef struct Node
{
    Player *player;
    struct Node *next;
} Node;

// Appends the passed player to the end of the linked list
void appendPlayerToList(Node **root, Player player)
{
    // Allocate the required memory for a new node and a copy of the passed player
    Node *newNode = (Node*) malloc(sizeof(Node));
    Player *playerCopy = (Player*)malloc(sizeof(Player));
    // Check if the required memory has been allocated successfully
    if(newNode == NULL || playerCopy == NULL)
    {
        printf("Error: The memory cannot be allocated!");
        exit(1);
    }

    // Copy the passed player
    strcpy(playerCopy->firstName, player.firstName);
    strcpy(playerCopy->lastName, player.lastName);
    for(int i = 0; i < TA_MMB_NR_LENGTH; i++)
    {
        playerCopy->taMmbNr[i] = player.taMmbNr[i];
    }

    // Set the attributes of the previously created node
    newNode->player = playerCopy;
    newNode->next = NULL;

    // Check if the linked list is currently empty
    if(*root == NULL)
    {
        // If the list is empty, set the new node to the first element of the list
        *root = newNode;
    }
    else
    {
        // If the list already contains elements, assign the new node to 'next' of the current last node
        Node *current = *root;
        while(current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Prints the information of the player to the console
void printPlayer(Player *player)
{
    // Print the TA-/MMB-Nr. to the console
    for(int i = 0; i < TA_MMB_NR_LENGTH; i++)
    {
        printf("%d", player->taMmbNr[i]);
    }
    printf(" ");
    // Print the players name to the console
    printString(player->lastName);
    printf(", ");
    printString(player->firstName);
}

// Prints all elements of the passed list to the console
void printList(Node *root)
{
    int counter = 1;
    // Check if the list is empty
    if(root != NULL)
    {
        // If the list is not empty, iterate through the linked list and print the current player to the console
        Node *current = root;
        while(current->next != NULL)
        {
            printf("%d: ", counter++);
            printPlayer(current->player);
            printf("\n");
            current = current->next;
        }
        // Print the last element of the list to the console
        printf("%d: ", counter);
        printPlayer(current->player);
        printf("\n");
    }
    else
    {
        printf("Error: The list is empty!");
    }
}

// Returns the size of the passed list (The size corresponds to the number of elements within the list)
int calculateListSize(Node *root)
{
    // Return 0 if the list is empty
    if(root == NULL)
    {
        return 0;
    }

    // Iterate through the list and count all elements
    int counter = 1;
    Node *current = root;
    while(current->next != NULL)
    {
        counter++;
        current = current->next;
    }

    return counter;
}

// Returns the player who is at the passed position in the list (The positions are defined so that the first element has the value 1)
Player *getPlayerFromList(Node *root, int position)
{
    // Return NULL if the list is empty
    if(root == NULL)
    {
        return NULL;
    }

    // Return NULL if the passed position lies outside the bounds of the list
    int listSize = calculateListSize(root);
    if(position < 1 || position > listSize)
    {
        return NULL;
    }

    // Iterate through the list and determine the player who is located at the passed position
    Player *player;
    int counter = 1;
    Node *current = root;
    while(current->next != NULL)
    {
        if(position == counter++)
        {
            player = current->player;
        }
        current = current->next;
    }
    if(current->next == NULL && position == counter)
    {
        player = current->player;
    }

    return player;
}

// // Prints the information of the player to the passed file
void printPlayerToFile(Player *player, FILE *file)
{
    // Convert the TA_MMB_NR from int[] to char[].
    char TA_MMB_NR[TA_MMB_NR_LENGTH];
    for(int i = 0; i < TA_MMB_NR_LENGTH; i++)
    {
        TA_MMB_NR[i] = player->taMmbNr[i] + '0';
    }
    TA_MMB_NR[TA_MMB_NR_LENGTH] = '\0';

    // Print the player in the correct format to the file
    fputs(TA_MMB_NR, file);
    fputs(" ", file);
    fputs(player->lastName,file);
    fputs(", ", file);
    fputc(player->firstName[0], file);
    fputs(".\n", file);
}

int main()
{
    // Create the roots of two linked lists
    Node *rootInputList = NULL;
    Node *rootOutputList = NULL;

    // Open the input file using the mode 'reading'
    FILE *inputFile;
    inputFile = fopen("Player_Lists/Playerlist_Input.txt", "r");

    // If the input file can be opened, go through the file and create a linked list of players based on the player information contained in it
    if (inputFile != NULL)
    {
        char currentCharacter;
        int charsWithinFileCounter = 0;
        int charsWithinLineCounter = 0;
        // Go through the file character by character
        while( (currentCharacter = fgetc(inputFile)) != EOF )
        {
            // Create a string containing the current line of the input file. When done, extract a new player from it and then add the player to the list
            char currentLine[MAX_LINE_LENGTH];
            if(currentCharacter == '\n')
            {
                // If the end of the line is reached, end the string, create a new player and add the player to the linked list

                // End the string
                currentLine[charsWithinLineCounter] = '\0';

                // Create a new player, extract the player information from the input-file and add the player to the linked list
                Player newPlayer;
                Player *newPlayerPointer = &newPlayer;
                extractPlayerFromLine(currentLine, newPlayerPointer);
                appendPlayerToList(&rootInputList, newPlayer);

                // Reset the 'charsWithinLineCounter' and clear 'currentLine'
                charsWithinLineCounter = 0;
                clearString(currentLine);
            }
            else
            {
                // If the current character is not the end of the file, append the current character to 'currentLine' and update the relevant counters by one
                currentLine[charsWithinLineCounter++] = currentCharacter;
                charsWithinFileCounter++;
            }
        }

        fclose(inputFile);
    }
    else
    {
        printf("Error: The input file could not be opened!\n");
        exit(2);
    }

    // From the previously created list, let the user create a new list, by selecting those players, who will play in the next game
    printf("Select the players by entering the corresponding numbers. Type 0 when you are done.\n");
    printList(rootInputList);
    printf("\n");

    int inputListSize = calculateListSize(rootInputList);
    int selection = -1;
    while(1)
    {
        printf("Selection: ");
        scanf("%d", &selection);

        // Leave the loop, when the user is done selecting the players
        if(selection == 0)
        {
            break;
        }
        // If the input is valid, add the selected player to the new list
        else if(selection > 0 && selection <= inputListSize)
        {
            appendPlayerToList(&rootOutputList, *getPlayerFromList(rootInputList, selection));
        }
        else
        {
            printf("Error: Invalid input!\n");
        }
    }

    // Open the output file using the mode 'writing'
    FILE *outputFile;
    outputFile = fopen("Player_Lists/Playerlist_Output.txt", "w");

    // If the output file can be opened, write the list of player who will play in the next game into the output file
    if(outputFile != NULL)
    {
        if(rootOutputList != NULL)
        {
            // Iterate through the list and print the current player to the output file
            Node *current = rootOutputList;
            while(current->next != NULL)
            {
                printPlayerToFile(current->player, outputFile);
                current = current->next;
            }
            // Print the last player in the list to the output file
            printPlayerToFile(current->player, outputFile);
        }
        else
        {
            printf("Error: The list is empty!\n");
        }
    }
    else
    {
        printf("Error: The output file could not be opened!\n");
        exit(3);
    }

    fclose(outputFile);
    return 0;
}
