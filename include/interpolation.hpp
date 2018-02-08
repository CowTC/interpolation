#ifndef INTERPOLATION_IMPL_H
#define INTERPOLATION_IMPL_H

#include "./interpolation.h"

#define NTABLE 121

InterpolationMethods::InterpolationMethods(int *n_, float *coord, float *inter, int nDim, int type)
{
    //allocate memory
    numDim_= new int[nDim];
    minCoord_= new float[nDim];
    disInter_= new float[nDim];

    nDim_= nDim;
    type_= type;

    for(int i= 0; i< nDim; i++)
    {
        //dimension
        numDim_[i]= n_[i];

        //minimum coordinate
        minCoord_[i]= coord[i];

        //coordinate interval
        disInter_[i]= inter[i];
        
    }
    
    //allocate memory coefficients
    int i= 1;    
    while(i<= type_)
    {
        if(1==i)
        {
            tab_d0= new float*[NTABLE];
            for(int j= 0; j< NTABLE; j++)
                tab_d0[j]= new float[4];
        }

        if(2==i)
        {
            tab_d1= new float*[NTABLE];
            for(int j= 0; j< NTABLE; j++)
                tab_d1[j]= new float[4];
        }

        if(3==i)
        {
            tab_d2= new float*[NTABLE];
            for(int j= 0; j< NTABLE; j++)
                tab_d2[j]= new float[4];
        }
        
        i++;
    }
}

InterpolationMethods::~InterpolationMethods()
{
    //delete memory
    //1D memory
    delete []numDim_;
    numDim_= NULL;

    delete []minCoord_;
    minCoord_= NULL;

    delete []disInter_;
    disInter_= NULL;

    //2D memory
    int i= 1;    
    while(i<= type_)
    {
        if(1==i)
        {
            for(int j= 0; j< NTABLE; j++) 
            {
                delete []tab_d0[j];
                tab_d0[j]= NULL;
            }
            delete []tab_d0;
            tab_d0= NULL;
        }

        if(2==i)
        {
            for(int j= 0; j< NTABLE; j++) 
            {
                delete []tab_d1[j];
                tab_d1[j]= NULL;
            }
            delete []tab_d1;
            tab_d1= NULL;
        }

        if(3==i)
        {
            for(int j= 0; j< NTABLE; j++) 
            {
                delete []tab_d2[j];
                tab_d2[j]= NULL;
            }
            delete []tab_d2;
            tab_d2= NULL;
        }

        i++;
    }
}
#endif
