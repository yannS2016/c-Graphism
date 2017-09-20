#ifndef BGIRec_H
#define BGIRec_H
/*
The BGIRec class defines the size of a two-dimensional object using integer point
precision. A size is specified by a width() and a height(). It can be set in the
constructor and changed using the setWidth(), setHeight(), or scale() functions
This class actually manges the windows geometry that are using for internal graphics painting
*/

class BGIRec
{
    public:
        /** Default constructor */
        BGIRec();
        /** Default destructor */
        virtual ~BGIRec();
        /** Copy constructor
         *  \param other Object to copy from
         */
        BGIRec(const int mleft, const int mTop, const int mRight, const int mBottom);
        BGIRec(const BGIRec &otherSize);
        #define ACCESS_METHOD(type, name)      \
            void set##name(const type value);  \
            type get##name() const;
        ACCESS_METHOD(int,Left)
        ACCESS_METHOD(int,Top)
        ACCESS_METHOD(int,Right)
        ACCESS_METHOD(int,Bottom)
        #undef ACCESS_METHOD // make sure ACCESS_METHOD make sense only at compile time
        //Returns true if either of the width and height is less than or equal to 0; otherwise returns false
        bool isEmpty() const;
        //Returns true if both the width and height is equal to or greater than 0; otherwise returns false.
        bool isValid() const;
    protected:

    private:
        int rLeft;
        int rTop;
        int rRight;
        int rBottom;
};

#endif // BGIRec_H
