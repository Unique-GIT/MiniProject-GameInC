#include"basicWritingFunctions.c"
#include"Algorithms.c"
#include"alphabets.c"

void printBetPage(int player){
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
}
