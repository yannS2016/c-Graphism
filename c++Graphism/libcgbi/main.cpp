#include "BGIWrapper.h"
#define DEBUG std::cout << __FILE__ << " " <<__FUNCTION__ << " line " << __LINE__ << " "
// A function adding two integers and returning the result
BGIWidget::BGIWidget()
{
    // define default window size
    DEBUG << " Running Default constrcutor !!" << std::endl;
    const char* windName = __FUNCTION__;
    initwindow(400, 300,windName);
    initColorMap();
    this->setBackGround("LightGray");
    // drawing area
    this->width = 400 -  BGI::LEFT_FRAME_WIDTH;
    this->height = 300 - BGI::BOTTOM_FRAME_WIDTH;
    // Initialising color table
}

BGIWidget::~BGIWidget()
{
    // memory cleanup
    if(cleanupRef != NULL){
        delete cleanupRef;
        cleanupRef = NULL;
        DEBUG << "Size object deleted\n";
    }
    // clear the map
    this->backColors.clear();
}

BGIWidget::BGIWidget(const char* widgetName, short int w , short int h)
{
    initwindow(w, h,widgetName);
    initColorMap();
    this->setBackGround("LightGray");
    this->isMinimized();
    // remove window bottom frame width
    this->height = h - BGI::BOTTOM_FRAME_WIDTH;
    // remove window left frame width
    this->width = w - BGI::LEFT_FRAME_WIDTH;
    // block calling thread till completion
    pthread_join(this->updateSizes(),NULL);
    DEBUG << " : Running Copy constrcutor" << std::endl;
}
// start a resize event thread
pthread_t BGIWidget::updateSizes()
{
    short int thState;
    //resizeEvent = new std::thread(&BGIWidget::setWindowGeometry, this);
    pthread_mutex_init(&lock, NULL);
    thState = pthread_create(&resizeEvent,NULL,setWindowGeometry, this);
    if(thState){
        DEBUG << "Error: unable to create thread" << thState<< std::endl;
        exit(-1);
    }
    return thState;
}

void* BGIWidget::setWindowGeometry(void *context)
{
    while(1){
        short int windW =  getmaxx();
        short int windH =  getmaxy();
       // if(windW >= ((BGIWidget *)context)->width || windH > ((BGIWidget *)context)->height)
        {
            /// protect shared data against data concurrency
            //pthread_mutex_lock(&((BGIWidget *)context)->lock);
            ((BGIWidget *)context)->width = windW;
            ((BGIWidget *)context)->height = windH;
            //DEBUG << "  Updating width: " << ((BGIWidget *)context)->width << std::endl;
            //pthread_mutex_unlock(&((BGIWidget *)context)->lock);
        }
        Sleep(0.025);
    }
    pthread_exit(NULL);
    return NULL;
}
void BGIWidget::setHeight(short int h)
{
   height = h;
}
void BGIWidget::setWidth(short int w)
{
    width = w;
}

short int BGIWidget::getHeight() const
{
   return height ;
}
short int BGIWidget::getWidth() const
{
    return width;
}
void BGIWidget::initColorMap()
{
    this->backColors.insert(std::make_pair("Black",colors::BLACK));
    this->backColors.insert(std::make_pair("Blue",colors::BLUE));
    this->backColors.insert(std::make_pair("Green",colors::GREEN));
    this->backColors.insert(std::make_pair("Cyan",colors::CYAN));
    this->backColors.insert(std::make_pair("Red",colors::RED));
    this->backColors.insert(std::make_pair("Black",colors::BLACK));
    this->backColors.insert(std::make_pair("Magenta",colors::MAGENTA));
    this->backColors.insert(std::make_pair("Brown",colors::BROWN));
    this->backColors.insert(std::make_pair("LightGray",colors::LIGHTGRAY));
    this->backColors.insert(std::make_pair("DarkGray",colors::DARKGRAY));
    this->backColors.insert(std::make_pair("LightBlue",colors::LIGHTBLUE));
    this->backColors.insert(std::make_pair("LightGreen",colors::LIGHTGREEN));
    this->backColors.insert(std::make_pair("LightCyan",colors::LIGHTCYAN));
    this->backColors.insert(std::make_pair("LightRed",colors::LIGHTRED));
    this->backColors.insert(std::make_pair("LightMagenta",colors::LIGHTMAGENTA));
    this->backColors.insert(std::make_pair("Yellow",colors::YELLOW));
    this->backColors.insert(std::make_pair("White",colors::WHITE));
}
void BGIWidget::setBackGround(std::string color)
{
    // declare a looping iterator and init to map 1st element
    std::map<std::string, colors>::iterator it = backColors.begin();
    short int colorID = 0;
    bool foundIt = false;
    DEBUG << " map size: " << backColors.size() << std::endl;
    /*for( ;it!=backColors.end(); ++it){

        if(!color.compare(it->first)){
            foundIt = true;
            // return the color ID
            colorID = backColors[color];
            DEBUG << " background color is: " << colorID << std::endl;
            // color was found exit the loop
            break;
        }
     }*/
     if(backColors.find(color) != backColors.end()){
        foundIt = true;
        colorID = backColors[color];

     }
     // call graphics.h h bkg color functions
     cleardevice();
     setbkcolor(foundIt?colorID:BGI::DEFAULT_COLOR);
     cleardevice();
     setbkcolor(foundIt?colorID:BGI::DEFAULT_COLOR);
}
bool BGIWidget::isMinimized()const
{
    if(this->getWidth() == BGI::MINIMIZED_SIZE || this->getHeight() == BGI::MINIMIZED_SIZE)
        return true;
    else
        return false;
}

