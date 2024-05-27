/** 
This game is made by 

Name - Aakash Shankar Prasad
Roll Number - 2201CS01
Course Number - CS210
Course Name - Architecture Lab
Course Instructor - Dr. Jimson Mathew 
Batch - 2022


All the parts of this project has been made by Aakash Shankar, 2201CS01 , from scratch . 
A few of the algorithms and inspirations taken are as follows: 
1) Bresman's algorithm for drawing : 
              i) a line 
              ii) a thick line
              iii) a circle
Rest all the functions are coded from scratch 
**/

#define SW_BASE               0xFF200040
#define KEY_BASE              0xFF200050
volatile int *KEY_ptr =(volatile int *) KEY_BASE;  
volatile int *SW_ptr  =(volatile int *) SW_BASE;

#include"basicWritingFunctions.c"
#include"Algorithms.c"
#include"rulesPage.c"
#include"scoresPage.c"
#include"welcomePage.c"
#include"squaresAndUpdates.c"
#include"alphabets.c"
#include"numbersAndRounds.c"

// ----------------------------------------------------------------------------------------------------------------------------------------------
// functions for displaying things on different pages 
void makeBoard();
void printRound(int round);   // prints the entire box with ROUND and round number !

// ----------------------------------------------------------------------------------------------------------------------------------------------
// Functions for game play mechanics 

// The following are display mechanics ...
void updateGreenSquare(int currX,int currY,int nextX,int nextY);   // shifting the green square
int makeaTurn();   // make a shift of the square ..... redrawing the square
void makeaShift(int r,int c,int val);  // finalizing the co-ordinates for the green square 
void updateBoard(); // for drawing X and O with the updated matrix 
void movementRulesBox();

int betPage(int player);


// Backend of the game play mechanics  ....
int callPlayer(int player);   // calls the player till it choses the box to write  
void callPlayerTillWrite(int player);     // calls the player till it writes (accomodation for writing on already written boxes )
int winCheck(int val);
int oneRoundTicTacToe(int round);
void waitForKeyPress();
int abs(int x);
void convertToStringAndPrint(int score,int x,int y);
void updateButton(int prev,int next);
int getMode();
void updateScore(int betOne,int betTwo,int winner);


// A few Global variables used ! -------------------------------------------------------------------------------------------------------------
int prevRow=0,prevCol=0;
int buttonX[]={50,123,207}; // buttonY == 110  and length=30
int currButtonX=0;
int scoreA=0;
int scoreB=0;
// Coordinates of the boxes of the TicTacToe Board 
int row[3]={8,68,128};
int col[3]={8,68,128};
  // makeThePointerSquare 
  // box1 == 8,8 | box2 == 68,8 | box3 == 128,8 |  box4 == 8,68 | box5 == 68,68 | box6 == 128,68
  // box7 == 8,128 | box8 == 68,128 | box9 == 128,128 

// Game Matrix 
int gameMatrix[3][3];
// making a Data structure to store the values 
int winnerPlus[]={1,3,5};
int LossMinus[]={1,2,3};
int drawMinus[]={0,-1,-2};

// --------------------------------------------------------------------------------------------------------------------------------------------

// ------------------------------------------------MAIN FUNCTION ---------------------------------------------------------------------------
int main(){
  clear_screen();
  clear_char();

  scoreA=0;
  scoreB=0;

  welcomePage();
  waitForKeyPress();
  rulesPage();
  waitForKeyPress();
  
  for(int i=1;i<=3;i++){
    scoresPage(scoreA,scoreB);
    waitForKeyPress();
    int val1=betPage(1);
    int val2=betPage(2);
    int winner = oneRoundTicTacToe(i);
    updateScore(val1,val2,winner);
    waitForKeyPress();
  }
  scoresPage(scoreA,scoreB);

  return 0;
}
// -------------------------------------------------------------------MAIN FUNCTION OVER--------------------------------------------
 
void updateScore(int betOne,int betTwo,int winner){
    if(winner == 1){
      scoreA+=winnerPlus[betOne];
      scoreB-=LossMinus[betTwo];
    }
    else if (winner == 0){
      scoreA-=LossMinus[betOne];
      scoreB+=winnerPlus[betTwo];
    }
    else{
      scoreA-=drawMinus[betOne];
      scoreB-=drawMinus[betTwo];
    }
}



// waiting for Key Press 
void waitForKeyPress(){
  int val=*KEY_ptr;
  if(val != 0){
    while(val != 0){
      val=*KEY_ptr;
    }
  }

  while(val != 1){
    val=*KEY_ptr;
  }
  return;
}



// -------------------------------------------------------------------------------------------------------------------------------------------
// Function for gameplay Mechanics 

// main game
int oneRoundTicTacToe(int round){
  prevRow=0,prevCol=0;
  makeBoard();
  printRound(round);
  int check=0;
  int i;
  for(i=1;i<=9;i++){
    int par=((i&1) == 1)?1:0;
    callPlayerTillWrite(par);
    check=winCheck(par);
    if(check == 1) return par;
  }

  return -1;
}

// For showing a wrong attempt ! 
void blinkRedSquare(){
  makeRedSquare(col[prevCol],row[prevRow],50);
  updateBoard();
}

// ---------------------------------------------------------------------------------------------------------------------------------------
// Functions for calling players 

// calling a player till it writes 
void callPlayerTillWrite(int player){
  int val=callPlayer(player);
  while(val == 0){
    blinkRedSquare();
    val=callPlayer(player);
  }
}

