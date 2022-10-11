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
\brief Calculates maximum Lumen value for  X/Y color.

\param[in]
    valX - X value of the color
\param[in]
    valY - Y value of the color
	
\param[out]
    calcMaxL - Pointer to the calculated maximum Lumen value for X/Y color
******************************************************************************/
void maxL_FromXY(unsigned int valX, unsigned int valY, int *calcMaxL);
