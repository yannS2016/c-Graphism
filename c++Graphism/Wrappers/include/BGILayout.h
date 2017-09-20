#ifndef BGILAYOUT_H
#define BGILAYOUT_H

#include <BGIRec.h>
#include "BGIConstant.h"
#include "BGIWidget.h"
class BGILayout : public BGIRec
{
    public:
        /** Default constructor */
        BGILayout(BGIWidget *parent);
        BGILayout(BGILayouts orientation, BGIRec margins, BGIWidget *parent);
        /** Default destructor */
        virtual ~BGILayout();
        /** Copy constructor
         *  \param other Object to copy from
         */
        BGILayout(const BGILayout& other);
        void setOrientation(BGILayouts lDir);
        void setMargins(BGIRec margins);
        bool isVertLayout();
        bool isHorizLayout();
        bool VertResize();
        bool HorizResize();

    protected:

    private:
        bool isVert;
        bool isHoriz;
        bool isVertResize;
        bool isHorizResize;
        BGIRec layoutMargins;
        unsigned short spacing;
        BGIWidget *lParent;
        BGILayouts lOrientation;

};

#endif // BGILAYOUT_H
