#ifndef TERM_H
#define TERM_H

#include "common.hpp"

class Term{

    private:
        int _sign;
        int _flag;
        char _base;
        float _coeff;
        float _exponent;

    public:
        ~Term();
        int getSign();
        Term(int sign);
        char getBase();
        float abs(float x);
        float getExponent();
        float getCoefficient();
        Term &operator+(const Term &rhs);
        Term &operator=(const Term &rhs);
        
        void setSign(int s);
        void setBase(char b);
        void toString(int f);
        void setExponent(float e);
        void setCoefficient(float f);
        void operator+=(const Term &rhs);

};

#endif