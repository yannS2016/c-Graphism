/*****************************************************************
// Copyright (C) 2017 Yann Stephen Mandza < mandza.y.s@gmail.com>
//                   - CPUT Bellville
// This file is part of BGI c++ based graphics
// This class is the base class for c++ wrapper classes for BGI
// graphics library. it is the all subsequent class inherits it.
// Note: This wrapper needs the use of std c++11
******************************************************************/
#ifndef BGIWRAPPER_H_INCLUDED
#define BGIWRAPPER_H_INCLUDED
#include <graphics.h>
#include <iostream>
#include <pthread.h>
#include <atomic>
#include <map>
#include <stdbool.h>
#include <wtypes.h>
// include the correct header for getting system screen res
#ifdef _WIN32
    #include <winuser.h>
#elif __linux
    #include <X11/Xlib.h>
#else
#endif // _WIN32
class BGIWidget;
class BGISize;
class BGIPen;
namespace BGI {
    typedef colors BGIColor;
    typedef struct linesettingstype BGILineSettings;
    typedef line_styles BGIPenStyle;
    typedef fill_styles BGIBrush;
    typedef font_names BGIFonts;
    typedef horiz BGIHorAlig;
    typedef vertical BGIVerAlign;
    static const int BOTTOM_FRAME_WIDTH = 10;
    static const int LEFT_FRAME_WIDTH = 9;
    static const int DEFAULT_COLOR = colors::BLACK;
    // screen limit sizes: these based on my PC screen sizes
    static const int MINIMIZED_SIZE = -1;
    static const int SCREEN_WIDTH_MARGIN = 1;
    static const int SCREEN_HEIGHT_MARGIN = 62;
    enum BGIDir { DIR_HORIZ,DIR_VERT, };
    enum BGIAlign { TEXT_LEFT = 0, TEXT_CENTER = 1, TEXT_RIGHT = 2,TEXT_BOTTOM = 0	,TEXT_TOP = 2,};
}
class BGISize
{
    public:
        /** Default constructor */
        BGISize();
        /** Default destructor */
        virtual ~BGISize();
        /** Copy constructor
         *  \param other Object to copy from
         */
        BGISize(const short winWidth, const short winHeight);

        BGISize(const BGISize &otherSize);
        #define ACCESS_METHOD(type, name)      \
            void set##name(const type value);  \
            type get##name() const;
        ACCESS_METHOD(short,Width)
        ACCESS_METHOD(short,Height)
        #undef ACCESS_METHOD // make sure ACCESS_METHOD make sense only at compile time
        //Returns true if either of the width and height is less than or equal to 0; otherwise returns false
        bool isEmpty() const;
        //Returns true if both the width and height is equal to or greater than 0; otherwise returns false.
        bool isValid() const;
    protected:

    private:
        short int mHeight;
        short int mWidth;
};

class BGIWidget
{
    public:
        /** Default constructor */
        BGIWidget();
        /** Default destructor */
        virtual ~BGIWidget();
        /** Copy constructor
         *  \param other Object to copy from
         */
        BGIWidget(const char* widgetName,short int w, short int h);
        void setHeight(short int h);
        void setWidth(short int w);
        void setBackGround(std::string color);
        short int getHeight() const;
        short int getWidth() const;
        bool isMinimized() const;
        bool isMaximized() const;
        BGISize drawAreaSizes()const ;// use by subclass to scale their content
        BGISize* refDrawSizes();// use by subclass to scale their content
    protected:

    private:
        pthread_t updateSizes();
        void initColorMap();
        static void* setWindowGeometry(void *context);
        // we declare these as atomic to protect against concurrencies
        // we can also use mmutexes
        std::atomic<short int> width;
        std::atomic<short int> height;
        //int width;
        //int height;
        // hold the reference to the thread object
        bool minimized;
        bool maximized;
        pthread_t resizeEvent;
        pthread_mutex_t lock;
        BGISize *cleanupRef;
        std::map<std::string, colors> backColors;
};
/*************************************************************
//          BGIPen class definition
// A BGIPen Object is a dedendancy to BGIPainter Object
// it set a drawing Pen attribute for painting on a BGIWidget
***************************************************************/
class BGIPen
{
    public:
        /** Default constructor */
        BGIPen();
        /** Default destructor */
        virtual ~BGIPen();
        BGIPen(const BGI::BGIColor color, const int width, const BGI::BGIPenStyle style);
        void setStyle(BGI::BGIPenStyle style);
        void setWidth(const int width);
        /// leave implementation to BGIPainter;
        //void setBrush(const BGIBrush brush);
        void setColor(const BGI::BGIColor color);
        // overload color function
        //void setColor(const int r,const int g, const int b);
        BGI::BGIPenStyle getStyle() const;
        int getPenWidth() const;
        BGI::BGIColor getPenColor() const;
    protected:

    private:
        BGI::BGIPenStyle penStyle;
        int penWidth;
        BGI::BGIColor penColor;
        int LIMIT(int x);

};
/*************************************************************
//          BGIFont class definition
// A BGIFont Object is a dedendancy to BGIPainter Object
// it set a text attributes for painting a text on a BGIWidget
***************************************************************/
class BGIFont
{
    public:
        /** Default constructor */
        BGIFont();
        /** Default destructor */
        virtual ~BGIFont();
        /** Overloaded constuctor */
        BGIFont(const BGI::BGIFonts font, const BGI::BGIDir Orientation, const BGI::BGIAlign textAlign, const int fontSize);
        void setFont(const BGI::BGIFonts font);
        void setFontSize(const int fontSize);
        void setOrientation(const BGI::BGIDir Orientation);
        void setAlignment(const BGI::BGIAlign textAlign);
        /** important getter method ***/
        BGISize getFontMetrics(char *str);

    protected:

    private:
        BGI::BGIFonts tFont;
        int tSize;
        BGI::BGIDir tDir;
        BGI::BGIAlign tAlign;
        BGISize fontMetrics;
};
#endif // BGIWRAPPER_H_INCLUDED
