/*
 * thinkedit.c -- mac-specific (console) board editing code for Conway's Life
 *
 * please see the file life.c for more information
 *
 * life is copyright � 1995, Jim Wise
 * You may redistribute this code freely.
 * You may modify and redistribute this code freely as long as you retain
 * this paragraph and an indication that the code has been modified.
 * life comes with absolutely NO WARRANTY.
 */

#include <stdio.h>
#include <curses.h>
#include "life.h"

#define	MOVECURSOR(delta_x, delta_y)		\
  cgotoxy(xcur, ycur, stdout);			\
  putc(CHAR(world[which][xcur][ycur]), stdout);	\
  xcur = MAX(MIN(xcur + delta_x, XMAX), 1);	\
  ycur = MAX(MIN(ycur + delta_y, YMAX), 1)	
					
/*
 * edit() -- allow the user to set up the board.
 * Returns 1 if the user wants to run, 0 if the user wants to quit...
 * This version, for the Think C console environment, implements a simple
 * text-based screen editing, using the commands described in life.c
 */

int
edit (int which) {
  char	c;
  int	xcur = 1, ycur = 1;
	
  display(which);
			
  /* Don't use message() to avoid pause */
  cgotoxy(1, YMAX+1, stdout);
  printf(EDIT_INSTSTR);
  ccleol(stdout);
	
  while (1) {
    cgotoxy(xcur, ycur, stdout);
    putc('%', stdout);
		
    c = getc(stdin);
		
    switch (c) {
    case 'h':
    case '4':
      MOVECURSOR(-1, 0);
    break;
    case '7':
      MOVECURSOR(-1, -1);
      break;
    case 'k':
    case '8':
      MOVECURSOR(0, -1);
    break;
    case '9':
      MOVECURSOR(1, -1);
      break;
    case 'l':
    case '6':
      MOVECURSOR(1, 0);
    break;
    case '3':
      MOVECURSOR(1, 1);
      break;
    case 'j':
    case '2':
      MOVECURSOR(0, 1);
    break;
    case '1':
      MOVECURSOR(-1, 1);
      break;
    case ' ':
    case '5':
      world[which][xcur][ycur] = OTHER(world[which][xcur][ycur]);
    break;
#ifndef	NO_FILE
    case 'f':
      filemenu(which);
      cgotoxy(1, YMAX+1, stdout);
      printf(EDIT_INSTSTR);
      ccleol(stdout);
      break;
#endif
    case 'q':
      return(0);
      break;
    case 'g':
      cgotoxy(xcur, ycur, stdout);
      putc(CHAR(world[which][xcur][ycur]), stdout);
      return(1);
      break;
    case 'c':
      clear_board(which);
      display(which);
      continue; 
    default:
      continue;
    }
  }
}
