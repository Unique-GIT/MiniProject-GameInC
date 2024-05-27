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
volatile int * KEY_ptr =(volatile int *) KEY_BASE;  
volatile int * SW_ptr  =(volatile int *) SW_BASE;


//Colours
#define BLACK 0x0000 		
#define GREEN 0x07E0 	
#define RED 0xF800 	 	
#define WHITE 0xFFFF	
#define LGRAY 0xC618 	
#define NAVY 0x000F 

// Basic write functions ! 
void write_pixel(int x,int y,short colour);
void clear_screen();
void write_char(int x,int y,char ch);
void clear_char();

// ------------------------------------------------------------------------------------------------------------------------------------------------------
// Some functions to draw basic shapes ! 
void draw_line(int x1,int y1,int x2,int y2);
void drawThickLine(int x0, int y0, int x1, int y1, int thickness, short color) ;
void makeSquare(int X ,int Y ,int leng ,short colour);
void draw_circle(int centerX,int centerY,int radius);
void makeGreenSquare(int x,int y,int leng);
void makeWhiteSquare(int x,int y,int leng);
void makeRedSquare(int x,int y,int leng);
void blinkRedSquare(); 

// ----------------------------------------------------------------------------------------------------------------------------------------------
// functions for displaying things on different pages 
void makeBoard();
void printRoundForDisplay();   // prints only ROUND
void printRound(int round);   // prints the entire box with ROUND and round number !
// letters of Round and number ! 
void printR();
void printRoundO();
void printU();
void printN();
void printD();
void printOne();
void printTwo();
void printThree();

// ----------------------------------------------------------------------------------------------------------------------------------------------
// Functions for game play mechanics 

// The following are display mechanics ...
void updateGreenSquare(int currX,int currY,int nextX,int nextY);   // shifting the green square
int makeaTurn();   // make a shift of the square ..... redrawing the square
void makeaShift(int r,int c,int val);  // finalizing the co-ordinates for the green square 
void printX(int x,int y); // x=col , y=row  --> for printing X
void printO(int x,int y); // x=col , y=row  --> for printing Y
void updateBoard(); // for drawing X and O with the updated matrix 
void welcomePage();
void rulesPage();
void scoresPage(int scoreOne,int scoreTwo);
void movementRulesBox();
void print01fn();
void print10fn();
void print11fn();
void printMode(int player);
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

//---------------------------------------------------------------------------------------------------------------------------------------------
// function for printing scores

