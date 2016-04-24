//  LSM303DLHC.h
//  LSM303DLHC
//
//  Created by Michael Brookes on 25/10/2015.
//  Copyright © 2015 Michael Brookes. All rights reserved.
//

#ifndef SRC_LSM303DLHC_H_
#define SRC_LSM303DLHC_H_

#include "./lib/I2C/I2CDevice.h"
/*
 * REGISTER ADDRESSES
 */
//From Table 17. of the LSM303 Data sheet ( https://www.adafruit.com/datasheets/LSM303DLHC.PDF )
#define ACCEL_ADDRESS               0x19    //!< I2C Address of the accelerometer device.
#define CTRL_REG1_A                 0x20    //!< Read/Write (power control) : Default - 00111
#define CTRL_REG2_A                 0x21    //!< Read/Write (filter selection) : Default - 0
#define CTRL_REG3_A                 0x22    //!< Read/Write (interrupt settings) : Default - 0
#define CTRL_REG4_A                 0x23    //!< Read/Write (range/resolution settings) : Default - 0
#define CTRL_REG5_A                 0x24    //!< Read/Write (FIFO setting | internal memory) : Default - 0
#define CTRL_REG6_A                 0x25    //!< Read/Write (CLICK interrupt setting) : Default - 0
#define REFERENCE_A                 0x26    //!< Read/Write (Reference value for interrupt generation) : Default - 0
#define STATUS_REG_A                0x27    //!< Read Only  (Overrun trigger) : Default - 0
#define OUT_X_L_A                   0x28    //!< Read Only  (X-axis acceleration data. The value is expressed in 2’s complement)
#define OUT_X_H_A                   0x29    //!< Read Only  (X-axis acceleration data. The value is expressed in 2’s complement)
#define OUT_Y_L_A                   0x2A    //!< Read Only  (Y-axis acceleration data. The value is expressed in 2’s complement)
#define OUT_Y_H_A                   0x2B    //!< Read Only  (Y-axis acceleration data. The value is expressed in 2’s complement)
#define OUT_Z_L_A                   0x2C    //!< Read Only  (Z-axis acceleration data. The value is expressed in 2’s complement)
#define OUT_Z_H_A                   0x2D    //!< Read Only  (Z-axis acceleration data. The value is expressed in 2’s complement)
#define FIFO_CTRL_REG_A             0x2E    //!< Read/Write (FIFO mode selection) : Default - 0
#define FIFO_SRC_REG_A              0x2F    //!< Read Only  (FIFO register)
#define INT1_CFG_A                  0x30    //!< Read/Write (interrupt 1 settings)
#define INT1_SOURCE_A               0x31    //!< Read Only  (interrupt 1 settings)
#define INT1_THS_A                  0x32    //!< Read/Write (interrupt 1 settings)
#define INT1_DURATION_A             0x33    //!< Read/Write (interrupt 1 settings)
#define INT2_CFG_A                  0x34    //!< Read/Write (interrupt 2 settings)
#define INT2_SOURCE_A               0x35    //!< Read 		(interrupt 2 settings)
#define INT2_THS_A                  0x36    //!< Read/Write (interrupt 2 settings)
#define INT2_DURATION_A             0x37    //!< Read/Write (interrupt 2 settings)
#define CLICK_CFG_A                 0x38    //!< Read/Write (interrupt double CLICK on Z axis) : Default - 0
#define CLICK_SRC_A                 0x39    //!< Read/Write (interrupt double CLICK settings)
#define CLICK_THS_A                 0x3A    //!< Read/Write (interrupt double CLICK settings)
#define TIME_LIMIT_A                0x3B    //!< Read/Write (interrupt double CLICK settings)
#define TIME_LATENCY_A              0x3C    //!< Read/Write (interrupt double CLICK settings)
#define TIME_WINDOW_A               0x3D    //!< Read/Write (interrupt double CLICK settings)

