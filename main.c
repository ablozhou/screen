//andy zhou 2014.4.24
#include <curses.h>                  /* 包含 curses.h , 并自动包含 stdio.h */ 
#include <stdlib.h>
#include <string.h>
#define StartX  1                    /* 决定光标初始位置 */ 
#define StartY  1 
void initial(); 
int main(void) 
{ 
	int x=StartX;                     /* 声明 x,y 并设定其初值 */ 
	int y=StartY; 
	int ch;                           /* 声明 ch 为整数,配合 getch() 使用   */ 

	initial();                        /* 调用 initial(), 启动 curses 模式, 并完成其它设定 */ 

	box(stdscr,'|','-');              /* 画方框 */ 

	//attron(A_REVERSE);                /* 开启反白模式 */ 
	init_pair(1, COLOR_RED, COLOR_GREEN); /*建立一个颜色对*/
	attron(COLOR_PAIR(1)); /*开启字符输出颜色*/
	//mvaddstr(0,20,"Curses Program");  /* 在 (20,0) 处输出反白字符 */ 
	const char* title="Curses Program";
	mvaddstr(0,(COLS-strlen(title))/2,title);  /* 在 (0,COLS/2) 处输出标题，LINES,COLS是宏 */ 
	//attroff(A_REVERSE);               /* 关闭反白模式 */ 
	attroff(COLOR_PAIR(1)); 			/*关闭颜色显示*/
	move(x,y);                         /* 将光标移至初始位置 */ 

	do {                              /* 以无限循环不断等待输入 */ 
		ch=getch();                      /* 等待自键盘输入字符*/ 
		switch(ch) {                     /* 判断输入字符为何 */ 

		case KEY_UP: 
			--y;             /* 判断是否"↑"键被按下 */ 
			break; 
		case KEY_DOWN: 
			++y;           /* 判断是否"↓"键被按下 */ 
			break; 
		case KEY_RIGHT: 
			++x;          /* 判断是否"→"键被按下 */ 
			break; 
		case KEY_LEFT: 
			--x;           /* 判断是否"←"键被按下 */ 
			break; 
		case '\r':                    /* 判断是否 ENTER 键被按下 */ 
			++y; 
			x=StartX; 
			break; 
		case '\t':                    /* 判断是否 TAB 键被按下 */ 
			x+=7; 
			break; 
		case 127:                     /* 判断是否 BACKSPACE 键被按下 */ 
			mvaddch(y,--x,' ');/* delete 一个字符 */ 
			break; 
		case 27: 
			endwin();            /* 判断是否[ESC]键被按下 */ 
			exit(1);             /* 结束 curses 模式 */ 

		default: 
			if(x<COLS-1) {
				x++; 
			} else {
				y+=1;
				x=StartX;
			}
				addch(ch);           /* 如果不是特殊字符, 将此字符印出     */ 
				break; 
		} 
		move(y,x);                      /* 移动光标至现在位置 */ 
	} while (1); 
	return 0;
} 
void initial()                       /* 自定开启 curses 函式 */ 
{ 
	initscr(); 
	cbreak(); 
	nonl(); 
	noecho(); 
	start_color();
	intrflush(stdscr,FALSE); 
	keypad(stdscr,TRUE); 
	refresh(); 
} 

