#ifndef BGIPAINTER_H
#define BGIPAINTER_H
#include "BGIFont.h"
#include "BGIRec.h"
#include "BGIPen.h"
#include "BGIWidget.h"
#include <pthread.h>
#include <vector>
/****************************************************
// This class will handle paint events
// it will not draw anything by itself
// but register an array of drawing functions with there attributes
// the same array will be access inside the paintEvent method of BGIWidgets
// and via indexing the approriate method will be executed.
// since we using a array of different function definition
// we will need function pointer casting  to derefence the array
// to the correct type of function.
****************************************************************************/
class BGIPainter
{
    public:
        BGIPainter(BGIWidget *paintDevice);
        BGIPainter(BGIPen pen, BGIFont font, BGIWidget *paintDevice);
        virtual ~BGIPainter();
        void setFont(const BGIFont &otherFont);
        void setFont(const BGIFonts tFont);
        void setFont(const BGIDir fOrient);
        void setFont(const BGIAlign fJust);
        void setFont(const int fSize);
        void setPen(const BGIPen &otherPen);
        void setPen(const BGIColor pColor);
        void setPen(const BGIBrush fillStyle, BGIColor fillColor);
        void setPen(const BGIPenStyle pStyle);
        void setPen(const int pWidth);


        // the bounding rect is used as viewport for text
        void setViewPort(BGIRec rec, bool anchor);
        void drawText(BGIPoint tPos, char *tStr, bool resizable);
        void drawLine(BGIPoint &begPoints, BGIPoint &endPoints, bool resizable);
        void drawLine(BGIPoint begPoints, BGIPoint endPoints, bool resizable);
        void drawCircle(BGIPoint &ctrPoints, short radius, bool hasBrush, bool resizable);
        void drawCircle(BGIPoint ctrPoints, short radius, bool hasBrush ,bool resizable);
        void drawBar(BGIRec endCoords, bool resizable);
    protected:

    private:
        BGIPen pPen;
        BGIFont pFont;
        BGIWidget *device;
        std::vector <BGIPaintObject*> dangPtrCleanup;
};

#endif // BGIPAINTER_H
