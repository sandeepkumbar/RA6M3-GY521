#include "common_utils.h"

void R_BSP_WarmStart(bsp_warm_start_event_t event);
static uint8_t data[0x14]; // data buffer to receive


static volatile i2c_master_event_t g_master_event = (i2c_master_event_t)RESET_VALUE; //event for call back

void hal_entry(void)

{
    /*Declare variables to store raw data from GY-521*/
    float Ax, Ay, Az, Gx, Gy, Gz, tmp;

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
         uint8_t PWR_MGMT_1_REG[0x02] = {0x6B,0x00};
         memcpy(data, PWR_MGMT_1_REG, 0x02);

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

         /* Read 14 BYTES of data starting from ACCEL_XOUT_H(0x3B) register
            6 registers(0x3B-0x40) are Accelerometer, 2 registers(0x41-0x43) are Temperature registers, 6 registers(0x44-0x48) are Gyroscope*/
         R_IIC_MASTER_Open(&g_i2c_master_ctrl,&g_i2c_master_cfg);
         uint8_t read_buffer_start_reg= 0x3B;
         g_master_event = (i2c_master_event_t)RESET_VALUE;
         while(1){

            /*Write ACCEL_XOUT_H(0x3B) register to read*/
            R_IIC_MASTER_Write(&g_i2c_master_ctrl, &read_buffer_start_reg,0x01, false);
            while(I2C_MASTER_EVENT_TX_COMPLETE != g_master_event)
            {
                ; // Wait till master complete transmit
            }
            /*Read ACCEL_XOUT_H(0x3B) register (14 bytes)*/
            R_IIC_MASTER_Read(&g_i2c_master_ctrl, data, 0x014, false);
            while(I2C_MASTER_EVENT_TX_COMPLETE != g_master_event)
            {
                ; // Wait till master complete transmit
            }

              /*Read the Accelerometer registers*/
               int16_t accelerometer_x = (int16_t)((data[0] << 8) | data[1]);
               int16_t accelerometer_y = (int16_t)((data[2] << 8) | data[3]);
               int16_t accelerometer_z = (int16_t)((data[4] << 8) | data[5]);

               /*Read the Temperature registers*/
               int16_t temperature_raw = (int16_t)((data[6] << 8) | data[7]);

               /* Read the Gyroscope registers*/
               int16_t gyroscope_x = (int16_t)((data[8] << 8) | data[9]);
               int16_t gyroscope_y = (int16_t)((data[10] << 8) | data[11]);
               int16_t gyroscope_z = (int16_t)((data[12] << 8) | data[13]);

               /* Formula to convert raw data to physical value for accelerometer
                * For ±2g divider is 16384.0
                * For ±4g divider is 8192.0
                * For ±8g divider is 4096.0
                * For ±16g divider is 2048.0
                * */
               Ax = accelerometer_x/2048.0;
               Ay = accelerometer_y/2048.0;
               Az = accelerometer_z/2048.0;

               /* Formula to convert raw data to physical value for Gyroscope */
               tmp=temperature_raw/340.00+36.53;

               /* Formula to convert raw data to physical value for Temperature
                * For 250 °/s divider is 131
                * For 500 °/s divider is 65.5
                * For 1000 °/s divider is 32.8
                * For 2000 °/s divider is 16.4
                *  */
               Gx = gyroscope_x/16.4;
               Gy = gyroscope_y/16.4;
               Gz = gyroscope_z/16.4;


               /*Conversion of float to string*/
               char AccX[10];
               snprintf(AccX, sizeof(AccX), "%.3f", Ax);
               char AccY[10];
               snprintf(AccY, sizeof(AccY), "%.3f", Ay);
               char AccZ[10];
               snprintf(AccZ, sizeof(AccZ), "%.3f", Az);

               char GyroX[10];
               snprintf(GyroX, sizeof(GyroX), "%.3f", Gx);
               char GyroY[10];
               snprintf(GyroY, sizeof(GyroY), "%.3f", Gy);
               char GyroZ[10];
               snprintf(GyroZ, sizeof(GyroZ), "%.3f", Gz);

               char Temp[10];
               snprintf(Temp, sizeof(Temp), "%.3f", tmp);


              // Print the Accelerometer values
              APP_PRINT("Accel x: %s \n",AccX);
              APP_PRINT("Accel y: %s \n",AccY);
              APP_PRINT("Accel z: %s \n",AccZ);

              // Print the Gyroscope values
               APP_PRINT("Gyro x: %s \n",GyroX);
               APP_PRINT("Gyro y: %s \n",GyroY);
               APP_PRINT("Gyro z: %s \n",GyroZ);


              // Print the Temperature values
               APP_PRINT("Temperature z: %s \n",Temp);
         }

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
