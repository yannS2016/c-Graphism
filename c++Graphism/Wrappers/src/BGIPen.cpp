#include "BGIPen.h"

BGIPen::BGIPen()
{
    this->penStyle  = BGIPenStyle::SOLID_LINE;
    this->penWidth = static_cast<int>(THICK_WIDTH);
    this->penColor =BGIColor::BLACK;
    this->penBrush = BGIBrush::SOLID_FILL;
    setcolor(BGIColor::RED);
    setlinestyle(this->penStyle ,0,this->penWidth);
    setfillstyle(BGIBrush::EMPTY_FILL,this->penColor); // use window background color
    std::cout <<"A pen object was created\n";
}
BGIPen::BGIPen(const BGIPen& other)
{
    this->penStyle = other.getStyle();
    this->penWidth = other.getPenWidth();
    this->penColor = other.getPenColor();
    this->penBrush = other.getPenBrush();
}
BGIPen::~BGIPen()
{
    //dtor
}
int BGIPen::LIMIT(int x)
{
    if(x >= NORM_WIDTH && x < THICK_WIDTH)
        return static_cast<int>(NORM_WIDTH);
    else if(x > THICK_WIDTH)
        return static_cast<int>(THICK_WIDTH);
    else
        return static_cast<int>(THICK_WIDTH);
}

BGIPen::BGIPen(const BGIColor color, const int width, const BGIPenStyle style, const BGIBrush brush)
{
    this->penColor = color;
    this->penWidth = LIMIT(width);
    this->penStyle = style;
    this->penBrush = brush;
    setcolor(color);
    setlinestyle(this->penStyle ,0,this->penWidth);
    int errorcode = graphresult();
    if(errorcode != grOk)
        DEBUG << "grError: Invalid Input for line style! \n";
    setfillstyle(this->penBrush,this->penColor); // use window background color
    if(errorcode != grOk)
        DEBUG << "grError: Invalid Input for fill style or color! \n";
   // DEBUG <<"A pen object was created with overloaded constructor\n";
}
void BGIPen::setStyle(BGIPenStyle style)
{
    /*
        BUG in graphics.h: the different line types are only visible for
        width size of 1 when width > 1 only solid-line are visible
        we default to a width of one when we need to set style
    */
    delay(1);
    this->penStyle = style;
    setlinestyle(this->penStyle,0,1);
    int errorcode = graphresult();
    if(errorcode != grOk)
        DEBUG << "grError: Invalid Input for line style! \n";
}
void BGIPen::setWidth(const int width)
{
    delay(1);
    this->penWidth = LIMIT(width);
    setlinestyle(this->penStyle,0,this->penWidth);
    int errorcode = graphresult();
    if(errorcode != grOk)
        DEBUG << "grError: Invalid Input for line width! \n";
}
void BGIPen::setBrush(const BGIBrush brush, BGIColor bColor)
{
    delay(2);// thread synchonizing delay
    this->penBrush = brush;
    setfillstyle(brush,bColor);
    int errorcode = graphresult();
    if(errorcode != grOk)
        DEBUG << "grError: Invalid Input for fill style or color! \n";
}
 void BGIPen::setColor(const BGIColor color)
 {
     /****************************************************************************
     // the delay below is added because the drawing system
     // seems to be redrawing shapes with last set color
     // this is highly unwanted.
     // it can be that the paintdevice thread is running faster that the graphics.h
     // drawing system thread thus graphics.h only cathes the last color setting
     // so we slow down our  painting to give internal system time to execute the
     // commands
     **********************************************************************/
     delay(1);
     this->penColor = color;
     // update pen color only new color # to old color
     if(this->penColor != getcolor())
        setcolor(this->penColor);
 }
BGIColor BGIPen::getPenColor() const
{
     if(this->penColor != getcolor()){
        DEBUG << "Internal and graphic system color differ!\n";
        // we cast the integer to a BGIColor enum since getcolor() return an int
        return static_cast<BGIColor>(getcolor());
     }
     else
        return this->penColor;
}
 BGIBrush BGIPen::getPenBrush() const
 {
     BGIFillSettings fillStyles;
     // copy internal fill setting data to user define structure
     getfillsettings(&fillStyles);
   if(this->penBrush != fillStyles.pattern){
     DEBUG << "Internal and graphic system linestyle differ!\n";
     // safe to cast statically since an enum is an int and vice versa
     return static_cast<BGIBrush>(fillStyles.pattern);
   }
   return this->penBrush;
 }
BGIPenStyle BGIPen::getStyle() const
{
   BGILineSettings styles;
   getlinesettings(&styles);
   if(this->penStyle != styles.linestyle){
     DEBUG << "Internal and graphic system linestyle differ!\n";
     // safe to cast statically since an enum is an int and vice versa
     return static_cast<BGIPenStyle>(styles.linestyle);
   }
   return this->penStyle;
}
// using int cause the fucntion to convert the return type to a character
//
int BGIPen::getPenWidth() const
 {
   BGILineSettings styles;
   getlinesettings(&styles);
   //std::cout << styles.thickness << std::endl;
   if(this->penWidth != styles.thickness){
     DEBUG << "Internal and graphic system pen width differ!\n";
     return styles.thickness;
   }
   return this->penWidth;
 }
