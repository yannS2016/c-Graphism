/**************************************************************************
// Copyright (C) 2017 Yann Stephen Mandza < mandza.y.s@gmail.com>
//                   - CPUT Bellville -
// This file is part of BGI c++ based graphics.It is the base class
// for c++ wrapper classes for BGI graphics library. it is the framework
// for all subsequent class inherits it.
***************************************************************************/

#include "BGIWidget.h"
#include <wtypes.h>
static const int BOTTOM_FRAME_WIDTH = 10;
static const int LEFT_FRAME_WIDTH = 9;
static const int DEFAULT_COLOR = colors::BLACK;
// screen limit sizes: these based on my PC screen sizes
static const int MINIMIZED_SIZE = -1;
static const int SCREEN_WIDTH_MARGIN = 1;
static const int SCREEN_HEIGHT_MARGIN = 62;

static  int INIT_WIDTH = 0;
static  int INIT_HEIGHT = 0;
static bool exitThread = false;

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
    INIT_WIDTH = this->width ;
    INIT_HEIGHT = this->height;
    // not initialising pointer and trying to test it is memory fault
    this->cleanupRef = NULL;
    // Initialising color table
}

BGIWidget::~BGIWidget()
{
/// Release the memory allocated to dependancy objets
    Sleep(0.05);
    if(cleanupRef != NULL){
        delete cleanupRef;
        cleanupRef = NULL;
        DEBUG << "Size object deleted\n";
    }
    // invalidated pointers so we dont left behind dangling ones
    int vSize = this->objectsToPaint.size();
    if(vSize  > 0) {
        for(int i  = 0 ; i < vSize; i++ ){
        // delete each PaintObject(release the memory allocated)
        delete this->objectsToPaint[i];
        }
       this->objectsToPaint.clear();
    }
    // clear the map
    this->backColors.clear();
    this->terminateGraph();
    DEBUG << "Widget internal memory was released!\n";
}

BGIWidget::BGIWidget(const char* widgetName, short int w , short int h)//:p()
{
    initwindow(w, h,widgetName);
    initColorMap();
    this->setBackGround("LightGray");
    this->isMinimized();
    // remove window bottom frame width
    this->height = h - BOTTOM_FRAME_WIDTH;
    // remove window left frame width
    this->width = w - LEFT_FRAME_WIDTH;
    this->cleanupRef = NULL;
    /// Store the initial widget sizes
    INIT_WIDTH = this->width ;
    INIT_HEIGHT = this->height;
    // block calling thread till completion
    pthread_join(this->updateSizes(),NULL);
    DEBUG << " : Running Copy constrcutor" << std::endl;
}
// start a resize event thread
pthread_t BGIWidget::updateSizes()
{
    short int thState;
    //resizeEvent = new std::thread(&BGIWidget::paintEngine, this);
    pthread_mutex_init(&lock, NULL);
    thState = pthread_create(&resizeEvent,NULL,paintEngine, this);
    if(thState){
        DEBUG << "Error: unable to create thread" << thState<< std::endl;
        exit(-1);
    }
    return thState;
}

void* BGIWidget::paintEngine(void *context)
{

    while(!exitThread)
    {
        short windW =  getmaxx();
        short windH =  getmaxy();
        ((BGIWidget *)context)->width = windW ;
        ((BGIWidget *)context)->height = windH;
        BGIPoint win(windW,windH);

        if(!((BGIWidget *)context)->isResized()){
            if(((BGIWidget *)context)->objectsToPaint.size()){
                for(BGIPaintObject* shape : ((BGIWidget *)context)->objectsToPaint ){
                    if(!shape->isObjDrawn()){
                        shape->draw();
                        //DEBUG << "Shape drawn: " << shape->getShapeID() << std::endl;
                        //DEBUG << "Container size: " << ((BGIWidget *)context)->objectsToPaint.size() << std::endl;
                    }
                }
            }
        }
        else {
            // here we will call redraw
            cleardevice();
            rectangle(0,0,win.getX(),win.getY());
            for(BGIPaintObject* shape : ((BGIWidget *)context)->objectsToPaint ){
                shape->redrawCircle(win.getX()/3);
            }
        }
    Sleep(0.025); // slow this thread so to free CPU time.
    }
    pthread_exit(NULL);
    DEBUG << "Thread was terminated!\n";
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
BGIPoint BGIWidget::drawAreaSizes()const
{
    //DEBUG << this->width << "  " << this->height << std::endl;
    return BGIPoint(this->width - LEFT_FRAME_WIDTH, this->height - BOTTOM_FRAME_WIDTH);
}
BGIPoint* BGIWidget::refDrawSizes()
{
    BGIPoint *refSize = new BGIPoint(this->width - LEFT_FRAME_WIDTH, this->height - BOTTOM_FRAME_WIDTH);
    this->cleanupRef = refSize; // track this pointer so we delete when the class goes out of scope
    return refSize;
}
/*** terminate the widgets*****/
void BGIWidget::terminateGraph() const
{
    closegraph();
}
void BGIWidget::pause() const
{
    while(!kbhit())
    {
        delay(50);
    }
}
void BGIWidget::getPaintObject(BGIPaintObject *pObject)
{
    // fill  in the list of object to paint;
    //pthread_mutex_lock(&this->lock);
    objectsToPaint.push_back(pObject);
    //pthread_mutex_unlock(&this->lock);
}
void BGIWidget::refresh() const
{
    cleardevice();
}
bool BGIWidget::isResized()
{
    if(this->width > INIT_WIDTH || this->height > INIT_HEIGHT){
        INIT_WIDTH = this->width;
        INIT_HEIGHT = this->height;
        return true;
    }
    else
        return false;
}
void BGIWidget::close()
{
    exitThread = true;
}

