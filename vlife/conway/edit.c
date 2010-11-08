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
#include <string.h>
#include <curses.h>
#include "life.h"

#define	MOVECURSOR(delta_x, delta_y)		\
  xcur = MAX(MIN(xcur + delta_x, XMAX+1), 1);	\
  ycur = MAX(MIN(ycur + delta_y, YMAX+1), 1);	
					
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
			
  message(EDIT_INSTSTR);
	
  while (1) {
    move(ycur-1, xcur-1);
		
    c = getch();
		
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
      CELL(ycur, xcur) = OTHER(CELL(ycur, xcur));
      addch(CHAR(CELL(ycur, xcur)));
      break;
    case 'f':
      filemenu(which);
      message(EDIT_INSTSTR);
      break;
    case 'q':
      return(0);
      break;
    case 'g':
      return(1);
      break;
    case 'c':
      clear_board(which);
      display(which);
      break;
    default:			/* e.g. ERR if no char ready */
      break;
    }
  }
}

/*
 * filemenu() -- let the user load or save a file
 */
 
void
filemenu (int which) {
  int		flag = 1;
  char	c, fname[NAMELEN];

  message(MENUSTR);

  while (flag) {
    c = getch();
		
    switch (c) {
    case 'l':
      clear_board(which);
      if (!getname(fname)) {
	if (load(which, fname))	{
	  prompt("Could not load board from file %s", fname);
	  clear_board(which);
	} else {
	  prompt("Board loaded from file %s", fname);
	}
      }
      display(which);
      message(MENUSTR);
      break;
    case 's':
      if (!getname(fname)) {
	if (save(which, fname))
	  prompt("Could not save board to file %s", fname);
	else
	  prompt("Board saved to file %s", fname);
      }
      message(MENUSTR);
      break;
    case 'r':
      flag = 0;
      break;
    default:			/* e.g. ERR, i.e. no char ready */
      break;
    }
  }
}

/*
 * getname() -- get file name from user and store in given char *
 * returns 0 on success, non-zero if user entered zero-length string
 */

int
getname(char *name) {
  message("Enter FileName: ");
  clrtoeol();
  refresh();
  
  echo();
  nocrmode();
  getstr(name);		/* XXX XXX real curses doesn't have getnstr, use wgetnstr once we have a win */
  crmode();
  noecho();

  return(!strlen(name));
}
