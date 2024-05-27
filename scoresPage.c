#include"Algorithms.c"
#include"basicWritingFunctions.c"

void scoresPage(int scoreOne,int scoreTwo);
void convertToStringAndPrint(int score,int x,int y);

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