/*******************************************************************************
 * (c) Copyright 2009-2018 Microsemi SoC Products Group.  All rights reserved.
 * 
 * CoreI2C driver interrupt control.
 * 
 * SVN $Revision: 9749 $
 * SVN $Date: 2018-02-12 18:26:37 +0530 (Mon, 12 Feb 2018) $
 */
#include "../../hal/hal.h"
#include "../../hal/hal_assert.h"
#include "core_i2c.h"
#include "../../CMSIS/m2sxxx.h"

extern i2c_instance_t  g_core_i2c0;
/*------------------------------------------------------------------------------
 * This function must be modified to enable interrupts generated from the
 * CoreI2C instance identified as parameter.
 */
void I2C_enable_irq( i2c_instance_t * this_i2c )
{
//    I2C_isr(this_i2c);
    // HAL_ASSERT(0)
   if(this_i2c == &g_core_i2c0)
   {
	   NVIC_EnableIRQ( FabricIrq0_IRQn );
   }
}

/*------------------------------------------------------------------------------
 * This function must be modified to disable interrupts generated from the
 * CoreI2C instance identified as parameter.
 */
void I2C_disable_irq( i2c_instance_t * this_i2c )
{
//    I2C_isr(this_i2c);
    // HAL_ASSERT(0)
   if(this_i2c == &g_core_i2c0)
   {
	   NVIC_DisableIRQ( FabricIrq0_IRQn );
   }
}
