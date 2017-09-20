#ifndef BGIPAINTOBJECT_H
#define BGIPAINTOBJECT_H
#include "BGIPoint.h"
#include "BGIRec.h"
#include "BGIConstant.h"
#include <atomic>
class BGIPaintObject
{
    public:
        /** Default constructor */
        BGIPaintObject(BGIPoint &pos, bool scaleO , char* charStr, BGIPaintType ID);
        /// This constructor is used to create lines and bar objects
        BGIPaintObject(BGIPoint &bPoints, BGIPoint &ePoints, bool scaleO, BGIPaintType ID);
        BGIPaintObject(BGIRec &bRec, bool scaleO, BGIPaintType ID);
        BGIPaintObject(BGIPoint &cPoints, short rad, bool hasBrush, bool scaleO, BGIPaintType ID);
        /** Default destructor */
        virtual ~BGIPaintObject();
        bool isResizable(bool scale);
        void draw();
        bool isObjDrawn();
        void resetFlag(bool state);
        BGIPaintType getShapeID() const;
        void redrawCircle(short nRad);

    protected:

    private:
        BGIPoint oPos;
        BGIRec oBdRec;
        char *oText;
        BGIPaintType drawId;
        bool scaleObject;
        bool isFilled;
        std::atomic<bool> isDrawn;
        short radius;

};

#endif // BGIPAINTOBJECT_H
