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
#include <stddef.h>

typedef struct card{
    int face; //hold index of face in face[]
    int suite; //hold index of suit in suit[]
    struct card *next; //pointer to next card
} Card;

typedef struct hand{
    Card card; //hold first card of hand, Set card = NULL if empty hand
    int numOfCard;
    int currentPoint;
} Hand;

typedef struct player{
    char name[20];
    int cash;
    Hand hand1;
    Hand hand2;
    int quit;
} Player;

//prototypes
void mainMenu(int *playerCount, Player *playerList);
void newPlayer(Player *player);
void playGame(Player *playerList, int *playerCount);
void shuffle( int [][ 13 ] );
void dealSingle( const int wDeck[][ 13 ], Hand *hand, unsigned int *cardIndex, int isDealer);
void deal( const int wDeck[][ 13 ],  Hand *hand, unsigned int *cardIndex, int numOfCardToDeal, int isDealer);
int getNewPoints(Hand *hand,Card card);
void addToHand(Hand *hand, Card newCard);
void displayCurrentHand(Hand *hand);
void subtractCash(Player player, int bet);
void addCash(Player player, int bet);
int getPlayerCash(Player player);
int atLeastOnePlayerIn(Player *playerList, int *playerCount);


//Hold cards
const char *suit[ 4 ] = { "Hearts", "Diamonds", "Clubs", "Spades" };
const char *face[ 13 ] = { "Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
int deck[ 4 ][ 13 ] = { 0 };

//Hold max number of player
#define MAX_PLAYER 5
#define INITIAL_CARDS 2

int main(int argc, const char * argv[]) {
    int playerCount = 1; // initialize to 1 b/c dealer counts as a player
    Player playersList[MAX_PLAYER];
    printf("WELCOME TO BLACKJACK\n");
    
    mainMenu(&playerCount, playersList);
    
    return 0;
}

/*
 * Displays main menu of the game
 * @param
 */
void mainMenu(int *playerCount, Player playerList[]) {
    int selection = -1;
    int i;
    //initialize playerlist back to 0
    for(i = 0; i < 5; i++){
        playerList[i].hand1.currentPoint = 0;
    }
    printf("Select an option: [1] New Player - [2] Play - [3] (will add more options later)\n");
    scanf("%d", &selection);
    
    switch (selection) {
        case 1: // new player
            newPlayer(&playerList[*playerCount]);
            *playerCount +=1;
            mainMenu(playerCount, playerList);
            break;
        case 2: //play game
        {
            for (size_t i = 0; i<*playerCount; ++i) {
                playerList[i].quit = 0;
            }
            playGame(playerList, playerCount);
        }
            break;
        default:
            break;
    }
}

/*
 * New player enters his/her new player information
 * @param
 */
void newPlayer(Player *player) {
    printf("Please enter your name: \n");
    //fgets(player->name, 20, stdin);
    scanf("%s", &player->name);
    
    printf("Enter how much cash you wish to play with: \n");
    scanf("%d", &player->cash);
    
    //test
    printf("name: %s - cash: $%d\n", player->name, player->cash);
}

/*
 *
 * Simulates the gameplay between players and dealer
 * @param
 */
void playGame(Player *playerList, int *playerCount) {
    
    
    
    
LOOP:   while (atLeastOnePlayerIn(playerList, playerCount) == 1) {
        puts("---top of while loop");
        //hold card index
        unsigned int cardIndex = 1;
        
        //hold variables
        size_t i;
        
        //hold array of points for each player
        int pointArray[MAX_PLAYER] = {0};
        
        int betArray[MAX_PLAYER] = {0};
        
        
        //shuffle the deck
        puts("---before shuffle called");
        shuffle(deck);
        puts("---after shuffle called");
        
        //Betting for each player
        for (i = 1; i<*playerCount; ++i) {
            puts("---inside for loop");
            if (playerList[i].quit == 0) {
                int input = 1;
                printf("\n (%s) Enter [0] if you wish to quit or [1] to continue\n", playerList[i].name);
                scanf("%d", &input);
                
                if (input == 0) {
                    playerList[i].quit = 1;
                    if (atLeastOnePlayerIn(playerList, playerCount)) {
                        continue;
                    } else {
                        mainMenu(playerCount, playerList);
                    }
                    
                } else {
                    printf("\n (%s) Enter a Bet (Min. = $5): \n", playerList[i].name);
                    scanf("%d", &betArray[i]);
                    
                    //test
                    printf("\n==TEST BEFORE BET: CURRENT CASH $%d", getPlayerCash(playerList[i]));
                    playerList[i].cash = playerList[i].cash - betArray[i];
                    //test
                    printf("\n==TEST AFTER BET: CURRENT CASH $%d", getPlayerCash(playerList[i]));
                }
            }
        } //end of for
        
        //Deal first hand
        for (i = 0; i<*playerCount; ++i) {
            if (playerList[i].quit == 0) {
                if (i == 0) {
                    //test
                    printf("\nDealer Hand\n");
                    deal(deck, &playerList[i].hand1, &cardIndex, 2, 0);
                    printf("\n--test-- dealing dealers cards (hidden)");
                } else {
                    printf("\nPlayer %s\n", playerList[i].name);
                    deal(deck, &playerList[i].hand1, &cardIndex, 2, 0);
                }
            }
        } //end of for
        
        //Ask if player want to stay or hit
        for (i = 1; i<*playerCount; ++i) {
            if (playerList[i].quit == 0) {
                int stay = 0;
                while (!stay) {
                    int decision;
                    
                    printf("\n (%s)Do you want to hit? [1] Yes - [0] No: \n", playerList[i].name);
                    fflush(stdin);
                    scanf("%d", &decision);
                    printf("Decision: %d\n", decision);
                    
                    switch (decision) {
                        case 1: {
                            
                            dealSingle(deck, &playerList[i].hand1, &cardIndex, 0);
                            displayCurrentHand(&playerList[i].hand1);
                            
                            
                        }
                            break;
                        case 0: {
                            stay = 1;
                            pointArray[i] = getNewPoints(&playerList[i].hand1, playerList[i].hand1.card);
                            printf("%s's point total: %d", playerList[i].name ,pointArray[i]);
                        }
                            break;
                            
                        default:
                            printf("\n ENTER VALID INPUT");
                            
                            break;
                    } //end of switch
                } //end of while
            } //end of if
        } //end of for
    
        //Get dealer point
        int dpoints = 0;
        dpoints = getNewPoints(&playerList[0].hand1, playerList[0].hand1.card);
        
        //Draw card if less than 16 points
        while ( dpoints < 16) {
            dealSingle(deck, &playerList[0].hand1, &cardIndex, 1);
            dpoints = getNewPoints(&playerList[0].hand1, playerList[0].hand1.card);
        }
        printf("\nDealer current point: %d\n", dpoints);
        
        //check winner of hand for each player
        for (i = 1; i<*playerCount; ++i){
            if (playerList[i].quit == 0){
                if (dpoints == pointArray[i]) {
                    printf("\n(%s) YOU PUSH!\n", playerList[i].name);
                    addCash(playerList[1], betArray[i]);
                    //test
                    printf("==TEST AFTER PUSH: CURRENT CASH $%d\n", getPlayerCash(playerList[1]));
                    
                } else if (dpoints > pointArray[i] ) {
                    if (pointArray[i] < 21 && dpoints <= 21) {
                        printf("\n(%s) YOU LOSE\n!", playerList[i].name);
                    } else if (pointArray[i] > 21 && dpoints > 21) {
                        printf("\n(%s) YOU PUSH!\n", playerList[i].name);
                        addCash(playerList[1], betArray[i]);
                        //test
                        printf("==TEST AFTER PUSH: CURRENT CASH $%d\n", getPlayerCash(playerList[1]));
                    }
                    
                } else if (dpoints < pointArray[i]) {
                    if (pointArray[i] <= 21 && dpoints < 21) {
                        printf("\n(%s) YOU WIN\n!", playerList[i].name);
                        addCash(playerList[1], betArray[i] * 2);
                        //test
                        printf("==TEST AFTER WIN: CURRENT CASH $%d\n", getPlayerCash(playerList[1]));
                    } else if (pointArray[i] > 21 && dpoints > 21) {
                        printf("\n(%s) YOU PUSH!\n", playerList[i].name);
                        addCash(playerList[1], betArray[i]);
                        //test
                        printf("==TEST AFTER PUSH: CURRENT CASH $%d\n", getPlayerCash(playerList[1]));
                    }
                    
                } else {
                    printf("\n UNTESTED");
                }
                
            }
           // pointArray[i] = 0;
        }
        //dpoints = 0;

    } //end of while loop
    
    //goes back to main menu,
    //mainMenu(playerCount, playerList);
}

//Shuffle the deck
void shuffle( int wDeck[][ 13 ] )
{
    int row, column, card;
    time_t t;
    srand((unsigned) time(&t));
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            wDeck[i][j] = 0;
        }
    }
    
    for ( card = 1; card <= 52; card++ ) {
        do {
            row = rand() % 4;
            column = rand() % 13;
        } while( wDeck[ row ][ column ] != 0 );
        
        wDeck[ row ][ column ] = card;
    }
}

