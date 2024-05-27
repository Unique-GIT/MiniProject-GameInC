#include"basicWritingFunctions.c"
#include"Algorithms.c"

// letters of Round and number ! 

void printOne();
void printTwo();
void printThree();


// print round number 
void print01fn();
void print10fn();
void print11fn();


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


// round numbers  ---------------------------------------------------

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
