#include "print.h"
#include "ports.h"
#include "string.h"

char default_color=0xf0;

char* vidmem=(char*)0xb8000;
static unsigned int curx=0, cury=0;

void clearLine(int from, int to, char color)
{				
	int i=0;
	for(i=from*COLS*2;i<to*COLS*2;i+=2){
		vidmem[i]=' ';		
		vidmem[i+1]=color;
	}			
}


void printLine(int from, int to, char msg[], char color)
{				
	int i=0, j=0;
	for(i=from*COLS*2,j=0;j<strlen(msg);i+=2){
		vidmem[i]=msg[j];		
		vidmem[i+1]=color;
		j++;
	}			
}

void move_cursor(){
	unsigned short loc=cury*COLS+curx;
	outb(0x3D4, 14);
	outb(0x3D5, loc >> 8);
	outb(0x3D4, 15);
	outb(0x3D5, loc);
}

void scroll(int line){
        unsigned short i = 0;
        clearLine(0,line-1, default_color);                                       
        for (i;i<COLS*(ROWS-2)*2;i++)
        {
                vidmem[i] = vidmem[i+COLS*2*line];
        }
        clearLine(ROWS-1-line,ROWS-2, default_color);
        if((cury - line) < 0 ) 
        {
                cury = 0;
                curx = 0;
        } 
        else 
        {
                cury -= line;
        }
        move_cursor();
}

void clear(char color){
	default_color=color;	
	clearLine(0, ROWS-1, color);
	curx=0;
	cury=0;
	move_cursor();
}

void clear_(){	
	clearLine(0, ROWS-1, default_color);
	curx=0;
	cury=0;
	move_cursor();
}

void printch(char c, char color)
{    
    switch(c)
    {
        case (0x08):
                if(curx > 0) 
                {
	                curx--;									
                   vidmem[(curx * COLS + curx)*2]=color;	                              
	       		 }
	        break;
      	case (0x09):
                curx = (curx + 8) & ~(8 - 1); 
                break;
        case ('\r'):
                curx= 0;
                break;
        case ('\n'):
                curx = 0;
                cury++;
                break;
        default:
                vidmem [((cury * COLS + curx))*2] = c;
                vidmem [((cury * COLS + curx))*2+1] = color;
                curx++; 
                break;
	
    }
    if(curx >= COLS)                                                                   
    {
        curx = 0;                                                                
        cury++;                                                                    
    }
	if(cury>=ROWS-2){
 		scroll(1);
	}
    move_cursor();
}

void print (char* ch)
{
        int i = 0;
        int length = strlen(ch);           
        for(i=0;i<length;i++)
        {
                printch(ch[i], default_color);
        }
}

void print_color (char* ch, char color)
{
        int i = 0;
        int length = strlen(ch);           
        for(i=0;i<length;i++)
        {
                printch(ch[i], color);
        }
}


void print_num(int i){
char* s[100];
int_to_ascii(i, s[100]);
print(s[100]);
}

void back_cursor(int l){
	int i=0;	
	if(l>0){
		//here 8 is the length of the shell line e.g "shell:# " (1 space) 
		if(curx>8){
		curx--;
		vidmem [((cury * COLS + curx))*2] = 0x0;
        	vidmem [((cury * COLS + curx))*2+1] = default_color;
		move_cursor();	
		}
	}
}
