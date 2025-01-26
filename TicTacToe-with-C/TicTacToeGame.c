#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clearScreen() {
#ifdef _WIN32
    system("CLS");  
#else
    system("clear");  
#endif
}

void check(char);
int n = 0;
char a[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

char player1[50], player2[50];  
char symbol1, symbol2;  

void gn() {
    printf("\t\t\t TIC TAC TOE \n");
}

void syem() {
    printf("\n\n\t\t\t|---|---|---|\n");
    printf("\t\t\t| %c | %c | %c |\n", a[0], a[1], a[2]);
    printf("\t\t\t|---|---|---|\n");
    printf("\t\t\t| %c | %c | %c |\n", a[3], a[4], a[5]);
    printf("\t\t\t|---|---|---|\n");
    printf("\t\t\t| %c | %c | %c |\n", a[6], a[7], a[8]);
    printf("\t\t\t|---|---|---|\n");
}

void sym() {
    printf("\n%s, choose your symbol (X or O): ", player1);
    scanf(" %c", &symbol1);
    if (symbol1 == 'X' || symbol1 == 'x') {
        symbol2 = 'O';  
    } else {
        symbol2 = 'X';  
    }
    printf("%s, your symbol is: %c\n", player1, symbol1);
    printf("%s, your symbol is: %c\n", player2, symbol2);
}

int count = 0;

void play() {
    char po;
    int validMove = 0;
    while (!validMove) {
        printf("\nEnter Position (1-9): ");
        fflush(stdin);
        scanf("%c", &po);
        validMove = (po >= '1' && po <= '9'); 
        if (!validMove) {
            printf("\nPlease enter a position between 1 and 9.\n");
        }
    }
    count++;
    check(po);
}

void check(char P) {
    int pos = P - '1'; 
    if (pos >= 0 && pos < 9 && a[pos] != 'x' && a[pos] != '0') { 
        if (n == 0) {
            a[pos] = symbol1; 
            n = 1;
        } else {
            a[pos] = symbol2; 
            n = 0;
        }
    } else {
        printf("\nInvalid move. Please choose an empty position from 1 to 9.\n");
    }
}

int end() {
    
    int win_combinations[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, 
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, 
        {0, 4, 8}, {2, 4, 6} 
    };

    for (int i = 0; i < 8; i++) {
       
        if (a[win_combinations[i][0]] == a[win_combinations[i][1]] && a[win_combinations[i][1]] == a[win_combinations[i][2]]) {
            if (a[win_combinations[i][0]] == symbol1) {
                return 100; 
            } else if (a[win_combinations[i][0]] == symbol2) {
                return 200; 
            }
        }
    }

    return 300; 
}

void main() {
    char ch;
    
    printf("Player 1, enter your name: ");
    scanf("%s", player1);
    printf("Player 2, enter your name: ");
    scanf("%s", player2);

    do {
        clearScreen();
        gn();
        syem();
        sym();  
        play();
        int k;
        do {
            clearScreen();
            syem();
            play();
            k = end();
            clearScreen();
            syem();
        } while (k == 300 && count < 9); 

        if (k == 100) {
            printf("\n%s WON The Match\n", player1);
        } else if (k == 200) {
            printf("\n%s WON The Match \n", player2);
        } else {
            printf("\nGame Draw\n");
        }

        
        while (getchar() != '\n'); 

        printf("Do you want to play again? (y/n): ");
        scanf("%c", &ch);

        if (ch == 'y' || ch == 'Y') {
            
            a[0] = '1'; a[1] = '2'; a[2] = '3'; a[3] = '4'; a[4] = '5'; a[5] = '6'; a[6] = '7'; a[7] = '8'; a[8] = '9';
            n = 0;
            count = 0;
        }
    } while (ch == 'y' || ch == 'Y');

    exit(0); 
}
