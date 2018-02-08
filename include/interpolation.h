#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include <iostream>

class InterpolationMethods
{

    public:
        InterpolationMethods(int *n_, float *coord, float *inter, int nDim, int type_= 1);

        ~InterpolationMethods();

    private:

        int nDim_;

        int type_;

        int *numDim_;

        float *minCoord_;

        float *disInter_;

        float **tab_d0;

        float **tab_d1;

        float **tab_d2;
};

#endif
