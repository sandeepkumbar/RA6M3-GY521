#include "common_utils.h"

void R_BSP_WarmStart(bsp_warm_start_event_t event);
static uint8_t data[0x1]; // data buffer to receive
#define BUF_LEN (0x02) // buffer length to write

static volatile i2c_master_event_t g_master_event = (i2c_master_event_t)RESET_VALUE; //event for call back

void hal_entry(void)

{
    /* opening IIC master module */
    R_IIC_MASTER_Open(&g_i2c_master_ctrl,&g_i2c_master_cfg);
    uint8_t verify=0x75; //Register to read the GY-521 address

     /*setting master event to reset value*/
     g_master_event = (i2c_master_event_t)RESET_VALUE;

     /*Write 0x75 to GY-521*/
     R_IIC_MASTER_Write(&g_i2c_master_ctrl, &verify,0x01, false);

     while((I2C_MASTER_EVENT_TX_COMPLETE != g_master_event))
        {
          ; // Wait till master complete transmit
        }
     /*Read from GY-521*/
     R_IIC_MASTER_Read(&g_i2c_master_ctrl, data, 0x01, false);

       while((I2C_MASTER_EVENT_RX_COMPLETE != g_master_event) )
         {
           ; // Wait till master complete its reception
         }
          APP_PRINT("%d",data[0]); //104(0x68) will be returned by the sensor if everything goes well

     /* closing IIC master module */
     R_IIC_MASTER_Close (&g_i2c_master_ctrl);
}

/*I2C Master Callback function*/
void i2c_master_callback(i2c_master_callback_args_t * p_args)//uy
{
    if (NULL != p_args)
    {
        g_master_event = p_args->event;
    }
}

/*******************************************************************************************************************//**
 * This function is called at various points during the startup process.  This implementation uses the event that is
 * called right before main() to set up the pins.
 *
 * @param[in]  event    Where at in the start up process the code is currently at
 **********************************************************************************************************************/

void R_BSP_WarmStart(bsp_warm_start_event_t event)
{
    if (BSP_WARM_START_POST_C == event)
    {
        /* C runtime environment and system clocks are setup. */

        /* Configure pins. */
        R_IOPORT_Open (&g_ioport_ctrl, &g_bsp_pin_cfg);
    }
}


/*******************************************************************************************************************//**
 * @} (end addtogroup r_iic_slave_ep)
 **********************************************************************************************************************/
