#include"basicWritingFunctions.c"
#include"Algorithms.c"


void printRoundForDisplay();
void printR();
void printRoundO();
void printU();
void printN();
void printD();

void printMode(int player);

// Print ROUND 

// print X and O 
void printO(int x,int y); // x=col , y=row  --> for printing Y
void printX(int x,int y); // x=col , y=row  --> for printing X


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


// ------------------------------------------
// print X and print O

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


// print MODE for MODE page


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