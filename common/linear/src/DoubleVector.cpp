// DoubleVector.cpp

#include "DoubleVector.h"

namespace linear
{
    void DoubleVector::Reset()
    {
        fill(begin(), end(), 0);
    }

    double DoubleVector::Norm2() const
    {
        double result = 0.0;
        for(double element : *this)
        {
            result += element * element;
        }
        return result;
    }

    void DoubleVector::AddTo(double* p_other, double scalar) const
    {
        for(uint i = 0; i<Size(); ++i)
        {
            p_other[i] += scalar * (*this)[i];
        }
    }

    void DoubleVector::Scale(double s)
    {
        for (uint i = 0; i<Size(); ++i)
        {
            (*this)[i] *= s;
        }
    }

    double DoubleVector::Dot(const double* p_other) const
    {
        double result = 0.0;
        for(uint i = 0; i<Size(); ++i)
        {
            result += (*this)[i] * p_other[i];
        }
        
        return result;
    }

    void DoubleVector::Print(ostream & os) const
    {
        for (double x : *this)
        {
            os << x << '\t';
        }
    }

    uint DoubleVector::Size() const
    {
        return vector<double>::size();
    }
}