#define MAG_ADDRESS                 0x1E    //!< I2C Address of the magnetometer device.
#define CRA_REG_M                   0x00    //!< Read/Write (0x94 or 10010100 Temp sensor on and 30 hz refresh rate.)
#define CRB_REG_M                   0x01    //!< Read/Write
#define MR_REG_M                    0x02    //!< Read/Write (0x00 or 00000000 Continuous conversion mode.)
#define OUT_X_H_M                   0x03    //!< Read Only  (X-axis magnetometer data. The value is expressed in 2’s complement)
#define OUT_X_L_M                   0x04    //!< Read Only  (X-axis magnetometer data. The value is expressed in 2’s complement)
#define OUT_Z_H_M                   0x05    //!< Read Only  (Z-axis magnetometer data. The value is expressed in 2’s complement)
#define OUT_Z_L_M                   0x06    //!< Read Only  (Z-axis magnetometer data. The value is expressed in 2’s complement)
#define OUT_Y_H_M                   0x07    //!< Read Only  (Y-axis magnetometer data. The value is expressed in 2’s complement)
#define OUT_Y_L_M                   0x08    //!< Read Only  (Y-axis magnetometer data. The value is expressed in 2’s complement)
#define SR_REG_Mg                   0x09    //!< Read Only
#define IRA_REG_M                   0x0A    //!< Read Only
#define IRB_REG_M                   0x0B    //!< Read Only
#define IRC_REG_M                   0x0C    //!< Read Only
#define TEMP_OUT_H_M                0x31    //!< Read Only  (Temp sensor data. The value is expressed in 2’s complement)
#define TEMP_OUT_L_M                0x32    //!< Read Only  (Temp sensor data. The value is expressed in 2’s complement)
/*
 * END OF REGISTER ADDRESSES
 */

/*
 * POWER SETTINGS - REGISTER TO WRITE TO : CTRL_REG1_A 0x20
 */
#define POWER_DEFAULT               0x07
#define POWER_DOWN                  0x00

#define 1HZ                         0x17
#define 10HZ                        0x27
#define 25HZ                        0x37
#define 50HZ                        0x47
#define 100HZ                       0x57
#define 200HZ                       0x67
#define 400HZ                       0x77
#define 1344KHZ                     0x97

#define 1HZ_LOW_POWER               0x1F
#define 10HZ_LOW_POWER              0x2F
#define 25HZ_LOW_POWER              0x3F
#define 50HZ_LOW_POWER              0x4F
#define 100HZ_LOW_POWER             0x5F
#define 200HZ_LOW_POWER             0x6F
#define 400HZ_LOW_POWER             0x7F
#define 1620KHZ_LOW_POWER           0x8F
#define 5.376KHZ_LOW_POWER          0x9F
/*
 * END OF POWER SETTINGS
 */

/*
 * HIGH PASS FILTER SETTINGS - REGISTER : CTRL_REG2_A 0x21
 */
#define CTRL_REG2_A_DEFAULT         0x00
#define HIGHPASS_NORMAL_RESET       0x00
#define HIGHPASS_REF_SIGNAL         0x40
#define HIGHPASS_NORMAL             0xC0
#define HIGHPASS_AUTO_RESET         0x80
// W/ FILTERED DATA SELECTION
#define HIGHPASS_NORMAL_RESET_FDS   0x08
#define HIGHPASS_REF_SIGNAL_FDS     0x48
#define HIGHPASS_NORMAL_FDS         0xC8
#define HIGHPASS_AUTO_RESET_FDS     0x88
/*
 * END OF HIGH PASS FILTER SETTINGS
 */

/*
 * INTERRUPT SETTINGS - REGISTER : CTRL_REG3_A 0x22
 */
#define CTRL_REG3_A_DEF             0x00
#define INT1_CLICK_ENABLED_ONLY     0x80
#define INT1_AOI1_ENABLED_ONLY      0x40
#define INT1_AOI2_ENABLED_ONLY      0x20
#define INT1_DRDY1_ENABLED_ONLY     0x10
#define INT1_DRDY2_ENABLED_ONLY     0x08
#define INT1_WTM_ENABLED_ONLY       0x04
#define INT1_OVERRUN_ENABLED_ONLY   0x02
/*
 * END OF INTERRUPT SETTINGS
 */

/*
 * RESOLUTION AND SCALE SETTINGS - REGISTER : CTRL_REG4_A 0x23
 */
#define CTRL_REG4_A_DEFAULT         0x00
#define HI_RES_2G_SCALE             0x08
#define HI_RES_4G_SCALE             0x18
#define HI_RES_8G_SCALE             0x28
#define HI_RES_16G_SCALE            0x38

#define LOW_RES_2G_SCALE            0x00
#define LOW_RES_4G_SCALE            0x10
#define LOW_RES_8G_SCALE            0x20
#define LOW_RES_16G_SCALE           0x30
/*
 * END OF RESOLUTION AND SCALE SETTINGS
 */

/*
 * REGISTER : CTRL_REG5_A 0x24
 */
#define CTRL_REG5_A_DEFAULT         0x00
/*
 * END OF REGISTER
 */

/*
 * REGISTER : CTRL_REG6_A 0x25
 */
#define CTRL_REG6_A_DEFAULT         0x00
#define PAD2_CLICK_ENABLED_ONLY     0x80
#define PAD2_INT1_ENABLED_ONLY      0x40
#define PAD2_INT2_ENABLED_ONLY      0x20
#define PAD2_PERFORM_MEM_REBOOT     0x10
#define PAD2_FUNCTION_ENABLED       0x08
#define PAD2_INTERRUPT_ACTIVE_HIGH  0x02
/*
 * END OF REGISTER
 */