void convertToStringAndPrint(int score,int x,int y){
  char sign;
  if(score>=0) sign='+';
  else sign='-';

  score=abs(score);
  char ones,tens;
  ones=(char)('0'+(score%10));
  score=score/10;
  tens=(char)('0'+(score%10));
  

  char ans[]={sign,tens,ones,'\0'};

  int startX=x;
  int startY=y;

  char * ptr=ans;
  while(*ptr != '\0'){
    write_char(startX,startY,*ptr);
    ptr++;
    startX++;
  }
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

// Updating the shifting of the green square !
void updateGreenSquare(int currX,int currY,int nextX,int nextY){
  makeWhiteSquare(currX,currY,50);
  makeGreenSquare(nextX,nextY,50);
  updateBoard();
}

// For showing a wrong attempt ! 
void blinkRedSquare(){
  makeRedSquare(col[prevCol],row[prevRow],50);
  updateBoard();
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


// Static codes for white and green squares 
void makeSquare(int X ,int Y ,int leng ,short colour){
  for(int x=X;x<X+leng;x++){
    for(int y=Y;y<Y+leng;y++){
      write_pixel(x,y,colour);
    }
  }
}
void makeGreenSquare(int X,int Y,int leng){
  makeSquare(X,Y,50,GREEN);
}

void makeWhiteSquare(int X,int Y,int leng){
  makeSquare(X,Y,50,WHITE);
}

void makeRedSquare(int X,int Y,int leng){
  makeSquare(X,Y,50,RED);
}

// Printing X and O 

void printX(int x,int y){
  int yStart1=y;
  int yStart2=y+50;
  for(int i=x;i<x+50;i++){
      write_pixel(i,yStart1,NAVY);
      write_pixel(i,yStart2,NAVY);
      yStart1++;
      yStart2--;
  }
  return;
}

void printO(int x,int y){
  draw_circle(x+25,y+25,25);
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


// ----------------------------------------------------------------------------------------------------------------------


// Basic Codes for writing stuff on VGA 
// Plus addition code for drawing Line and drawing a Circle 



/* set a single pixel on the screen at x,y
 * x in [0,319], y in [0,239], and colour in [0,65535]
 */
void write_pixel(int x, int y, short colour) {
  volatile short *vga_addr=(volatile short*)(0x08000000 + (y<<10) + (x<<1));
  *vga_addr=colour;
}

/* use write_pixel to set entire screen to black (does not clear the character buffer) */
void clear_screen() {
  int x, y;
  for (x = 0; x < 320; x++) {
    for (y = 0; y < 240; y++) {
	  write_pixel(x,y,BLACK);
	  }
  }
}

/* write a single character to the character buffer at x,y
 * x in [0,79], y in [0,59]
 */
void write_char(int x, int y, char c) {
  // VGA character buffer
  volatile char * character_buffer = (char *) (0x09000000 + (y<<7) + x);
  *character_buffer = c;
}

void clear_char(){
  char ch='\0';
  for(int x=0;x<80;x++){
    for(int y=0;y<60;y++){
      write_char(x,y,ch);
    }
  }
}


void draw_line(int x1, int y1, int x2, int y2) {
    int dx = abs((x2 - x1));
    int dy = abs((y2 - y1));
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (x1 != x2 || y1 != y2) {
        write_pixel(x1, y1,NAVY);
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}


void draw_circle(int centerX, int centerY, int radius) {
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y) {
        write_pixel(centerX + x, centerY + y, NAVY);
        write_pixel(centerX + y, centerY + x, NAVY);
        write_pixel(centerX - y, centerY + x, NAVY);
        write_pixel(centerX - x, centerY + y, NAVY);
        write_pixel(centerX - x, centerY - y, NAVY);
        write_pixel(centerX - y, centerY - x, NAVY);
        write_pixel(centerX + y, centerY - x, NAVY);
        write_pixel(centerX + x, centerY - y, NAVY);

        if (err <= 0) {
            y += 1;
            err += 2*y + 1;
        }
        if (err > 0) {
            x -= 1;
            err -= 2*x + 1;
        }
    }
    return;
}

// Function to draw a thick line using Bresenham's algorithm
// Function to draw a thick line using Bresenham's algorithm
void drawThickLine(int x0, int y0, int x1, int y1, int thickness, short color) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    if (dx > dy) {
        for (int i = -thickness / 2; i < thickness / 2; i++) {
            draw_line(x0, y0 + i, x1, y1 + i);
        }
    } else {
        for (int i = -thickness / 2; i < thickness / 2; i++) {
            draw_line(x0 + i, y0, x1 + i, y1);
        }
    }
}

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------

// A bunch of functions to print letters !

// print Round 
void printRoundForDisplay(){
  printR();
  printRoundO();
  printU();
  printN();
  printD();
}
// Print R
void printR(){
  drawThickLine(20,200,20,230,5,NAVY);
  drawThickLine(20,200,35,200,5,NAVY);
  drawThickLine(20,215,35,215,5,NAVY);
  drawThickLine(20,215,40,230,5,NAVY);
  drawThickLine(35,200,35,215,5,NAVY);
}

void printRoundO(){
  drawThickLine(50,200,50,230,5,NAVY);  // |
  drawThickLine(50,200,65,200,5,NAVY);  // -
  drawThickLine(65,200,65,230,5,NAVY);  // |  
  drawThickLine(50,230,65,230,5,NAVY);  // _
}

void printU(){
  drawThickLine(80,200,80,230,5,NAVY);
  drawThickLine(80,230,95,230,5,NAVY);
  drawThickLine(95,200,95,230,5,NAVY);
}

void printN(){
  drawThickLine(105,200,105,230,5,NAVY);
  drawThickLine(105,200,125,230,5,NAVY);
  drawThickLine(125,200,125,230,5,NAVY);
}

void printD(){
  drawThickLine(140,200,140,230,5,NAVY);  // |
  drawThickLine(140,200,160,210,5,NAVY);  // -
  drawThickLine(160,210,160,220,5,NAVY);  // |  
  drawThickLine(140,230,160,220,5,NAVY);  // _
}

void printOne(){
  drawThickLine(195,200,195,230,5,NAVY);
}
void printTwo(){
  drawThickLine(195,200,195,230,5,NAVY);
  drawThickLine(205,200,205,230,5,NAVY);
}
void printThree(){
  drawThickLine(195,200,195,230,5,NAVY);
  drawThickLine(205,200,205,230,5,NAVY);
  drawThickLine(215,200,215,230,5,NAVY);
}


void printRoll(){
  // print 2 
  drawThickLine(20,200,35,200,5,NAVY);
  drawThickLine(35,200,35,215,5,NAVY);
  drawThickLine(20,215,35,215,5,NAVY);
  drawThickLine(20,215,20,230,5,NAVY);
  drawThickLine(20,230,35,230,5,NAVY);


  // print 2 
  drawThickLine(45,200,60,200,5,NAVY);
  drawThickLine(60,200,60,215,5,NAVY);
  drawThickLine(45,215,60,215,5,NAVY);
  drawThickLine(45,215,45,230,5,NAVY);
  drawThickLine(45,230,60,230,5,NAVY);

  // print 0
  drawThickLine(70,200,70,230,5,NAVY);
  drawThickLine(70,200,85,200,5,NAVY);
  drawThickLine(70,230,85,230,5,NAVY);
  drawThickLine(85,200,85,230,5,NAVY);

  // print !
  drawThickLine(100,200,100,230,5,NAVY);

  // print C
  drawThickLine(115,200,130,200,5,NAVY);
  drawThickLine(115,200,115,230,5,NAVY);
  drawThickLine(115,230,130,230,5,NAVY);

  // print S
  drawThickLine(145,200,160,200,5,NAVY);
  drawThickLine(145,200,145,215,5,NAVY);
  drawThickLine(145,215,160,215,5,NAVY);
  drawThickLine(160,215,160,230,5,NAVY);
  drawThickLine(145,230,160,230,5,NAVY);

  // print 0
  drawThickLine(185,200,185,230,5,NAVY);
  drawThickLine(185,200,200,200,5,NAVY);
  drawThickLine(185,230,200,230,5,NAVY);
  drawThickLine(200,200,200,230,5,NAVY);

  // print 1
  drawThickLine(210,200,210,230,5,NAVY);
}


// -----------------------------------------------------------------------------------------------------
// Some ASCII art codes for display pages ! 

void scoresPage(int scoreOne,int scoreTwo){
  clear_screen();
  clear_char();
  for(int x=20;x<300;x++){
    for(int y=20;y<220;y++){
      write_pixel(x,y,LGRAY);
    }
  }

  for(int x=125;x<=185;x++){
    for(int y=100;y<=140;y++){
      write_pixel(x,y,BLACK);
    }
  }

    // print 1
  drawThickLine(50,80,50,160,5,NAVY);

    // print ->
  drawThickLine(60,120,110,120,5,NAVY);
  drawThickLine(85,110,110,120,5,NAVY);
  drawThickLine(85,130,110,120,5,NAVY);

    // print 2
  drawThickLine(250,80,250,160,5,NAVY);
  drawThickLine(265,80,265,160,5,NAVY);

    // print <-
  drawThickLine(200,120,240,120,5,NAVY);
  drawThickLine(220,110,200,120,5,NAVY);
  drawThickLine(220,130,200,120,5,NAVY);
  

  char *ch="SCORES";
  int x=36;
  while(*ch!='\0'){
    write_char(x,28,*ch);
    ch++;
    x++;
  }

  convertToStringAndPrint(scoreOne,32,30);
  convertToStringAndPrint(scoreTwo,42,30);
}


void welcomePage(){
  clear_char();
  clear_screen();

  for(int x=0;x<320;x++){
    for(int y=0;y<30;y++){
      write_pixel(x,y,LGRAY);
    }
  }

    char * ch="\0";
    char *welcome_art[] = {
".::    .   .:::.,::::::   :::       .,-:::::      ...      .        :    .,::::::\n",  
"';;,  ;;  ;;;' ;;;;''''   ;;;     ,;;;'````'   .;;;;;;;.   ;;,.    ;;;   ;;'''' \n", 
" '[[, [[, [['   [[cccc    [[[     [[[         ,[[     [[[, [[[[, ,[[[[   [[cccc   \n",
"   Y$c$$$c$P    $$$$$$    $$$     $$$         $$,     $$$  $$$$   $$$$   $$  \n ",
"     88888      8.....    o88oo,. `88bo,__,o  88,_ _,88P8  Y88    888    88oo___ \n",
"      MM        YUMMMM     YUMMM    YUMMMMMP     YMMMMMP   MMM    MMMM   YUMMM\n",
"                                        ",
"                                         ",
" ::::::::::::   ...     ",
" ;;;;;;;;''''.;;;;;;;.  ",
"     [[    ,[[      [[,",
"     $$    $$$,     $$$",
"     88,   888,_ _,88P",
"     MMM     YMMMMMP ",
"                                        ",
"                                         ",
"  #########   ###########  ######       #########     #       ###            ",
"     ##           ##       ##              ##       #  #     #           ",
"     ##           ##       ##              ##      ######   #              ",
"     ##           ##       ##              ##     #      #   #          ",
"     ##       ###########  ######          ##    #        #   ###         ",
"                                        ",
"                                         ",
"    #######    # # #    #######   ",
"      ##     #     #   ##          ",
"      ##     #     #   #####       ",
"      ##     #     #   ##          ",
"      ##       ###     #######     ",
"                                        ",
"                                         ",
" ###      ##    #      #   #     ######   #######  #####  #####",
" #  #   #    #  #      #   #     #          ##       #    #",
" ###    #    #  #      #   #     ###        ##       #    ###",
" ##     #    #   #    #    #     #          ##       #    #",
" #  #     ##       ##      ####  ######     ##       #    #####",
"\0" // NULL terminator to indicate end of array
    };

    int x,y;
    y=10;
    char **ptr = welcome_art;
    while (*ptr != ch) {
        x=0;
        char *line = *ptr;
        while (*line != '\0') {
            write_char(x,y,*line);
            // printf("%c",*line);
            line++;
            x++;
        }
        y++;
        ptr++;
    }

  for(int y=190;y<240;y++){
    for(int x=0;x<320;x++){
      write_pixel(x,y,LGRAY);
    }
  }
  printRoll();
  return;
}

void rulesPage(){
  clear_screen();
  clear_char();
  for(int i=0;i<320;i++){
    for(int j=0;j<240;j++){
      write_pixel(i,j,LGRAY);
    }
  }

  drawThickLine(5,5,310,5,5,NAVY);
  drawThickLine(5,230,310,230,5,NAVY);
  drawThickLine(5,5,5,230,5,NAVY);
  drawThickLine(310,5,310,230,5,NAVY);
  // print RULES 
  
  // print R
  drawThickLine(40,25,40,75,5,NAVY);
  drawThickLine(40,25,55,25,5,NAVY);
  drawThickLine(40,50,55,50,5,NAVY);
  drawThickLine(40,50,60,75,5,NAVY);
  drawThickLine(55,25,55,50,5,NAVY);

  // print U
  drawThickLine(70,25,70,75,5,NAVY);
  drawThickLine(70,75,95,75,5,NAVY);
  drawThickLine(95,25,95,75,5,NAVY);

  // print L 
  drawThickLine(110,25,110,75,5,NAVY);
  drawThickLine(110,75,135,75,5,NAVY);

  // print E
  drawThickLine(150,25,150,75,5,NAVY);  // |
  drawThickLine(150,25,175,25,5,NAVY);  // upper -
  drawThickLine(150,50,165,50,5,NAVY);  // middle -
  drawThickLine(150,75,175,75,5,NAVY);

  // print S
  drawThickLine(190,25,215,25,5,NAVY);   // upper -
  drawThickLine(190,25,190,50,5,NAVY);   // |
  drawThickLine(190,50,215,50,5,NAVY);   // middle -
  drawThickLine(215,50,215,75,5,NAVY);   // right | 
  drawThickLine(190,75,215,75,5,NAVY);   // down _ 

  // printing the rules 
  char *rules[]={
    "1. Two Players have to play three rounds of Tic Tac Toe",
    "",
    "2. The player with the maximum score wins !",
    "",
    "3. But .........",
    "",
    "4. The players can get higher points by bets",
    "",
    "5. And even higher points for Blind ",
    "",
    "",
    "----------------------------------------",
    "Way --> | Normal | Bet | Blind |",
    "        |        |     |       |",
    "Win     |  +1    |  +3 |  +5   |",
    "        |        |     |       |",
    "Loss    |  -1    |  -2 |  -3   |",
    "        |        |     |       |",
    "Draw    |   0    |  -1 |  -2   | ",
    "                                  ",
    "More Risk More Reward",
    "\0"
  };

  char * ch="\0";
      int x,y;
    y=30;
    char **ptr = rules;
    while (*ptr != ch) {
        x=10;
        char *line = *ptr;
        while (*line != '\0') {
            write_char(x,y,*line);
            // printf("%c",*line);
            line++;
            x++;
        }
        y++;
        ptr++;
    }
}



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

void print01fn(){
  // print 0
  drawThickLine(200,7,222,7,5,NAVY);  // upper -
  drawThickLine(200,7,200,37,5,NAVY);   
  drawThickLine(200,37,222,37,5,NAVY);
  drawThickLine(222,7,222,37,5,NAVY);

  // print 1
  drawThickLine(230,7,230,37,5,NAVY);


  // print ->
  drawThickLine(245,20,290,20,5,NAVY);
  drawThickLine(270,7,290,20,5,NAVY);
  drawThickLine(270,37,290,20,5,NAVY);
}


void print10fn(){

  // print 1
  drawThickLine(200,45,200,75,5,NAVY);

  // print 0
  drawThickLine(215,45,230,45,5,NAVY);  // upper -
  drawThickLine(215,45,215,75,5,NAVY);   
  drawThickLine(215,75,230,75,5,NAVY);
  drawThickLine(230,45,230,75,5,NAVY);

 // print |
  //       \/
  drawThickLine(260,45,260,75,5,NAVY);
  drawThickLine(240,60,260,75,5,NAVY);
  drawThickLine(280,60,260,75,5,NAVY);
}

void print11fn(){
      // print 1
  drawThickLine(200,90,200,130,5,NAVY);
    // print 1
  drawThickLine(220,90,220,130,5,NAVY);

  // print tick 
  drawThickLine(240,110,260,130,5,NAVY);
  drawThickLine(260,130,300,90,5,NAVY);
}

int betPage(int player){
  clear_screen();
  clear_char();

  for(int x=40;x<=240;x++){
    for(int y=15;y<=90;y++){
      write_pixel(x,y,LGRAY);
    }
  }

  printMode(player);


  char *bet="BET";
  char *normal="NORMAL";
  char *blind="BLIND"; 
  char *inst="Keep switch == 1 when selecting , else 0"; 
  char *inst2="Push button to move the cursor";

  int y=30;
  int x=13;
  
  char *ptr=normal;
  while(*ptr !='\0'){
    write_char(x,y,*ptr);
    ptr++;
    x++;
  }

  x=33;
  ptr=bet;
  while(*ptr !='\0'){
    write_char(x,y,*ptr);
    ptr++;
    x++;
  }

  x=53;
  ptr=blind;
  while(*ptr!='\0'){
    write_char(x,y,*ptr);
    ptr++;
    x++;
  }

  x=15;
  ptr=inst2;
  while(*ptr!='\0'){
    write_char(x,40,*ptr);
    ptr++;
    x++;
  }

  x=15;
  ptr=inst;
  while(*ptr!='\0'){
    write_char(x,45,*ptr);
    ptr++;
    x++;
  }



  makeSquare(50,110,30,LGRAY);
  makeSquare(123,110,30,LGRAY);
  makeSquare(207,110,30,LGRAY);

  int chosenWhichOne=getMode();
  return chosenWhichOne;
  
}

int abs(int x){
  if(x>=0) return x;
  x-=(2*x);
  return x;
}


void printMode(int player){
  // print MODE

  // print M
  drawThickLine(45,20,45,80,4,NAVY);  // |   
  drawThickLine(45,20,53,50,4,NAVY);
  drawThickLine(53,50,61,20,4,NAVY);
  drawThickLine(61,20,61,80,4,NAVY);

  // print O 
  drawThickLine(75,20,90,20,4,NAVY);
  drawThickLine(75,20,75,80,4,NAVY);
  drawThickLine(75,80,90,80,4,NAVY);
  drawThickLine(90,80,90,20,4,NAVY);

  //print D
  drawThickLine(105,20,120,50,4,NAVY);
  drawThickLine(105,20,105,80,4,NAVY);
  drawThickLine(105,80,120,50,4,NAVY);

  // print E
  drawThickLine(135,20,135,80,4,NAVY);
  drawThickLine(135,20,160,20,4,NAVY);
  drawThickLine(135,50,150,50,4,NAVY);
  drawThickLine(135,80,160,80,4,NAVY);

  // player number ! 

  if(player == 1){
    drawThickLine(180,20,180,80,4,NAVY);
  }
  else{
    drawThickLine(180,20,180,80,4,NAVY);
    drawThickLine(189,20,189,80,4,NAVY);
  }
}
