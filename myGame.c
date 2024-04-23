/** 
This game is made by 

Name - Aakash Shankar Prasad
Roll Number - 2201CS01
Course Number - CS210
Course Name - Architecture Lab
Course Instructor - Dr. Jimson Mathew 


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


// Coordinates of the boxes of the TicTacToe Board 
int row[3]={8,68,128};
int col[3]={8,68,128};
  // makeThePointerSquare 
  // box1 == 8,8 | box2 == 68,8 | box3 == 128,8 |  box4 == 8,68 | box5 == 68,68 | box6 == 128,68
  // box7 == 8,128 | box8 == 68,128 | box9 == 128,128 

// Game Matrix 
int gameMatrix[3][3];
// making a Data structure to store the values 

void write_pixel(int x,int y,short colour);
void clear_screen();
void write_char(int x,int y,char ch);
void clear_char();
void makeBoard();
void printRound();
void draw_line(int x1,int y1,int x2,int y2);
void drawThickLine(int x0, int y0, int x1, int y1, int thickness, short color) ;
void makeSquare(int X ,int Y ,int leng ,short colour);
void draw_circle(int centerX,int centerY,int radius);
void makeGreenSquare(int x,int y,int leng);
void makeWhiteSquare(int x,int y,int leng);
void makeRedSquare(int x,int y,int leng);
void blinkRedSquare();
void updateGreenSquare(int currX,int currY,int nextX,int nextY);
int makeaTurn();
void makeaShift(int r,int c,int val);
void mySleep();
void printX(int x,int y); // x=col , y=row  --> for printing X
void printO(int x,int y); // x=col , y=row  --> for printing Y
void updateBoard(); // for updating the values of the matrix 
int callPlayer(int player);
void callPlayerTillWrite(int player);
int winCheck(int val);
void printR();
void printRoundO();
void printU();


int prevRow=0,prevCol=0;

int main(){
  clear_screen();
  makeBoard();
  printRound();

  prevRow=0,prevCol=0;


  int check=0;
  for(int i=1;i<=9;i++){
    int par=((i&1) == 1)?1:0;
    callPlayerTillWrite(par);
    check=winCheck(par);
    if(check == 1) break;
  }

  return 0;
}

// -------------------------------------------------------------------------------------------------------------------------------------------
// Function for gameplay Mechanics 


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

void printRound(){
  for(int y=190;y<240;y++){
    for(int x=0;x<320;x++){
      write_pixel(x,y,LGRAY);
    }
  }
  // print R
  printR();
  printRoundO();
  printU();
}

// Print R
void printR(){
  drawThickLine(5,200,5,230,5,NAVY);
  drawThickLine(5,200,20,200,5,NAVY);
  drawThickLine(5,215,20,215,5,NAVY);
  drawThickLine(5,215,25,230,5,NAVY);
  drawThickLine(20,200,20,215,5,NAVY);
}

void printRoundO(){
  drawThickLine(35,200,35,230,5,NAVY);  // |
  drawThickLine(35,200,50,200,5,NAVY);  // -
  drawThickLine(50,200,50,230,5,NAVY);  // |  
  drawThickLine(35,230,50,230,5,NAVY);  // _
}

void printU(){
  drawThickLine(65,200,65,230,5,NAVY);
  drawThickLine(65,230,80,230,5,NAVY);
  drawThickLine(80,200,80,230,5,NAVY);
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
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
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
