#include "BGIPainter.h"
BGIPainter::BGIPainter(BGIWidget *paintDevice): pPen(), pFont()
{
    this->device = paintDevice;
}
BGIPainter::BGIPainter(BGIPen pen, BGIFont font, BGIWidget *paintDevice)
    : pPen(pen), pFont(font)
{
    this->device = paintDevice;
    DEBUG << "a Painter Object was created\n";
}

BGIPainter::~BGIPainter()
{
    this->device = nullptr;
}
void BGIPainter::drawText(BGIPoint tPos, char *tStr , bool resizable)
{
    //DEBUG << "Draw Text was executed\n";
    /* passing by reference means that the functionparameter is a reference to the object(address of object)
       therefore we must not passed a reference to the object but the object itself*/
    BGIPaintObject *object = new BGIPaintObject(tPos, resizable, tStr, TEXT);
    device->getPaintObject(object);
    //this->dangPtrCleanup.push_back(object);
    //DEBUG << "Dangling list size: " << dangPtrCleanup.size() << std::endl;

}
void BGIPainter::drawLine(BGIPoint &begPoints, BGIPoint &endPoints, bool resizable)
{
    BGIPaintObject *object = new BGIPaintObject(begPoints, endPoints, resizable, LINE);
    device->getPaintObject(object);
    //this->dangPtrCleanup.push_back(object);
}
void BGIPainter::drawLine(BGIPoint begPoints, BGIPoint endPoints, bool resizable)
{
    //DEBUG << "Draw Line was executed\n";
    /***************************************************************************************
    // it migths be that the object is destroyed when this function returns
    // even though the list still has it , but its content get reset. the reference is a dangling pointer
    // so it better to create this object on the heap so they stay when the function return
    // Note: it will be better to use to smart pointers
    ****************************************************************************************/
    BGIPaintObject *object = new BGIPaintObject(begPoints, endPoints, resizable, LINE);
    device->getPaintObject(object);
    //this->dangPtrCleanup.push_back(object);
}
/// this method are used to draw a circle on the painting device:
/// one take a copy of BGIPoint and the other takes a reference
void BGIPainter::drawCircle(BGIPoint ctrPoints, short radius, bool hasBrush ,bool resizable)
{
    BGIPaintObject *object = new BGIPaintObject(ctrPoints, radius, hasBrush, resizable, CIRCLE);
    device->getPaintObject(object);
    // we need to cleanup dangling pointer left after object deletion
    //this->dangPtrCleanup.push_back(object);
}
void BGIPainter::drawCircle(BGIPoint &ctrPoints, short radius, bool hasBrush, bool resizable)
{
    BGIPaintObject *object = new BGIPaintObject(ctrPoints, radius, hasBrush, resizable, CIRCLE);
    device->getPaintObject(object);
   // this->dangPtrCleanup.push_back(object);
}

void BGIPainter::drawBar(BGIRec endCoords, bool resizable)
{
    BGIPaintObject *object = new BGIPaintObject(endCoords, resizable, BAR);
    device->getPaintObject(object);
    //this->dangPtrCleanup.push_back(object);
}

void BGIPainter::setPen(const BGIPen &otherPen)
{
    this->pPen = otherPen;
}
void BGIPainter::setPen(const BGIColor pColor)
{
    this->pPen.setColor(pColor);
}
void BGIPainter::setPen(const BGIPenStyle pStyle)
{
    this->pPen.setStyle(pStyle);
}
void BGIPainter::setPen(const BGIBrush fillStyle,BGIColor fillColor)
{
    // fillstyle and flood fill work together.
    // fill style select the fill type and fill color while flood fill colors
    // the internal or external space with fill type and fill color
    // however with bars, setting fill type and fill color is all that's required
    delay(5); // thread synchonization delay
    this->pPen.setStyle(BGIPenStyle::SOLID_LINE); //we can only fill with solid lines
    // reset the pen color to white : flooding use white background
    this->pPen.setColor(BGIColor::WHITE);
    this->pPen.setBrush(fillStyle, fillColor);
}
void BGIPainter::setPen(const int pWidth)
{
    this->pPen.setWidth(pWidth);
}
void BGIPainter::BGIPainter::setFont(const BGIFont &otherFont)
{
    this->pFont = otherFont;
}
void BGIPainter::setFont(const BGIDir fOrient)
{
    this->pFont.setOrientation(fOrient);
    DEBUG << "New Font direction set!\n";
    DEBUG << pFont.getFontDir() << std::endl;
}
void BGIPainter::setFont(const BGIAlign fJust)
{
    this->pFont.setAlignment(fJust);
}
void BGIPainter::setFont(const int fSize)
{
    this->pFont.setFontSize(fSize);
}
void BGIPainter::setFont(const BGIFonts tFont)
{
    this->pFont.setFont(tFont);
}
// this set a viewport( a drawing 2D drawing space within the paint  device)
void BGIPainter::setViewPort(BGIRec rec, bool anchor)
{
    setviewport(rec.getLeft(),rec.getTop(),rec.getRight(),rec.getBottom(),anchor);
}
