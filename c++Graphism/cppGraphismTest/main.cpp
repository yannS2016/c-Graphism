#include <iostream>
#include <graphics.h>
#include <ctime>
#include <iomanip>
int eventID = 0;
int drawLine(int x1, int y1, int x2, int y2 )
{
    //line(x1,y1,x2,y2);
    return eventID = x1 + y1 - x2 - y2;
}
int drawText(int x, int y, char *textStr)
{
    //outtextxy(x,y,textStr);
    return eventID = 2;
}
typedef int (*mline)(int x1, int y1, int x2, int y2);
typedef int (*mText)(int x, int y, char *textStr);
typedef int (*generic_ptr)(void);
generic_ptr func_table[2] = {(generic_ptr)drawLine, (generic_ptr)drawText };
#define CLIP_ON 1
/* the names of the fill styles supported */

char *fname[] = { "EMPTY_FILL", "SOLID_FILL", "LINE_FILL", "LTSLASH_FILL", "SLASH_FILL", "BKSLASH_FILL",
                  "LTBKSLASH_FILL", "HATCH_FILL", "XHATCH_FILL", "INTERLEAVE_FILL", "WIDE_DOT_FILL", "CLOSE_DOT_FILL", "USER_FILL" };

int main(void){
   /* request autodetection */

   int gdriver = DETECT, gmode, errorcode;

   int midx, midy, i;



   /* initialize graphics and local variables */

   initgraph(&gdriver, &gmode, "");



   /* read result of initialization */

   errorcode = graphresult();

   if (errorcode != grOk) {   /* an error occurred */

      //printf("Graphics error: %s\n", grapherrormsg(errorcode));



      //printf("Press any key to halt:");

      getch();

      exit(1);               /* terminate with an error code */

   }



   midx = getmaxx() / 2;

   midy = getmaxy() / 2;



   /* loop through the fill patterns */

   for (i=SOLID_FILL; i<USER_FILL; i++) {

      /* set the fill style */

      setfillstyle(i, getmaxcolor());



      /* draw the bar */

      bar(50, 50, 100, 100);

      getch();

   }

   /* clean up */

   closegraph();

   return 0;
}
