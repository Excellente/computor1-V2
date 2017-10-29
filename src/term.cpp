#include "term.hpp"

Term::~Term(){}

float Term::abs(float x)
{
    if (x < 0)
        x *= -1;
    return (x);
}

int Term::getSign()
{
    return (_sign);
}

float Term::getCoefficient()
{
    return (_coeff);
}

float Term::getExponent()
{
    return (_exponent);
}

char Term::getBase()
{
    return (_base);
}

void Term::setSign(int s)
{
    _sign = s;
}

void Term::setBase(char s)
{
    _base = s;
}

void Term::setExponent(float e)
{
    _exponent = e;
}

void Term::setCoefficient(float f)
{
    _coeff = f;
}

Term::Term(int sign) : _sign(sign)
{
    _flag = 0;
    _base = 'x';
    _coeff = 0.0f;
    _exponent = 0.0f;
}

void Term::toString(int f)
{
    if (f == 0 && _sign == 0)
        cout << _coeff << " * " << _base << "^" << _exponent;
    else
    {
        if (_sign == 1)
            cout << " -";
        else
            cout << " +";
        cout << " " << _coeff << " * " << _base << "^" << _exponent;
    }
}


Term &Term::operator=(const Term &rhs)
{
    _sign = rhs._sign;
    _flag = rhs._flag;
    _base = rhs._base;
    _coeff = rhs._coeff;
    _exponent = rhs._exponent;
    return (*this);
}

void Term::operator+=(const Term &rhs)
{
    *this = *this + rhs;
}


Term &Term::operator+(const Term &rhs)
{
    if (_sign == rhs._sign)
    {
        _coeff += rhs._coeff;
        if (_coeff == 0)
            _sign = 0;
    }
    else
    {
        _coeff -= rhs._coeff;
        if (_coeff < 0)
        {
            _coeff = abs(_coeff);
            _sign = rhs._sign;
        }
    }
    return (*this);
}