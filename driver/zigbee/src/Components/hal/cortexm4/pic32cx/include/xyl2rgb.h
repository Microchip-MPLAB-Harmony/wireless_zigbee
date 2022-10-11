/*********************************************************************************************//**
\file

\brief

\author
    Microchip Corporation: http://ww.microchip.com \n
    Support email: support@microchip.com

  Copyright (c) 2008-2015, Microchip Corporation. All rights reserved.
  Licensed under Microchip's Limited License Agreement.

\internal
***************************************************************************************************/
/**************************************************************************//**
\brief Converts X/Y/L values of the color to corresponding R/G/B values

\param[in]
    valX - X value of the color
\param[in]
    valY - Y value of the color
\param[in]
	valL - level value of the color
\param[in]
	maxL - maximum Lumen value of the X/Y color	
	
\param[out]
    calcR - Pointer to the calculated R (red) value of the color
\param[out]
    calcG - Pointer to the calculated G (green) value of the color
\param[out]
    calcB - Pointer to the calculated B (blue) value of the color
******************************************************************************/
void XYL2RGB(unsigned int valX, unsigned int valY, int valL, int maxL, unsigned int *calcR, unsigned int *calcG, unsigned int *calcB);

