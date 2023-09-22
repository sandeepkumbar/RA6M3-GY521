#include "common_utils.h"

void R_BSP_WarmStart(bsp_warm_start_event_t event);
static uint8_t data[0x14]; // data buffer to receive
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

       while(I2C_MASTER_EVENT_RX_COMPLETE != g_master_event)
         {
           ; // Wait till master complete its reception
         }
          APP_PRINT("%d",data[0]); //104(0x68) will be returned by the sensor if everything goes well

     /* closing IIC master module */
     R_IIC_MASTER_Close (&g_i2c_master_ctrl);

     /*Check if slave responded correctly*/
     if(104==data[0]){

         /*Write 0x00 to PWR_MGMT_1_REG(0x6B) register to wake the sensor up*/
         R_IIC_MASTER_Open(&g_i2c_master_ctrl,&g_i2c_master_cfg);
         uint8_t read_buffer[0x02] = {0x6B,0x00};
         memcpy(data, read_buffer, 0x02);

         /*setting master event to reset value*/
         g_master_event = (i2c_master_event_t)RESET_VALUE;

         /*Write 0x00 to 0x6B register*/
         R_IIC_MASTER_Write(&g_i2c_master_ctrl, data,0x02, false);
         while(I2C_MASTER_EVENT_TX_COMPLETE != g_master_event)
         {
             ; // Wait till master complete transmit
         }
         R_IIC_MASTER_Close (&g_i2c_master_ctrl);

         /*Set DATA RATE of 1KHz by writing 0x07 to SMPLRT_DIV(0x19) register*/
         R_IIC_MASTER_Open(&g_i2c_master_ctrl,&g_i2c_master_cfg);
         uint8_t SMPLRT_DIV_REG[0x02] = {0x19,0x07};
         memcpy(data, SMPLRT_DIV_REG, 0x02);

         /*setting master event to reset value*/
         g_master_event = (i2c_master_event_t)RESET_VALUE;

         /*Write 0x07 to 0x19 register*/
         R_IIC_MASTER_Write(&g_i2c_master_ctrl, data,0x02, false);
         while(I2C_MASTER_EVENT_TX_COMPLETE != g_master_event)
         {
             ; // Wait till master complete transmit
         }
         R_IIC_MASTER_Close (&g_i2c_master_ctrl);


         /*Set accelerometer configuration in ACCEL_CONFIG Register(0x1C)
          * 0x00 to set full scale range of ±2g
          * 0x08 to set full scale range of ±4g
          * 0x10 to set full scale range of ±8g
          * 0x18 to set full scale range of ±16g*/
         R_IIC_MASTER_Open(&g_i2c_master_ctrl,&g_i2c_master_cfg);
         uint8_t ACCEL_CONFIG[0x02] = {0x1C,0x18};
         memcpy(data, ACCEL_CONFIG, 0x02);

         /*setting master event to reset value*/
         g_master_event = (i2c_master_event_t)RESET_VALUE;

         /*Write 0x18 to 0x1C register*/
         R_IIC_MASTER_Write(&g_i2c_master_ctrl, data,0x02, false);
         while(I2C_MASTER_EVENT_TX_COMPLETE != g_master_event)
         {
             ; // Wait till master complete transmit
         }
         R_IIC_MASTER_Close (&g_i2c_master_ctrl);

         /*Set Gyroscope configuration in GYRO_CONFIG Register(0x1B)
          * 0x00 to set full scale range of ± 250 °/s
          * 0x08 to set full scale range of ± 500 °/s
          * 0x10 to set full scale range of ± 1000 °/s
          * 0x18 to set full scale range of ± 2000 °/s */
         R_IIC_MASTER_Open(&g_i2c_master_ctrl,&g_i2c_master_cfg);
         uint8_t GYRO_CONFIG[0x02] = {0x1B,0x18};
         memcpy(data, GYRO_CONFIG, 0x02);

         /*setting master event to reset value*/
         g_master_event = (i2c_master_event_t)RESET_VALUE;

         /*Write 0x18 to 0x1B register*/
         R_IIC_MASTER_Write(&g_i2c_master_ctrl, data,0x02, false);
         while(I2C_MASTER_EVENT_TX_COMPLETE != g_master_event)
         {
             ; // Wait till master complete transmit
         }
         R_IIC_MASTER_Close (&g_i2c_master_ctrl);

         APP_PRINT("Configuration Completed");
     }
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
