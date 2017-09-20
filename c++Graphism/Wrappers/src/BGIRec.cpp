#include "BGIRec.h"
BGIRec::BGIRec()
{
    //ctor
    this->rLeft = this->rTop = 0;
    this->rRight = this->rBottom = 0;
}

BGIRec::~BGIRec()
{
    //dtor
}

BGIRec::BGIRec(const int mleft, const int mTop, const int mRight, const int mBottom)
{
    //copy ctor
    this->rLeft = mleft;
    this->rTop = mTop;
    this->rRight =  mRight;
    this->rBottom = mBottom;
}
BGIRec::BGIRec(const BGIRec &otherSize)
{
    //copy ctor
    this->rLeft  =  otherSize.getLeft();
    this->rTop   = otherSize.getTop();
    this->rRight =  otherSize.getRight();
    this->rBottom = otherSize.getBottom();
}
bool BGIRec::isValid()const
{
    return ((rRight - rLeft) >= 0 && (rBottom - rTop) >= 0);
}
/**************************************************
// Access Method
****************************************************/
#define ACCESS_METHOD(type, name)                   \
void BGIRec::set##name(const type value){           \
    type temp;                                      \
    temp = value;                                   \
    if(this->r##name != temp) {                     \
        this->r##name = temp;                       \
    }                                               \
}                                                   \
type BGIRec::get##name() const {                    \
    return this->r##name;                           \
}
ACCESS_METHOD(int,    Left)
ACCESS_METHOD(int,    Top)
ACCESS_METHOD(int,    Right)
ACCESS_METHOD(int,    Bottom)
#undef ACCESS_METHOD
