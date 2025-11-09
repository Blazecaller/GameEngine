#ifndef VECTOR2D_H
#define VECTOR2D_H
#include <iostream>

class Vector2D
{
    public:
        float X, Y;
        Vector2D(float x=0, float y=0): X(x), Y(y){}
        //add
        inline Vector2D operator +(const Vector2D &v2) const{
            return Vector2D(X + v2.X, Y + v2.Y);
        }
        //diff
        inline Vector2D operator -(const Vector2D &v2) const{
            return Vector2D(X - v2.X, Y - v2.Y);
        }

        //mul
        inline Vector2D operator *(const float scaler) const{
            return Vector2D(X*scaler, Y*scaler);
        }

        void Log(std::string msg = ""){
            std::cout << msg << "(X Y) = {" << X <<", " << Y << "}" << std::endl;
        }
};

#endif // VECTOR2D_H