/*
 * REGISTER : FIFO_CTRL_REG_A 0x2E
 */
#define FIFO_CTRL_REG_A_DEFAULT     0x00
#define BYPASS_MODE_LINKED_TO_INT1  0x00
#define FIFO_MODE_LINKED_TO_INT1    0x40
#define STREAM_MODE_LINKED_TO_INT1  0x80
#define TRIGGER_MODE_LINKED_TO_INT1 0xC0
#define BYPASS_MODE_LINKED_TO_INT2  0x20
#define FIFO_MODE_LINKED_TO_INT2    0x60
#define STREAM_MODE_LINKED_TO_INT2  0xA0
#define TRIGGER_MODE_LINKED_TO_INT2 0xE0
/*
 * END OF REGISTER
 */

/*
* REGISTER INT1_CFG_A 0x30
*/
#define INT1_CFG_A_DEFAULT          0x00
/*
 * END OF REGISTER
 */

/*
 * INT1_THS_A 0x32
 */
#define INT1_THS_A_DEFAULT          0x00
/*
 * END OF INT1_THS_A
 */

/*
 *INT1_DURATION_A 0x33
 */
#define INT1_DURATION_A_DEFAULT     0x00
/*
 * END OF INT1_DURATION_A
 */

/*
* REGISTER INT2_CFG_A 0x34
*/
#define INT2_CFG_A_DEFAULT          0x00
/*
 * END OF INT2_CFG_A
 */

/*
 * INT2_THS_A 0x36
 */
#define INT2_THS_A_DEFAULT          0x00
/*
 * END OF INT2_THS_A
 */

/*
 *INT2_DURATION_A 0x37
 */
#define INT2_DURATION_A_DEFAULT     0x00
/*
 * END OF INT2_DURATION_A
 */

/*
 * CLICK_CFG_A 0x38
 */
#define CLICK_CFG_A_DEFAULT         0x00
#define DOUBLECLICK_CFG_Z_AXIS_ONLY 0x40
#define DOUBLECLICK_CFG_X_AXIS_ONLY 0x02
#define DOUBLECLICK_CFG_Y_AXIS_ONLY 0x08
#define SINGLECLICK_CFG_Z_AXIS_ONLY 0x10
#define SINGLECLICK_CFG_X_AXIS_ONLY 0x01
#define SINGLECLICK_CFG_Y_AXIS_ONLY 0x04
#define ENABLE_ALL_CFG              0x3F
/*
 * END OF CLICK_CFG_A
 */

/*
 * CLICK_SRC_A 0x39
 */
#define CLICK_SRC_A_DEFAULT
/*
 * END OF CLICK_SRC_A
 */

/*
 * CLICK_THS_A 0x3A
 */
#define CLICK_THS_A_DEFAULT
/*
 * END OF CLICK_THS_A
 */

/*
 * TIME_LIMIT_A 0x3B
 */
#define TIME_LIMIT_A_DEFAULT
/*
 * END OF TIME_LIMIT_A
 */

/*
 * TIME_LATENCY_A 0x3C
 */
#define TIME_LATENCY_A_DEFAULT
/*
 * END OF TIME_LATENCY_A
 */

/*
 * TIME_WINDOW_A 0x3D
 */
#define TIME_WINDOW_A_DEFAULT
/*
 * END OF TIME_WINDOW_A
 */

/*
 * CRA_REG_M 0x00
 */
#define CRA_REG_M_DEFAULT
/*
 * END OF CRA_REG_M
 */

/*
 * CRB_REG_M 0x01
 */
#define CRB_REG_M_DEFAULT
/*
 * END OF CRB_REG_M
 */

/*
 * MR_REG_M 0x02
 */
#define MR_REG_M_DEFAULT
/*
 * END OF MR_REG_M
 */

/**
 \brief LSM303DLHC : A class that provides control of the LSM303DLHC which contains : accelerometer, magnetometer, temp and gyro.
 \version   2.3
 \date      Oct-2015
 \copyright GNU Public License.
 */
class LSM303DLHC : public I2C::I2CDevice {

public:

    /**
     \brief LSM303DLHC : A class that provides control of the LSM303DLHC's accelerometer, magnetometer, temp and gyro.
     */
    LSM303DLHC( );

protected:

    virtual void SetDeviceAddress( int _DeviceAddress ) = 0;

    virtual void SetBusId( int _BusId ) = 0;
    
};

#endif /* SRC_LSM303DLHC_H_ */