void dealSingle( const int wDeck[][ 13 ], Hand *hand, unsigned int *cardIndex, int isDealer){
    return deal(wDeck, hand, cardIndex, 1, isDealer);
}

//Deal 1 card and save it to pointer card
void deal( const int wDeck[][ 13 ], Hand *hand, unsigned int *cardIndex, int numOfCardToDeal, int isDealer)
{
    int row, column;
    unsigned int finalCardIndex = *cardIndex + numOfCardToDeal;
    Card *ptr = &hand->card;
//    Card *previousPtr = NULL;
    //    printf("carIndex: %u", *cardIndex);
    //    printf("finalCardIndex: %u", finalCardIndex);
    
    for ( ; *cardIndex < finalCardIndex; *cardIndex = *cardIndex + 1 ){
        
        for ( row = 0; row <= 3; row++ ){
            
            for ( column = 0; column <= 12; column++ ){
                
                if ( wDeck[ row ][ column ] == *cardIndex ){
                    
                    while (ptr->next != NULL) {
                        ptr = ptr->next;
                    }
                    ptr->next = malloc(sizeof(Card));
                    ptr->next->face = column;
                    ptr->next->suite = row;
                    hand->numOfCard+=1;
                    
                    if (!isDealer) {
                        printf( "Card deal: \t%5s of %-8s%c\n",
                               face[ column ], suit[ row ],
                               *cardIndex % 2 == 0 ? '\n' : '\t' );
                    }
                    
                }
            }
        }
    }
}

