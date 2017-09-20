#ifndef BGIPOINT_H
#define BGIPOINT_H


class BGIPoint
{
public:
        /** Default constructor */
        BGIPoint();
        /** Default destructor */
        virtual ~BGIPoint();
        /** Copy constructor
         *  \param other Object to copy from
         */
        BGIPoint(const short x, const short y);

        BGIPoint(const BGIPoint &otherSize);
        #define ACCESS_METHOD(type, name)      \
            void set##name(const type value);  \
            type get##name() const;
        ACCESS_METHOD(short,X)
        ACCESS_METHOD(short,Y)
        #undef ACCESS_METHOD // make sure ACCESS_METHOD make sense only at compile time
        //Returns true if either of the width and height is less than or equal to 0; otherwise returns false
        bool isEmpty() const;
        //Returns true if both the width and height is equal to or greater than 0; otherwise returns false.
        bool isValid() const;
    protected:

    private:
        short int mX;
        short int mY;
};

#endif // BGIPOINT_H
