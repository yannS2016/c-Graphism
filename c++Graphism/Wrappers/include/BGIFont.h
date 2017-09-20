#ifndef BGIFONT_H
#define BGIFONT_H
#include "BGIConstant.h"
#include "BGIPoint.h"
class BGIFont
{
    public:
        /** Default constructor */
        BGIFont();
        /** Copy constructor */
        BGIFont(const BGIFont &other);
        /** Default destructor */
        virtual ~BGIFont();
        /** Overloaded constuctor */
        BGIFont(const BGIFonts font, const BGIDir Orientation, const BGIAlign textAlign, const int fontSize);
        void setFont(const BGIFonts font);
        void setFontSize(const int fontSize);
        void setOrientation(const BGIDir Orientation);
        void setAlignment(const BGIAlign textAlign);
        /** getters ***/
        BGIFonts getFont() const;
        int getFontSize() const;
        BGIDir getFontDir() const;
        BGIAlign getFontAlign() const;
        /** important getter method ***/
        BGIPoint getFontMetrics(char *str);

    protected:

    private:
        BGIFonts tFont;
        int tSize;
        BGIDir tDir;
        BGIAlign tAlign;
        BGIPoint fontMetrics;
};

#endif // BGIFONT_H
