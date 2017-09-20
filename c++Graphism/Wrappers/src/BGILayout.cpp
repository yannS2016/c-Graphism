#include "BGILayout.h"
/// define some constant
static short orgWidth  = 0;
static short orgHeight = 0;
static short oldWidth  = 0;
static short oldHeight = 0;
BGILayout::BGILayout()
{
    this->lParent = parent;
    this->lOrientation = BGILayouts::LAY_OUT_HORIZ; // default orientation
    orgWidth = parent->getWidth();
    orgHeight = parent->getHeight();
}

BGILayout::~BGILayout()
{
    //dtor
}

BGILayout::BGILayout(BGILayouts orientation, BGIRec margins)
: layoutMargins(margins)
{
    this->lParent = parent;
    this->lOrientation = orientation;
    orgWidth = parent->getWidth();
    orgHeight = parent->getHeight();
}

BGILayout::BGILayout(const BGILayout& other)
{
    //copy ctor
}
bool BGILayout::VertResize()
{
    int contSize = lParent.;
    if(this->lParent->getWidth() > orgWidth || this->lParent->getWidth() < orgWidth)
    {
        this->isVertResize = true;
    }
}
