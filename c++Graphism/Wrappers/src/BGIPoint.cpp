#include "BGIPoint.h"

BGIPoint::BGIPoint()
{
    //ctor
    this->mX = this->mY = 0;
}

BGIPoint::~BGIPoint()
{
    //dtor
}

BGIPoint::BGIPoint(const short x, short y)
{
    //copy ctor
    this->mX = x;
    this->mY = y;
}
BGIPoint::BGIPoint(const BGIPoint &otherSize)
{
    //copy ctor
    this->mX =  otherSize.getX();
    this->mY = otherSize.getY();
}
bool BGIPoint::isValid()const
{
    return (this->mY >= 0 && mX >= 0);
}
/**************************************************
// Access Method
****************************************************/
#define ACCESS_METHOD(type, name)                   \
void BGIPoint::set##name(const type value){          \
    type temp;                                      \
    temp = value;                                     \
    if(this->m##name != temp) {                     \
        this->m##name = temp;                       \
    }                                               \
}                                                   \
type BGIPoint::get##name() const {                   \
    return this->m##name;                           \
}
ACCESS_METHOD(short,    X)
ACCESS_METHOD(short,    Y)
#undef ACCESS_METHOD
