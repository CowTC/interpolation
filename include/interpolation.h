#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include <iostream>

class InterpolationMethods
{

    public:
        //constructor function
        InterpolationMethods(int *n_, float *coord, float *inter, int nDim, int type_= 1);

        //constructor function
        ~InterpolationMethods();

        //set input data
        int set_input(float *input);

        //calculation of coefficient        
        int extrpolation_coefficient();

        //interpolation
        int interpolation(float *coord, float *output);

    private:

        int nDim_;

        int type_;

        int *numDim_;

        float *minCoord_;

        float *disInter_;

        float **tab_d0;

        float **tab_d1;

        float **tab_d2;

        float *input_;

        //calculation of coeficients in value interpolation
        int extrpolation_coefficient_cbsi_0();

        //calculation of coeficients in 1st order interpolation
        int extrpolation_coefficient_cbsi_1();

        //calculation of coeficients in 2nd order interpolation
        int extrpolation_coefficient_cbsi_2();

        //original data interpolation
        int interpolation_cbsi_1D_0(float xCoord, float *output);

        //1st order interpolation
        int interpolation_cbsi_1D_1(float xCoord, float *output);

        //2nd order interpolation
        int interpolation_cbsi_1D_2(float xCoord, float *output);
};

#endif
