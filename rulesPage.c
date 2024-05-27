#include"Algorithms.c"
#include"basicWritingFunctions.c"

// Rules Page -----------------------------------------------------------------------------------------------------
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

