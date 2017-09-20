#ifndef BGIWIDGET_H
#define BGIWIDGET_H
#include <BGIConstant.h>
#include <pthread.h>
#include <atomic>
#include <map>
#include <vector>
#include <stdbool.h>
#include "BGIPoint.h"
#include "BGIPen.h"
#include "BGIPaintObject.h"
// include the correct header for getting system screen res
#ifdef _WIN32
    #include <winuser.h>
#elif __linux
    #include <X11/Xlib.h>
#else
#endif // _WIN32

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
        BGIPoint drawAreaSizes()const ;// use by subclass to scale their content
        BGIPoint* refDrawSizes();// use by subclass to scale their content
        void terminateGraph() const;
        void close(); // this use to stop the internal thread loop before deleted the object
        void pause() const;
        void getPaintObject(BGIPaintObject *pObject);
        void refresh() const;
    protected:

    private:
        pthread_t updateSizes();
        void initColorMap();
        bool isResized();
        static void* paintEngine(void *context);
        // we declare these as atomic to protect against concurrencies
        // we can also use mmutexes
        std::atomic<short int> width;
        std::atomic<short int> height;
        // hold the reference to the thread object
        bool minimized;
        bool maximized;
        pthread_t resizeEvent;
        pthread_mutex_t lock;
        BGIPoint *cleanupRef;
        std::map<std::string, colors> backColors;
        std::vector<BGIPaintObject*> objectsToPaint;
};

#endif // BGIWIDGET_H
