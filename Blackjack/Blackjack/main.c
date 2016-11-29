//
//  main.c
//  Blackjack
//
//  Created by jerremy ferrer & duc nguyen
//  CS 49c
//
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct card{
    int face; //hold index of face in face[]
    int suite; //hold index of suit in suit[]
    struct card *next; //pointer to next card
} Card;

typedef struct hand{
    Card card; //hold first card of hand, Set card = NULL if empty hand
    int numOfCard;
} Hand;

typedef struct player{
    char name[20];
    int cash;
    Hand hand;
} Player;

//prototypes
void mainMenu(int count, Player *playerList);
void newPlayer(Player player);
void playGame(Player *playerList, int count);
void shuffle( int [][ 13 ] );
void dealSingle( const int wDeck[][ 13 ], Card *newCard, unsigned int *cardIndex);
void deal( const int wDeck[][ 13 ],  Card *newCard, unsigned int *cardIndex, int numOfCardToDeal);
int getPoints(Card card);
void addToHand(Hand *hand, Card newCard);

//Hold cards
const char *suit[ 4 ] = { "Hearts", "Diamonds", "Clubs", "Spades" };
const char *face[ 13 ] = { "Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
int deck[ 4 ][ 13 ] = { 0 };

int main(int argc, const char * argv[]) {
    
    printf("Test functions: \n");
    shuffle(deck);
    printf("\tShuffled deck\n");
    unsigned int cardIndex = 0;
    Card newCard;
    deal(deck, &newCard, &cardIndex, 1);
    printf("\tDeal card: %s of %s\n", face[newCard.face], suit[newCard.suite]);
    Hand newHand;
    printf(" print empty hand: %d\n\n", newHand.card.face);
    
    
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
    shuffle(deck);
    
    
}

//Shuffle the deck
void shuffle( int wDeck[][ 13 ] )
{
    int row, column, card;
    time_t t;
    srand((unsigned) time(&t));
    
    for ( card = 1; card <= 52; card++ ) {
        do {
            row = rand() % 4;
            column = rand() % 13;
        } while( wDeck[ row ][ column ] != 0 );
        
        wDeck[ row ][ column ] = card;
    }
}

void dealSing( const int wDeck[][ 13 ], Card *newCard, unsigned int *cardIndex){
    return deal(wDeck, newCard, cardIndex, 1);
}

//Deal 1 card and save it to pointer card
void deal( const int wDeck[][ 13 ], Card *newCard, unsigned int *cardIndex, int numOfCardToDeal)
{
    int row, column;
    unsigned int finalCardIndex = *cardIndex + numOfCardToDeal;
    //    printf("carIndex: %u", *cardIndex);
    //    printf("finalCardIndex: %u", finalCardIndex);
    
    for ( ; *cardIndex < finalCardIndex; *cardIndex = *cardIndex + 1 )
        
        for ( row = 0; row <= 3; row++ )
            
            for ( column = 0; column <= 12; column++ )
                
                if ( wDeck[ row ][ column ] == *cardIndex ){
                    newCard->face = column;
                    newCard->suite = row;
                    printf( "\t%5s of %-8s%c",
                           face[ column ], suit[ row ],
                           *cardIndex % 2 == 0 ? '\n' : '\t' );
                }
}

/*
 *
 * Check player hand and return points of hand
 * @param card the first card of player
 */
int getPoints(Card card){
    
    int totalPoint = 0;
    int numOfAce = 0;
    
    while (card.next!=NULL) {
        int cardValue = card.face + 1;
        
        if(cardValue==1){
            ++numOfAce;
            continue;
        }
        
        if (cardValue>10) {
            cardValue = 10;
        }

        totalPoint+=cardValue;
        
        card=*card.next;
    }
    
    while (numOfAce>0) {
        if (totalPoint) {
            <#statements#>
        }
    }
    return totalPoint;
}

//add a card to hand
void addToHand(Hand *hand, Card newCard){
    //if hand is empty
    if (hand->numOfCard==0) {
        hand->card = newCard;
    }
    else
    {
        newCard.next = &hand->card;
        hand->card = newCard;
        hand->numOfCard++;
    }
}
