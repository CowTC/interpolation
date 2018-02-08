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

int InterpolationMethods::set_input(float *input)
{
    input_= input;

    return 0;
}
int InterpolationMethods::extrpolation_coefficient_cbsi()
{
    if(1==type_)
        extrpolation_coefficient_cbsi_0();

    if(2==type_)
    {
        extrpolation_coefficient_cbsi_0();
        extrpolation_coefficient_cbsi_1();
    }

    if(3==type_)
    {
        extrpolation_coefficient_cbsi_0();
        extrpolation_coefficient_cbsi_1();
        extrpolation_coefficient_cbsi_2();
    }

    return 0;
}

//calculation of coeficients in value interpolation
int InterpolationMethods::extrpolation_coefficient_cbsi_0()
{
    int i;
    float x;

    for(i= 0; i< NTABLE ; i++)
    {    
        x= (float)i / (float)(NTABLE - 1);  

        tab_d0[i][3]= x*x*x / 6.0; 
        tab_d0[i][2]= -0.5 * x*x*x + 0.5 * x*x + 0.5 * x + 1.0 / 6.0; 
        tab_d0[i][1]= 0.5 * x*x*x - x*x + 2.0 / 3.0; 
        tab_d0[i][0]=  (- x*x*x + 3.0 * x*x - 3.0 * x + 1.0) / 6.0; 
    }    

    return 0;

}

//calculation of coeficients in 1st order interpolation
int InterpolationMethods::extrpolation_coefficient_cbsi_1()
{
    int i;
    float x;

    for(i= 0; i< NTABLE; i++)
    {
        x= (float)i / (float)(NTABLE- 1);

        tab_d1[i][3]= 0.5 * x*x;
        tab_d1[i][2]= -1.5 * x*x + x + 0.5;
        tab_d1[i][1]= 1.5 * x*x - 2.0 * x;
        tab_d1[i][0]=  -0.5 * x*x + x - 0.5;
    }

    return 0;

}

//calculation of coeficients in 2nd order interpolation
int InterpolationMethods::extrpolation_coefficient_cbsi_2()
{
    int i;
    float x;

    for(i= 0; i< NTABLE; i++)
    {
        x = (float)i / (float)(NTABLE - 1);

        tab_d2[i][3] = x;
        tab_d2[i][2] = -3.0 * x + 1.0;
        tab_d2[i][1] = 3.0 * x - 2.0;
        tab_d2[i][0] = - x + 1.0;
    }

    return 0;
}

//interpolation
int InterpolationMethods::interpolation(float xCoord, float *output)
{

    if(1==type_)
        interpolation_cbsi_1D_0(xCoord, output);

    if(2==type_)
        interpolation_cbsi_1D_1(xCoord, output);

    if(3==type_)
        interpolation_cbsi_1D_2(xCoord, output);
    
    return 0;
}

int InterpolationMethods::interpolation_cbsi_1D_0(float xCoord, float *output)
{
	int inx, jdx, i, itmp1;

	inx = (int) ((xCoord - minCoord_[0]) / disInter_[0]);
	jdx  = (int) (((xCoord - minCoord_[0]) / disInter_[0] - inx) * NTABLE);

	*output = 0;

	if (0 < inx && nDim_-2 > inx)
		for (i=0; i<4; i++)
			*output += input_[inx-1+i] * tab_d0[jdx][i];
	else
	{
		for (i=0; i<4; i++)
		{
			itmp1 = inx - 1 + i;
			if (0 > itmp1)
				itmp1 = 0;
			else if (nDim_-1 < itmp1)
				itmp1 = nDim_ - 1;

			*output += input_[itmp1] * tab_d0[jdx][i];
		}
	}

	return 0;
}

int InterpolationMethods::interpolation_cbsi_1D_1(float xCoord, float *output)
{
	int inx, jdx, i, itmp1;

	inx = (int) ((xCoord- minCoord_[0]) / disInter_[0]);
	jdx  = (int) (((xCoord- minCoord_[0]) / disInter_[0] - inx) * NTABLE);

	*output = 0;

	if (0 < inx && nDim_-2 > inx)
		for (i=0; i<4; i++)
			*output += output[inx-1-i] * tab_d1[jdx][i];
	else
	{
		for (i=0; i<4; i++)
		{
			itmp1 = inx - 1 + i;
			if (0 > itmp1)
				itmp1 = 0;
			else if (nDim_- 1 < itmp1)
				itmp1 = nDim_- 1;

			*output += output[itmp1] * tab_d1[jdx][i];
		}
	}

	*output /= disInter_[0];

	return 0;
}

int InterpolationMethods::interpolation_cbsi_1D_2 (float xCoord, float *output)
{
	int inx, jdx, i, itmp1;

	inx = (int) ((xCoord - minCoord_[0]) / disInter_[0]);
	jdx  = (int) (((xCoord - minCoord_[0]) / disInter_[0] - inx) * NTABLE);

	*output = 0;

	if (0 < inx && nDim_-2 > inx)
		for (i=0; i<4; i++)
			*output += output[inx-1-i] * tab_d2[jdx][i];
	else
	{
		for (i=0; i<4; i++)
		{
			itmp1 = inx - 1 + i;
			if (0 > itmp1)
				itmp1 = 0;
			else if (nDim_-1 < itmp1)
				itmp1 = nDim_ - 1;

			*output += output[itmp1] * tab_d2[jdx][i];
		}
	}

	*output /= disInter_[0] * disInter_[0];

	return 0;
}

#endif