/*
 *
 * Check player hand and return points of hand
 * @param card the first card of player
 */
int getNewPoints(Hand *hand, Card cardIn){
    
    int totalPoint = 0;
    int numOfAce = 0;
    Card *ptr = &cardIn;
    ptr = ptr->next;
    while (ptr != NULL) {
        int cardValue = ptr->face + 1;
        
        if(cardValue==1){
            ++numOfAce;
            ptr = ptr->next;
            continue;
        }
        
        if (cardValue>10) {
            cardValue = 10;
        }

        totalPoint+=cardValue;
        if (ptr->next != NULL) {
            ptr=ptr->next;
        }
        else break;
    }
    
    if (totalPoint+numOfAce == 21 || totalPoint+numOfAce > 21) return totalPoint+numOfAce;
    
    else{
        while (numOfAce>0) {
            totalPoint+=11;
            --numOfAce;
            if (totalPoint+numOfAce < 21) continue;
            else if (totalPoint+numOfAce == 21) return totalPoint+numOfAce;
            else return totalPoint+numOfAce;
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
    hand->currentPoint = getNewPoints(hand, newCard);
}

//Check if current hand is splitable
//return 0 if false
//return 1 if true
int splitable(Hand hand){
    if(hand.numOfCard==2){
        int face = hand.card.face;
        if (hand.card.next->face == face) {
            return 1;
        }
    }
    return 0;
}

//Split hand into 2 hands
void split(Player *player){
    player->hand2.card = *player->hand1.card.next;
    player->hand1.card.next = NULL;
}
//Displays a list of a players hand
void displayCurrentHand(Hand *hand) {
    Card *ptr = &hand->card;
    
    printf("Hand\n");
    while (ptr != NULL) {
        ptr = ptr->next;
        if (ptr!=NULL) {
            printf("\t%s %s\n", face[ptr->face], suit[ptr->suite]);
        }
    }
}
//takes money from players bank
void subtractCash(Player player, int bet) {
    player.cash = player.cash - bet;
}
//adds cash to players bank
void addCash(Player player, int bet) {
    player.cash = player.cash + bet;
}
//retrieves players cash
int getPlayerCash(Player player) {
    return player.cash;
}
//check if there is at least one player that is still in the game
int atLeastOnePlayerIn(Player *playerList, int *playerCount) {
    for (size_t i = 1; i < *playerCount; i++) {
        if (playerList[i].quit == 0)
            return 1;
    }
    return 0;
}


