#include <stdio.h>
#include<string.h>
#include<Stdlib.h>

char draw(int i) 
{
    switch(i) {
        case -1:
            return 'X';
        case 0:
            return ' ';
        case 1:
            return 'O';
    }
}

void array(int b[9]) 
{
    printf(" %c | %c | %c\n",draw(b[0]),draw(b[1]),draw(b[2]));
    printf("-----------\n");
    printf(" %c | %c | %c\n",draw(b[3]),draw(b[4]),draw(b[5]));
    printf("---+---+---\n");
    printf(" %c | %c | %c\n",draw(b[6]),draw(b[7]),draw(b[8]));
}

int winning(int structure[9])
 {
    //determines if a competative has won, returns 0 otherwise.
    int wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    int i;
    for(i = 0; i < 8; ++i)
	 {
        if(structure[wins[i][0]] != 0 &&
           structure[wins[i][0]] == structure[wins[i][1]] &&
           structure[wins[i][0]] == structure[wins[i][2]])
            return structure[wins[i][2]]; // if there is an x on i ,then it will return :-1 and if there is ' O' it will return 1:
    }
    return 0;
}

int ai(int structure[9], int competative) 
{
    //How is the position like for competative (their turn) on structure?
    int winner = winning(structure);
    if(winner != 0) return winner*competative;

   int  move = 0;
    int runs = -2;
    int i;
    for(i = 0; i < 9; ++i) {
        if(structure[i] == 0) {// it will check from starting that if the place is empty then will put it over there 
            structure[i] = competative;//Try the move
            int points = -ai(structure, competative*-1);
            if(points > runs) {
                runs = points;
                move = i; // if move successfull then we will take it as i .
            }
            structure[i] = 0;//reset the structure after trying
        }
    }
    if(move == 0) return 0;
    return runs;
}

void botmove(int structure[9])
 {
    int move = 0;
    int runs = -2;
    int i;
    for(i = 0; i < 9; ++i) {
        if(structure[i] == 0)
		 {
            structure[i] = 1; // 1 MEANS ' O ' WHICH IS THE SYMBOL OF COMPUTER MEANS IF THE PLACE IN EMPTY.. PLACE AN O OVER THERE
            int botpoint = -ai(structure, -1);
            structure[i] = 0; 
            if(botpoint > runs) {
                runs = botpoint;
                move = i;
            }
        }
    }
    
    structure[move] = 1; // means that move is assigned to bot in the structure of tic tac toe
}

void mymove(int structure[9]) {
    int move = 0;
   for (move =0 ; move <= 9  && structure[move] == 0; move++);
        printf("\nInput move ([0..8]): ");
        scanf("%d", &move);
        printf("\n");
    
    structure[move] = -1; // any move he writes btw 0 and 8 that move will be taken as -1 (X) ON STRUCTURE
}

int main() {
    int structure[9] = {0,0,0,0,0,0,0,0,0};
    //computer squares are 1, competative squares are -1.
  printf("Computer: O, You: X\nPlay (1)st or (2)nd? ");
    //int competative=0;
  //  scanf("%d",&competative);
    printf("\n");
    int  turn;
    for(turn = 0; turn < 5 &&  winning(structure) == 0; ++turn) // either it will ask 5 times or unless someone wins
	 {
     if (winning(structure)) // every time it will check if some one has won..
     {
     break ;	
	 }
	
      array(structure);
            mymove(structure);// if you want bot move as 1st .. replace line 120 and 121
            botmove(structure);
       
           
       
    }
    switch(winning(structure))
	 {
        case 0:
            printf("ITS A DRAW ");
            break;
        case 1:
            array(structure);
            printf("Ahhhhh You Lose");
            break;
        case -1:
            printf("YOU WIN CONGRATSSS !!!");
            break;
    }
}