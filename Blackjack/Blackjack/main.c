//
//  main.c
//  Blackjack
//
//  Created by jerremy ferrer & duc nguyen
//  CS 49c
//
//

#include <stdio.h>

typedef struct player{
    char name[20];
    int cash;
} Player;
//prototypes
void mainMenu(int count, Player *playerList);
void newPlayer(Player player);
void playGame(Player *playerList, int count);
void shuffle( int [][ 13 ] );
void deal( const int [][ 13 ], const char *[], const char *[], unsigned int *cardIndex, int hand[][2]);

int main(int argc, const char * argv[]) {
    int playerCount = 1; // initialize to 1 b/c dealer counts as a player
    Player playersList[] = {};
    printf("WELCOME TO BLACKJACK\n");
    
    mainMenu(playerCount, playersList);
    
    return 0;
}
/*
 * Displays main menu of the game
 * @param
 */
void mainMenu(int count, Player *playerList) {
    int selection = -1;
    
    
    printf("Select an option: [1] New Player - [2] Play - [3] (will add more options later)\n");
    scanf("%d", &selection);
    
    switch (selection) {
        case 1: // new player
            newPlayer(playerList[++count]);
            mainMenu(count, playerList);
            break;
        case 2: //play game
            playGame(playerList, count);
            break;
        default:
            break;
    }
}
/*
 * New player enters his/her new player information
 * @param
 */
void newPlayer(Player player) {
    printf("Please enter your name: \n");
    scanf("%s", &player.name);
    
    printf("Enter how much cash you wish to play with: \n");
    scanf("%d", &player.cash);
    
    //test
    printf("name: %s - cash: $%d\n", player.name, player.cash);
}
/*
 *
 * Simulates the gameplay between players and dealer
 * @param
 */
void playGame(Player *playerList, int count) {
    
    //TODO: call shuffle method, deal method
    
}
void shuffle( int wDeck[][ 13 ] )
{
    int row, column, card;
    
    for ( card = 1; card <= 52; card++ ) {
        do {
            row = rand() % 4;
            column = rand() % 13;
        } while( wDeck[ row ][ column ] != 0 );
        
        wDeck[ row ][ column ] = card;
    }
}
void deal( const int wDeck[][ 13 ], const char *wFace[], const char *wSuit[],
          unsigned int *cardIndex, int hand[][2])
{
    int row, column;
    unsigned int finalCardIndex = *cardIndex + 5;
    unsigned int handIndex = 0;
    //    printf("carIndex: %u", *cardIndex);
    //    printf("finalCardIndex: %u", finalCardIndex);
    
    for ( ; *cardIndex < finalCardIndex; *cardIndex = *cardIndex + 1 )
        
        for ( row = 0; row <= 3; row++ )
            
            for ( column = 0; column <= 12; column++ )
                
                if ( wDeck[ row ][ column ] == *cardIndex ){
                    hand[handIndex][0] = column;
                    hand[handIndex][1] = row;
                    ++handIndex;
                    printf( "\t%5s of %-8s%c",
                           wFace[ column ], wSuit[ row ],
                           *cardIndex % 2 == 0 ? '\n' : '\t' );
                }
    
}

