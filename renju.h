#include <gtk/gtk.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HUMAN                1          
#define COMPUTER             2           
#define EMPTY                3            
#define NUM                  16            
#define MAXSIZE              300            
#define SIZE                 28              
#define CMANSIZE             (SIZE-10)        
#define WINDOW_BORDER_WIDTH  10                
#define DRAWING_AREA_WIDTH   (NUM*SIZE+1)       
#define DRAWING_AREA_HEIGHT  (NUM*SIZE+1)        
#define LABELWIDTH           DRAWING_AREA_WIDTH   
#define LABELHEIGHT          20                    
#define WINWIDTH             (DRAWING_AREA_WIDTH+20)
#define WINHEIGHT            (DRAWING_AREA_HEIGHT+LABELHEIGHT+25)

#define CURTOPOS(x) (x/SIZE*SIZE+(SIZE-CMANSIZE)/2)  
#define CURTOROW(x) (x/SIZE)                      
#define ROWTOPOS(x) (x*SIZE+(SIZE-CMANSIZE)/2)    

int play(int, int, int *, int *);                  
int isWin(int );                                  
int firstStep(int, int, int *, int *);           
int judge(int, int, int *, int *);              
int judgePoint(int, int , int, int , int , int *, int *);
int forcast(int, int, int *, int *);           
int findTwo(int, int, int, int, int, int *, int *); 
int isIllegal(int , int , int );                   
