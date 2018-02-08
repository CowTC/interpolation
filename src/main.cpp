#include "../include/interpolation.hpp"

int main()
{
    int num= 3;
    int *ndimen= new int[num];
    float *coord= new float[num];
    float *interval= new float[num];


    for(int i= 0; i< num; i++)
    {
        ndimen[i]= i;
        coord[i]= i* 0.0;
        interval[i]= i*1.0;
    }

    InterpolationMethods interTest(ndimen, coord, interval, num);

    return 1;
}
