#include "BGIPaintObject.h"
///this constructor is use to draw a text on painting device
BGIPaintObject::BGIPaintObject(BGIPoint &pos, bool scaleO, char* charStr, BGIPaintType ID)
: oPos(pos), oBdRec()
{
    this->oText = charStr;
    this->scaleObject = scaleO;
    this->drawId = ID;
    this->radius = 0;
    this->isDrawn = false;
}
/// this constructor is used to draw a line on painting device
BGIPaintObject::BGIPaintObject(BGIPoint &bPoints, BGIPoint &ePoints, bool scaleO, BGIPaintType ID)
: oPos(),oBdRec(bPoints.getX(),bPoints.getY(),ePoints.getX(),ePoints.getY())
{
    this->oText = NULL;
    this->scaleObject = scaleO;
    this->drawId = ID;
    this->radius = 0;
    this->isDrawn = false;
}
/// this constructor is used to draw a bar on the painting device
BGIPaintObject::BGIPaintObject(BGIRec &bRec, bool scaleO, BGIPaintType ID)
: oPos(),oBdRec(bRec)
{
    this->oText = NULL;
    this->scaleObject = scaleO;
    this->drawId = ID;
    this->radius = 0;
    this->isDrawn = false;
}
/// this constructor is used to draw a circle on the painting device
BGIPaintObject::BGIPaintObject(BGIPoint &cPoints, short rad, bool hasBrush, bool scaleO, BGIPaintType ID)
: oPos(cPoints), oBdRec()
{
    this->oText = NULL;
    this->scaleObject = scaleO;
    this->drawId = ID;
    this->radius = rad;
    this->isFilled =  hasBrush;
    this->isDrawn = false;
}
BGIPaintObject::~BGIPaintObject()
{
    //dtor
}
void BGIPaintObject::redrawCircle(short nRad)
{
    this->radius = nRad;
    this->draw();
}
void BGIPaintObject::draw()
{
    //there seem to be a bug with outextxy when calling it from another thread but main
    // the problem was locking draw loop within mutexes
    switch(this->drawId)
    {
        case BAR:       bar(oBdRec.getLeft(),oBdRec.getTop(),oBdRec.getRight(), oBdRec.getBottom());
                        //bar(100,100,150,200);
                        this->isDrawn = true;
                        break ;
        case TEXT:      outtextxy(this->oPos.getX(),this->oPos.getY(),this->oText);
                        outtextxy(this->oPos.getX(),this->oPos.getY(),this->oText);
                        this->isDrawn = true;
                        break;
        case LINE:
                        line(oBdRec.getLeft(),oBdRec.getTop(),oBdRec.getRight(),oBdRec.getBottom());
                        this->isDrawn = true;
                        //delay(500);
                        break;
        case CIRCLE:    circle(this->oPos.getX(),this->oPos.getY(),this->radius);
                        this->isDrawn = true;
                        if(this->isFilled)
                            floodfill(this->oPos.getX(),this->oPos.getY(),WHITE);
                        break;
        case ELLIPSE:   break;
    }
}
bool BGIPaintObject::isResizable(bool scale)
{
    return (this->scaleObject = scale);
}
bool BGIPaintObject::isObjDrawn()
{
    if(this->isDrawn)
        return true;
    else
        return false;
}
BGIPaintType BGIPaintObject::getShapeID()const
{
    return this->drawId;
}
/*void BGIPaintObject::resetFlag(bool state)
{
    this->isDrawn = state;
    DEBUG << "Reset it " << this->isDrawn << std::endl;
}*/
