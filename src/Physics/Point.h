#ifndef POINT_H
#define POINT_H
#include <iostream>

class Point{
    public:
        float X, Y;
        Point(float x=0, float y=0): X(x), Y(y){}
        //add
        inline Point operator +(const Point &p2) const{
            return Point(X + p2.X, Y + p2.Y);
        }
        //add +=
        inline friend Point operator +=(Point &p1, const Point &p2){
            p1.X += p2.X;
            p1.Y += p2.Y;
            return p1;
        }
        //subtraction
        inline Point operator -(const Point &p2) const{
            return Point(X - p2.X, Y - p2.Y);
        }

        //subtraction-=
        inline friend Point operator -=(Point &p1, const Point &p2){
            p1.X -= p2.X;
            p1.Y -= p2.Y;
            return p1;
        }
        //mul
        inline Point operator *(const float scaler) const{
            return Point(X*scaler, Y*scaler);
        }

        void Log(std::string msg = ""){
            std::cout << msg << "P(X Y) = {" << X <<", " << Y << "}" << std::endl;
        }
};

#endif // POINT_H
