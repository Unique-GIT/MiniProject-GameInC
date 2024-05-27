#include"Algorithms.c"
#include"basicWritingFunctions.c"

void welcomePage();
void printRoll();


// Welcome Page -------------------------------------------------------------------------------------------------
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


