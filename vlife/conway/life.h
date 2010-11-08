/*
 * life.h -- common include file for conway's life
 *
 * please see the file life.c for more information
 *
 * life is copyright � 1995, Jim Wise
 * You may redistribute this code freely.
 * You may modify and redistribute this code freely as long as you retain
 * this paragraph and an indication that the code has been modified.
 * life comes with absolutely NO WARRANTY.
 */

#ifndef LIFE_H
#define LIFE_H

#define	VERSION_STR	"1.3"

/* default settings for these two... should be overridden by specific builds */
#define	XMAX	80
#define	YMAX	23

/* board selectors */
#define	BOARD_A	0
#define	BOARD_B	1

/* (abstract) file open modes */
#define WRITEFILE	0
#define	READFILE	1

/* board file magic words */
#define FILE_HEADERSTRING	"Life, copyright 1995, Jim Wise\nFile Format Version 1.0\n\n"
#define FILE_SIZESTRING		"Board Size "
#define	FILE_SEPSTRING		"----------\n"
#define FILE_SIZEFMT		"%d x %d\n"

/* visible world runs from 1..?MAX+1, with fenceposts all around */
typedef unsigned char Board[YMAX+3][XMAX+3];

/* shared routines */

int	checkstring (char *, ...);
void	clear_board (int);
int	closefile (void);
int	determine (int, int, int);
void	display (int);
int	edit (int);
void	filemenu (int which);
void	findbounds (int);
void	generation (int, int);
int	getboard (int, int, int);
int	getcell (void);
int	getname (char *);
int	getsize (int *, int *);
int	load (int, char *);
void	message(char *, ...);
int	openfile (char *, int);
void	prompt(char *, ...);
int	putboard (int);
int	putcell (int);
int	putsize (int, int);
int	putstring (char *, ...);
void	run (void);
int	save (int, char *);

extern Board	world[2];

#define CELL(row, col)	world[which][row][col]
#define	OTHER(a)	((a) ? 0 : 1)
#define MIN(x,y)	(((x)<=(y)) ? (x) : (y))
#define MAX(x,y)	(((x)>=(y)) ? (x) : (y))

#define	NAMELEN		512
#define	MENUSTR		"[L]oad; [S]ave; [R]eturn"
#define	EDIT_INSTSTR	"Move [keypad/hjkl]; Toggle [5/space]; [F]ile; [C]lear; [G]o; [Q]uit"

#define	CHAR(x)	((x) ? '*' : ' ')

#endif