// calling a player , 1 for X , 2 for O
int callPlayer(int player){
  int val=makeaTurn();
  while(val!=1){
    val=makeaTurn();
  }
  int previousVal=gameMatrix[prevRow][prevCol];
  if(previousVal!=-1) return 0;
  gameMatrix[prevRow][prevCol]=(player == 1)?1:0;
  updateBoard();
  return 1;
}
// ------------------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------------------------------------

// Functions for shifting squares 
// Shifting the green square  
void makeaShift(int r,int c,int val){
  int rFinal=r,cFinal=c;
  if (val !=1 && val!=2) return;
  if(val == 1) cFinal=(c+1)%3; // go right
  if(val == 2) rFinal=(r+1)%3; // go down
  prevRow=rFinal;
  prevCol=cFinal;
  updateGreenSquare(col[c],row[r],col[cFinal],row[rFinal]); 

  return;
}

// Making a turn 
int makeaTurn(){
  int val=*KEY_ptr;
  while(val == 0){
    val=*KEY_ptr;
    if(val == 1){
      int moveDirection = *SW_ptr;
      if(moveDirection == 3) return 1;
      makeaShift(prevRow,prevCol,moveDirection);
      return 0;
    }
  }
  return 0;
}



// Function for button and movements for Bet Page

int getMode(){
  currButtonX=0;
  makeSquare(buttonX[currButtonX],110,30,GREEN);
  waitForKeyPress();
  int chosen=*SW_ptr;
  if(chosen == 1) return currButtonX;
  else {
    while(chosen!=1){
      updateButton(currButtonX,((currButtonX+1)%3));
      currButtonX=(currButtonX+1)%3;
      waitForKeyPress();
      chosen=*SW_ptr;
    }
    return currButtonX;
  }
}

void updateButton(int prev,int next){
  makeSquare(buttonX[prev],110,30,LGRAY);
  makeSquare(buttonX[next],110,30,GREEN);
}


// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// win condition check
int winCheck(int val){
  // all Rows
  for(int myRow=0;myRow<3;myRow++){
    int won=1;
    for(int myCol=0;myCol<3;myCol++){
      if(gameMatrix[myRow][myCol] == val) continue;
      else won=0;
    }

    if(won == 1){
      makeWhiteSquare(col[prevCol],row[prevRow],50);
      for(int myCol=0;myCol<3;myCol++){
        makeGreenSquare(col[myCol],row[myRow],50);
      }
      updateBoard();
      return 1;
    }
  }

  // for all Columns
  for(int myCol=0;myCol<3;myCol++){
    int won=1;
    for(int myRow=0;myRow<3;myRow++){
      if(gameMatrix[myRow][myCol] == val) continue;
      else won=0;
    }
    if(won == 1){
      makeWhiteSquare(col[prevCol],row[prevRow],50);
      for(int myRow=0;myRow<3;myRow++){
        makeGreenSquare(col[myCol],row[myRow],50);
      }
      updateBoard();
      return 1;
    }
  }

  // left top - right bottom diagonal 
  int diagWin=1;
  for(int i=0;i<3;i++){
    if(gameMatrix[i][i] == val) continue;
    else diagWin=0;
  }
  if(diagWin == 1){
    makeWhiteSquare(col[prevCol],row[prevRow],50);
    for(int i=0;i<3;i++){
      makeGreenSquare(col[i],row[i],50);
    }
    updateBoard();
    return 1;
  }


  // right top - left bottom diagonal 
  int diagWinOther=1;
  for(int i=0;i<3;i++){
    if(gameMatrix[i][2-i] == val) continue;
    else diagWinOther=0;
  }
  if(diagWinOther == 1){
    makeWhiteSquare(col[prevCol],row[prevRow],50);
    for(int i=0;i<3;i++){
      makeGreenSquare(col[i],row[2-i],50);
    }
    updateBoard();
    return 1;
  }

  return 0;
}

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Basic functions for the SETUP and fixed processes that aren't a part of the Gameplay Mechanics !

void makeBoard(){
  clear_screen();
  clear_char();
  movementRulesBox();
  // Initialise the matrix 
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      gameMatrix[i][j]=-1;
    }
  }
  // makeTheBoard ! 
  for(int x = 5;x<=185;x++){
    for(int y=5;y<=185;y++){
      write_pixel(x,y,WHITE);
    }
  }
  // The two vertical lines .. 
  draw_line(60,5,60,185);
  draw_line(120,5,120,185);

  // The two horizontal lines ..
  draw_line(5,60,185,60);
  draw_line(5,120,185,120);

  // makeThePointerSquare 
  // box1 == 8,8 | box2 == 68,8 | box3 == 128,8 |  box4 == 8,68 | box5 == 68,68 | box6 == 128,68
  // box7 == 8,128 | box8 == 68,128 | box9 == 128,128 
  makeGreenSquare(8,8,50);
}

void updateBoard(){
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      if(gameMatrix[i][j] == 1) printX(col[j],row[i]);
      if(gameMatrix[i][j] == 0) printO(col[j],row[i]);
    }
  }
}

// Print Round

void printRound(int round){
  for(int y=190;y<240;y++){
    for(int x=0;x<320;x++){
      write_pixel(x,y,LGRAY);
    }
  }
  // print Round
  printRoundForDisplay();
  if(round == 1) printOne();
  else if(round == 2) printTwo();
  else printThree();
}

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------

void movementRulesBox(){
  for(int x=190;x<=310;x++){
    for(int y=5;y<=185;y++){
      write_pixel(x,y,LGRAY);
    }
  }
  print01fn();
  print10fn();
  print11fn();
}

int betPage(int player){
  printBetPage(player);
  int chosenWhichOne=getMode();
  return chosenWhichOne; 
}



int abs(int x){
  if(x>=0) return x;
  x-=(2*x);
  return x;
}



