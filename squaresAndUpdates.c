#include"basicWritingFunctions.c"
// ------------------------------------------------------------------------------------------------------------------------------------------------------
// Some functions to draw basic shapes ! 

// Making squares .....------------------------------------------------------
void makeSquare(int X ,int Y ,int leng ,short colour);
void makeGreenSquare(int x,int y,int leng);
void makeWhiteSquare(int x,int y,int leng);
void makeRedSquare(int x,int y,int leng);
void blinkRedSquare(); 

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


// Updating squares --------------------------------------------------------------------------
// Updating the shifting of the green square !
void updateGreenSquare(int currX,int currY,int nextX,int nextY){
  makeWhiteSquare(currX,currY,50);
  makeGreenSquare(nextX,nextY,50);
  updateBoard();
}

