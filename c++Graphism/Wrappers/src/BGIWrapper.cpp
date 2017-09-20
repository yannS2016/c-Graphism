/*****************************************************************
// Copyright (C) 2017 Yann Stephen Mandza < mandza.y.s@gmail.com>
//                   - CPUT Bellville
// This file is part of BGI c++ based graphics
// This class is the base class for c++ wrapper classes for BGI
// graphics library. it is the all subsequent class inherits it.
******************************************************************/
#include "BGIWrapper.h"
#define DEBUG std::cout << __FILE__ << " " <<__FUNCTION__ << " line " << __LINE__ << " "
BGIWidget::BGIWidget()
{
    // define default window size
    DEBUG << " Running Default constrcutor !!" << std::endl;
    const char* windName = __FUNCTION__;
    initwindow(400, 300,windName);
    initColorMap();
    this->setBackGround("LightGray");
    // drawing area
    this->width = 400 -  LEFT_FRAME_WIDTH;
    this->height = 300 - BOTTOM_FRAME_WIDTH;
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
    this->height = h - BOTTOM_FRAME_WIDTH;
    // remove window left frame width
    this->width = w - LEFT_FRAME_WIDTH;
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
     setbkcolor(foundIt?colorID:DEFAULT_COLOR);
     cleardevice();
     setbkcolor(foundIt?colorID:DEFAULT_COLOR);
}
bool BGIWidget::isMinimized()const
{
    if(this->getWidth() == MINIMIZED_SIZE || this->getHeight() == MINIMIZED_SIZE)
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
    if(width == (desktopX - SCREEN_WIDTH_MARGIN) || height == (desktopY - SCREEN_HEIGHT_MARGIN))
        return true;
    else
        return false;
}
BGISize BGIWidget::drawAreaSizes()const
{
    return BGISize(this->width - LEFT_FRAME_WIDTH, this->height - BOTTOM_FRAME_WIDTH);
}
BGISize* BGIWidget::refDrawSizes()
{
    BGISize *refSize = new BGISize(this->width - LEFT_FRAME_WIDTH, this->height - BOTTOM_FRAME_WIDTH);
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


