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
\brief Converts Hue/Saturation values of the color to corresponding X/Y values

\param[in]
    hue - Hue value of the color
\param[in]
    sat - Saturation value of the color
	
\param[out]
    calcX - Pointer to the calculated X value of the color
\param[out]
    calcY - Pointer to the calculated Y value of the color
******************************************************************************/
void HS2XY(int hue, int sat, unsigned int *calcX, unsigned int *calcY);
