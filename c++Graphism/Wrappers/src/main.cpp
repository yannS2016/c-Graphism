#include <iostream>
#include <ctime>
#include "BGIWidget.h"
#include "BGIPainter.h"

int main(void){
    /*********************** How are  main variable destroyed ****************************
    // the actual release of memory created in main occurs ater the return statement
    // object are deleted in reverse order of creation: last created first destroyed
    // mPaint will be released after mainWindow since we put mainWindow on the heap.
    // this is unwanted  behavior: we need to put all painting within additional
    // scope braces in main so that mPainter is destroyed before mainWindow.
    // Note: it is recommended to have mainWindow on the stack and choose wether to place
             painters on the heap or stack. if painter is on heap it must be released by user
    *****************************************************************************************/
    BGIWidget mainWindow("BGIWidget",500,600);
    /// passing a mainWindow ref to painter also ensure that a painter is created after mainWindow
    //BGIPainter mPaint(BGIPen(),BGIFont(BGIFonts::SCRIPT_FONT,BGIDir::DIR_HORIZ,BGIAlign::TEXT_LEFT,1),&mainWindow);
    // create a painter on the heap with default attributes
    BGIPainter *mPainter = new BGIPainter(&mainWindow);
   /*char mystr[50];
    strcpy(mystr,"Hello CodeBlocks");
    mPaint.drawText(BGIPoint(50,150), mystr,true);
    // set font width
    mPaint.setFont(5);
    // set font direcction
    mPaint.setFont(BGIDir::DIR_VERT);
    // set pen color
    mPaint.setPen(BGIColor::BLUE);
    mPaint.setFont(BGIAlign::TEXT_CENTER);
    mPaint.drawText(BGIPoint(50,200), mystr,true);

    mPaint.drawLine(BGIPoint(50,50),BGIPoint(100,100),true);
    mPaint.setPen(1);
    mPaint.setPen(BGIPenStyle::DASHED_LINE);
    mPaint.drawLine(BGIPoint(10,10),BGIPoint(10,50),true);

    mPaint.setPen(BGIColor::GREEN);
    mPaint.drawCircle(BGIPoint(200,50),50,false,true);
    // this call is needed to paint a circle with fill attribute
    mPaint.setPen(BGIBrush::SOLID_FILL,BGIColor::YELLOW);
   // delay(500);
    mPaint.drawCircle(BGIPoint(250,150),50,true,true);
    delay(500);
    mPaint.setPen(BGIBrush::INTERLEAVE_FILL,BGIColor::GREEN);
    mPaint.drawCircle(BGIPoint(250,150),50,true,true);
    delay(500);
    mPaint.setPen(BGIBrush::SOLID_FILL,BGIColor::RED);
    mPaint.drawCircle(BGIPoint(250,150),50,true,true);
    // it seems like we need to set the fill style and color before drawing a bar.
    mPaint.drawBar(BGIRec(150,200,200,300),true);

   // bar(50, 50, 100, 100);
   // bar3d(50, 50, 100, 100,1,0);
     // used viewport to flood a shape from a container viewport
     // use vieport port to create context menu for mouse event.
     // before flooding, reset the pen color to white as this is the color use to paint borders.
     // use viewport for temporary painting(in response to user event).
    /// use of dynamic painter*/
   // mPainter->setPen(BGIBrush::SOLID_FILL,BGIColor::YELLOW);
    //mPainter->drawBar(BGIRec(150,310,200,400),true);
    mPainter->drawCircle(BGIPoint(250,150),50,false,true);
    /// done using dynamic painter ?
    delete mPainter; // release it.
    /** This calls below a required for correct operation **/
    mainWindow.pause();
    mainWindow.close();
    //delete mainWindow;

    return 0;
}
