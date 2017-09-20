#ifndef BGIPEN_H
#define BGIPEN_H
#include "BGIConstant.h"

class BGIPen
{
    public:
        /** Default constructor */
        BGIPen();
        /** Default destructor */
        virtual ~BGIPen();
        /** Copy constructor
         *  \param other Object to copy from
         */
        BGIPen(const BGIPen& other);
        BGIPen(const BGIColor color, const int width, const BGIPenStyle style, const BGIBrush brush);
        void setStyle(BGIPenStyle style);
        void setWidth(const int width);
        void setBrush(const BGIBrush brush, BGIColor bColor);
        void setColor(const BGIColor color);
        BGIPenStyle getStyle() const;
        int getPenWidth() const;
        BGIColor getPenColor() const;
        BGIBrush getPenBrush() const;
    protected:

    private:
        BGIPenStyle penStyle;
        int penWidth;
        BGIColor penColor;
        BGIBrush penBrush;
        int LIMIT(int x);
};

#endif // BGIPEN_H