bool BGIWidget::isMaximized()const
{
    short int desktopX, desktopY;
    #ifdef _WIN32
        desktopX = GetSystemMetrics(SM_CXSCREEN);
        desktopY = GetSystemMetrics(SM_CYSCREEN);
        //DEBUG  << "Screen resolutions: " << desktopX << " " << desktopY << std::endl;
    #elif   __linux
        Display* disp = XOpenDisplay(NULL);
        Screen*  scrn = DefaultScreenOfDisplay(disp);
        desktopY = scrn->height;
        desktopX  = scrn->width;
    #endif // _WIN32
    if(width == (desktopX - BGI::SCREEN_WIDTH_MARGIN) || height == (desktopY - BGI::SCREEN_HEIGHT_MARGIN))
        return true;
    else
        return false;
}
BGISize BGIWidget::drawAreaSizes()const
{
    return BGISize(this->width - BGI::LEFT_FRAME_WIDTH, this->height - BGI::BOTTOM_FRAME_WIDTH);
}
BGISize* BGIWidget::refDrawSizes()
{
    BGISize *refSize = new BGISize(this->width - BGI::LEFT_FRAME_WIDTH, this->height - BGI::BOTTOM_FRAME_WIDTH);
    this->cleanupRef = refSize; // track this pointer so we delete when the class goes out of scope
    return refSize;
}
/*************************************************************************************/
BGISize::BGISize()
{
    //ctor
    this->mWidth = this->mHeight = 0;
}

BGISize::~BGISize()
{
    //dtor
}

