//
//  main.c
//  ProjectAttempt1
//
//  Created by Mehmet Soner Korucu on 1.01.2022.
//

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
//calling functions that are used before defined in detail.
void gamePlay(void);
void theMenu(void);
//defining every significant variable in a structure. Game depends on these 6 variables.
struct gamestate
{
 int planePos; // plane position in x-axis
 int bombPos; // bomb position in x-axis
 int distance; // distance between bomb and plane
 int index; // word index in word array
 int letter; // letter index in word array
 int score; // score
};
//defined all variables as 0 in default.
struct gamestate save = {0,0,0,0,0,0};
//loadGame func
void loadGame(void)
{
    //used some code found use input as file name.
    char userName[20];
    char fileName[25];
    printf("Please write a file name to load game: ");
    scanf("%s",userName);
    //these 2 lines below are to beautify the game. there will be more lines like that.
    printf("Searching for file..\n");
    sleep(1);
    //this line is the code i mentioned above.
    sprintf(fileName,"%s.txt",userName);
    FILE *savePtr = fopen(fileName,"r");
    //if files does not exist, it will go back to menu.
    if(savePtr == NULL)
    {
        printf("No such file.\nReturning to menu...");
        sleep(1);
        system("cls");
        theMenu();
    }
    else
    {
        // decorating code and then saving variables on text file
        printf("File founded.\nLoading game...");
        sleep(1);
        fscanf(savePtr,"%d%d%d%d%d%d",&save.planePos,&save.bombPos,&save.distance,&save.index,&save.letter,&save.score);
        fclose(savePtr);
    }
    gamePlay();
}
//save function.
void saveGame(void)
{
    //just a warning here..
    if(save.planePos== 0 && save.bombPos== 0 && save.distance==0 && save.index== 0 && save.letter==0 && save.score==0)
    {
        system("cls");
        printf("You really wanna save the default game??\nI'm sending you back to the menu...");
        sleep(1);
        system("cls");
        theMenu();
    }
    //same code used here to save the game.
    char userName[20];
    char fileName[25];
    printf("Please write a file name to save game: ");
    scanf("%s",userName);
    sprintf(fileName,"%s.txt",userName);
    FILE *savePtr = fopen(fileName,"w");
    if(savePtr == NULL) printf("no save founded.\n");
    else
    {
        fprintf(savePtr,"%d\n%d\n%d\n%d\n%d\n%d\n",save.planePos,save.bombPos,save.distance,save.index,save.letter,save.score);
        fclose(savePtr);
    }
    //decorating code
    printf("Game is being saved...\n");
    sleep(1);
    printf("Game saved successfully!\n");
    sleep(1);
    system("cls");
    theMenu();
}
//this is the code where game is loaded.
void gamePlay(void)
{
    //calling the words text file
    FILE *wordsPtr = fopen("codewords.txt","r");
    // warning for returning null
    if(wordsPtr == NULL)
    {
        printf("words file can't be found. please add the words file and try again.\n");
        sleep(1);
        theMenu();
    }
    //defining words array. first dimension for words & second dimension for letters
    char words[49][11];
    //loops for placing words into array
    for(int e = 0;e<35;e++)
    {
        char temporaryArray[11];
        fscanf(wordsPtr,"%s",temporaryArray);
        for(int q = 0; q<11;q++)
        {
            words[e][q] = temporaryArray[q];
        }
        //printf("%s\n",words[e]);
        //usleep(100000);
    }
    fclose(wordsPtr);
    system("cls");
    //distance between plane and city is 15 lines. reverseDistance is lines between plane and bomb.
    int reverseDistance = 15 - save.distance;
    while(1)
        {
            //variable below is for increasing game speed. i chose to speed up game in every 3 words.
            int sleepTime = 150000-(save.index/3)*5000;
            while (_kbhit())
            {
                char c = _getch();
                // ASCII code of esc character is 27.
                if (c == 27)
                {
                    system("cls");
                    theMenu();
                }
                //if input is equal to the character next to bomb
                else if(c==words[save.index][save.letter])
                {
                    //increasing score.
                    save.score++;
                    //if word is completed...
                    if(words[save.index][save.letter+1]== '\0')
                    {
                        //skipping next word.
                        save.index++;
                        save.letter=0;
                        //reset bomb distance
                        save.distance=0;
                        reverseDistance = 15 - save.distance;
                        //setting bomb's new position according to plane
                        if ((save.planePos/16)%2 == 0) save.bombPos = save.planePos;
                        if ((save.planePos/16)%2 == 1) save.bombPos = 32-save.planePos;
                    }
                    // if word is not completed, it moves  letter index
                    else save.letter++;
                }
                //decreasing score while preventing negative score
                else if(save.score >0) save.score--;
            }
            system("cls");
            //printing plane and score
            if((save.planePos/32)%2 == 1) save.planePos =0;
            if((save.planePos/16)%2 == 0)
            {
                for(int d = save.planePos; d>0;d--) printf("  ");
                printf("(|__.-. |");
                for(int d = save.planePos; d<22;d++) printf("  ");
                printf("SCORE: %d\n",save.score);
                for(int d = save.planePos; d>0;d--) printf("  ");
                printf("== ===_]+\n");
                for(int d = save.planePos; d>0;d--) printf("  ");
                printf("        |\n");
            }
            if((save.planePos/16)%2 == 1)
            {
                for(int d = save.planePos; d<32;d++) printf("  ");
                printf("(|__.-. |");
                for(int d = save.planePos; d>10;d--) printf("  ");
                printf("SCORE: %d\n",save.score);
                for(int d = save.planePos; d<32;d++) printf("  ");
                printf("== ===_]+\n");
                for(int d = save.planePos; d<32;d++) printf("  ");
                printf("        |\n");
            }
            //printing reverseDistance which between plane and bomb
            for(int j = reverseDistance; j<=15;j++) printf("\n");
            for(int d = save.bombPos; d>0;d--) printf("  ");
            printf("<|>\n");
            for(int d = save.bombPos; d>0;d--) printf("  ");
            printf(" |");
            //printing words
            for(int i= save.letter; i<11;i++) printf("%c",words[save.index][i]);
            printf("\n");
            //printing distance between bomb and city.
            for(int d = save.bombPos; d>0;d--) printf("  ");
            printf(" *\n");
            for (int i = save.distance; i<=15 ; i++) printf("\n");
            if(save.distance >=15) break;
            printf(" _____        _____    _________________ ________    _________\n");
            printf("|o o o|_______|    |__|               | | # # # |____|o o o o|\n");
            printf("|o o o|* * *|: ::|. . |               |o| # # # |. . |o o o o|\n");
            printf("|o o o|* * *|::  |. . | []  []  []  []|o| # # # |. . |o o o o|\n");
            printf("|o o o|**** |:  :| . .| []  []  []    |o| # # # |. . |o o o o|\n");
            printf("|_[]__|__[]_|_||_|__< |____________;;_|_|___[]__|_.|_|__[]___|");
            usleep(sleepTime);
            save.planePos++;
            //increasing distance
            save.distance ++;
            reverseDistance--;
            if(save.index == 35) break;
        }
    //if while broke, it will clear screen and return to menu
    system("cls");
    if(save.index >= 35) printf("YOU WIN!<3\n");
    else if (save.distance >= 15) printf("YOU LOSE!\n");
    sleep(1);
    theMenu();
}
void returnGame(void)
{
    //if game variables are 0, it will warn player and start a new game
    if(save.planePos== 0 && save.bombPos== 0 && save.distance==0 && save.index== 0 && save.letter==0 && save.score==0)
    {
        system("cls");
        printf("Nothing to return.\nStarting new game..");
        sleep(1);
        system("cls");
    }
    //returnGame won't update variables like newgame. it will use unchanged variables. Basicly will return game.
    gamePlay();
}
void newGame(void)
{
    save.bombPos = 0; save.planePos = 0; save.bombPos = 0; save.distance = 0; save.index = 0; save.letter = 0; save.score = 0;
    gamePlay();
}
// A standard menu function. Nothing to explain here
void theMenu(void)
{
    //char below is for no use except preventing bugs.
    char str[12];
    int menuInput = 0;
    printf("1. New game\n2. Load a Saved Game\n3. Save Current Game\n4. Return to Game\n5. Exit\n");
    scanf("%d",&menuInput);
    switch(menuInput)
    {
        case 1: printf("map is being created...\n");sleep(1);newGame(); break;
        case 2: loadGame(); break;
        case 3: saveGame();break;
        case 4: returnGame(); break;
        case 5: exit(0);
        default: scanf("%s",str);system("cls");theMenu();
    }
}
int main()
{
    theMenu();
    system("cls");
    return 0;
}
/*
 All sleep codes are to beautify the code itself since it is a game.
 */
