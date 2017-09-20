#include "BGIFont.h"

BGIFont::BGIFont()
{
    /// SANS_SERIF_FONT and SMALL FONT dont work with VERTICAL ORIENTATION
    this->tFont = BGIFonts::SCRIPT_FONT;
    this->tDir = BGIDir::DIR_HORIZ;
    this->tAlign = BGIAlign::TEXT_LEFT;
    this->tSize = 1;
    settextstyle(this->tFont,this->tDir,this->tSize);
    settextjustify(this->tAlign,this->tAlign);
    DEBUG << "A font object was created\n";
}
BGIFont::BGIFont(const BGIFont &other)
{
    this->tFont = other.getFont();
    this->tDir =  other.getFontDir();
    this->tAlign = other.getFontAlign();
    this->tSize = other.getFontSize();
}
BGIFont::~BGIFont()
{
    //dtor
}
BGIFont::BGIFont(const BGIFonts font, const BGIDir Orientation, const BGIAlign textAlign, const int fontSize)
{
    this->tFont = font;
    this->tDir = Orientation;
    this->tAlign = textAlign;
    this->tSize = fontSize;
    DEBUG <<"A font object was created with overloaded constructor\n";
    settextstyle(this->tFont,this->tDir,this->tSize);
    if(this->tDir == DIR_HORIZ){
        if(textAlign == TEXT_TOP || textAlign == TEXT_BOTTOM){
           this->tAlign = TEXT_LEFT;
        }
    }
    else {
        if(textAlign == TEXT_LEFT || textAlign == TEXT_RIGHT){
            this->tAlign = TEXT_BOTTOM;
        }
        else{
           this->tAlign = ((textAlign == static_cast<BGIAlign>(3)) ? static_cast<BGIAlign>(0) :static_cast<BGIAlign>(2));
        }
    }
   settextjustify(this->tAlign,this->tAlign);
    int errorcode = graphresult();
    if(errorcode != grOk)
        DEBUG << "grError: Invalid Input For Text Alignment!\n";
}
/********************************************************************/
void BGIFont::setFont(const BGIFonts font)
{
      delay(1);
      this->tFont = font;
      settextstyle(this->tFont,this->tDir,this->tSize);
      //delay(1);
}
/********************************************************************/
void BGIFont::setFontSize(const int fontSize)
{
       this->tSize = fontSize;
       delay(2);// smallest delay value for correct operation
       settextstyle(this->tFont,this->tDir,this->tSize);
}
/**********************************************************************/
void BGIFont::setOrientation(const BGIDir Orientation)
{
    /****************************************************************************
     // the delay below is added because the drawing system
     // seems to be redrawing shapes with last set attributes
     // this is highly unwanted.
     // it can be that the paintdevice thread is running faster that the graphics.h
     // drawing system thread thus graphics.h only cathes the last color setting
     // so we slow down our  painting to give internal system time to execute the
     // commands
     **********************************************************************/
        delay(5);
        this->tDir = Orientation;
        settextstyle(this->tFont,this->tDir,this->tSize);
}
/************************************************************************/
void BGIFont::setAlignment(const BGIAlign textAlign)
{
    //delay(1);
    this->tAlign = textAlign;
    settextjustify(textAlign,textAlign);
    int errorcode = graphresult();
    if(errorcode != grOk)
        DEBUG << "grError: Invalid Input for Text Alignment!\n";
}
/** Getter methods****/
BGIFonts BGIFont::getFont() const
{
    return this->tFont;
}
int BGIFont::getFontSize() const
{
    return this->tSize;
}
BGIDir BGIFont::getFontDir() const
{
    return this->tDir;
}
BGIAlign BGIFont::getFontAlign() const
{
    return this->tAlign;
}
BGIPoint BGIFont::getFontMetrics(char *str)
{
    /**
    // All BGIFont objects access and modify the same internal data as there are created.
    // The last created determines the state of internal data: Therefore this method must
    // be called to get the font metrics for the selected font before another font object is created
    */
    this->fontMetrics.setX(textwidth(str));
    this->fontMetrics.setY(textheight(str));
    return this->fontMetrics;
}