BGISize::BGISize(const short winWidth, short winHeight)
{
    //copy ctor
    this->mWidth =  winWidth;
    this->mHeight = winHeight;
}
BGISize::BGISize(const BGISize &otherSize)
{
    //copy ctor
    this->mWidth =  otherSize.getWidth();
    this->mHeight = otherSize.getHeight();
}
bool BGISize::isValid()const
{
    return (this->mHeight >= 0 && mWidth >= 0);
}
/**************************************************
// Access Method
****************************************************/
#define ACCESS_METHOD(type, name)                   \
void BGISize::set##name(const type value){          \
    type temp;                                      \
    temp = value;                                     \
    if(this->m##name != temp) {                     \
        this->m##name = temp;                       \
    }                                               \
}                                                   \
type BGISize::get##name() const {                   \
    return this->m##name;                           \
}
ACCESS_METHOD(short,    Width)
ACCESS_METHOD(short,    Height)
#undef ACCESS_METHOD
/********************** Drawing Pen Class ********************************/
BGIPen::BGIPen()
{
    this->penStyle  = BGI::BGIPenStyle::SOLID_LINE;
    this->penWidth = static_cast<int>(THICK_WIDTH);
    this->penColor =BGI::BGIColor::BLACK;
    setcolor(BGI::BGIColor::BLACK);
    setlinestyle(this->penStyle ,0,this->penWidth);
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

BGIPen::BGIPen(const BGI::BGIColor color, const int width, const BGI::BGIPenStyle style)
{
    //copy ctor
    this->penColor = color;
    this->penWidth = LIMIT(width);
    this->penStyle = style;
    setcolor(color);
    setlinestyle(this->penStyle ,0,this->penWidth);
}
void BGIPen::setStyle(BGI::BGIPenStyle style)
{
    /*
        BUG in graphics.h: the different line types are only visible for
        width size of 1 when width > 1 only solid-line are visible
        we default to a width of one when we need to set style
    */
    this->penStyle = style;
    setlinestyle(this->penStyle,0,1);
}
void BGIPen::setWidth(const int width)
{
    this->penWidth = LIMIT(width);
    //DEBUG << "New Width is: " << width << this->penWidth << std::endl;
    setlinestyle(this->penStyle,0,this->penWidth);
}
/*void BGIPen::setBrush(const BGIBrush brush)
{
    this->penBrush = brush;
    setfillstyle(brush,this->penColor);
}*/
void BGIPen::setColor(const BGI::BGIColor color)
{
     this->penColor = color;
     // update pen color only new color # to old color
     if(this->penColor != getcolor())
        setcolor(this->penColor);
}
BGI::BGIColor BGIPen::getPenColor() const
{
     if(this->penColor != getcolor()){
        DEBUG << "Internal and graphic system color differ!\n";
        // we cast the integer to a BGIColor enum since getcolor() return an int
        return static_cast<BGI::BGIColor>(getcolor());
     }
     else
        return this->penColor;
}
BGI::BGIPenStyle BGIPen::getStyle() const
{
   BGI::BGILineSettings styles;
   getlinesettings(&styles);
   if(this->penStyle != styles.linestyle){
     DEBUG << "Internal and graphic system linestyle differ!\n";
     // safe to cast statically since an enum is an int and vice versa
     return static_cast<BGI::BGIPenStyle>(styles.linestyle);
   }
   return this->penStyle;
}
// using int cause the fucntion to convert the return type to a character
//
int BGIPen::getPenWidth() const
 {
   BGI::BGILineSettings styles;
   getlinesettings(&styles);
   std::cout << styles.thickness << std::endl;
   if(this->penWidth != styles.thickness){
     DEBUG << "Internal and graphic system pen width differ!\n";
     return styles.thickness;
   }
   return this->penWidth;
 }
 /**************** Text Attributes class ****************/
BGIFont::BGIFont()
{
    /// SANS_SERIF_FONT and SMALL FONT dont work with VERTICAL ORIENTATION
    this->tFont = BGI::BGIFonts::DEFAULT_FONT;
    this->tDir = BGI::BGIDir::DIR_HORIZ;
    this->tAlign = BGI::BGIAlign::TEXT_CENTER;
    this->tSize = 1;
    settextstyle(this->tFont,this->tDir,this->tSize);
    settextjustify(this->tAlign,this->tAlign);
}

BGIFont::~BGIFont()
{
    //dtor
}
BGIFont::BGIFont(const BGI::BGIFonts font, const BGI::BGIDir Orientation, const BGI::BGIAlign textAlign, const int fontSize)
{
    this->tFont = font;
    this->tDir = Orientation;
    this->tAlign = textAlign;
    this->tSize = fontSize;
    settextstyle(this->tFont,this->tDir,this->tSize);
    if(this->tDir == BGI::DIR_HORIZ){
        if(textAlign == BGI::TEXT_TOP || textAlign == BGI::TEXT_BOTTOM){
           this->tAlign = BGI::TEXT_LEFT;
        }
    }
    else {
        if(textAlign == BGI::TEXT_LEFT || textAlign == BGI::TEXT_RIGHT){
            this->tAlign = BGI::TEXT_BOTTOM;
        }
        else{
           this->tAlign = ((textAlign == static_cast<BGI::BGIAlign>(3)) ? static_cast<BGI::BGIAlign>(0) :static_cast<BGI::BGIAlign>(2));
        }
    }
   settextjustify(this->tAlign,this->tAlign);
}
/********************************************************************/
void BGIFont::setFont(const BGI::BGIFonts font)
{
      this->tFont = font;
      settextstyle(this->tFont,this->tDir,this->tSize);
}
/********************************************************************/
void BGIFont::setFontSize(const int fontSize)
{
       this->tSize = fontSize;
       settextstyle(this->tFont,this->tDir,this->tSize);
}
/**********************************************************************/
void BGIFont::setOrientation(const BGI::BGIDir Orientation)
{
        this->tDir = Orientation;
        settextstyle(this->tFont,this->tDir,this->tSize);
}
/************************************************************************/
void BGIFont::setAlignment(const BGI::BGIAlign textAlign)
{
    this->tAlign = textAlign;
    settextjustify(textAlign,textAlign);
}
/** Getter methods****/
BGISize BGIFont::getFontMetrics(char *str)
{
    /**
    // All BGIFont object access and modify the same internal data as there are created
    // the last created determines the state of internal data: Therefore this method must be call
    // to get the font metrics for the selected font before another font object is created
    */
    this->fontMetrics.setWidth(textwidth(str));
    this->fontMetrics.setHeight(textheight(str));
    return this->fontMetrics;
}
