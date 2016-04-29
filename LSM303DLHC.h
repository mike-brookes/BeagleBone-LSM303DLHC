//  LSM303DLHC.h
//  BBBLSM303DLHC
//
//  Created by Michael Brookes on 25/10/2015.
//  Copyright © 2015 Michael Brookes. All rights reserved.
//

#ifndef SRC_LSM303DLHC_H_
#define SRC_LSM303DLHC_H_

#include "Lib/I2C/I2CDevice.h"
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

#define REGISTER_ZERO               0b00000000

/*
 * POWER SETTINGS - REGISTER TO WRITE TO : CTRL_REG1_A 0x20
 */
#define POWER_OFF                   REGISTER_ZERO
#define DATA_RATE_1HZ               0b00010000
#define DATA_RATE_10HZ              0b00100000
#define DATA_RATE_25HZ              0b00110000
#define DATA_RATE_50HZ              0b01000000
#define DATA_RATE_100HZ             0b01010000
#define DATA_RATE_200HZ             0b01100000
#define DATA_RATE_400HZ             0b01110000
#define DATA_RATE_1344KHZ           0b10010000
#define LOW_POWER_DISABLED          REGISTER_ZERO
#define LOW_POWER_ENABLED           0b00001000
#define Z_AXIS_DISABLED             REGISTER_ZERO
#define Z_AXIS_ENABLED              0b00000100
#define Y_AXIS_DISABLED             REGISTER_ZERO
#define Y_AXIS_ENABLED              0b00000010
#define X_AXIS_DISABLED             REGISTER_ZERO
#define X_AXIS_ENABLED              0b00000001

#define CTRL_REG1_A_SETTINGS( DATA_RATE, LOW_POWER_MODE, Z_AXIS, Y_AXIS, X_AXIS ) DATA_RATE | LOW_POWER_MODE | Z_AXIS | Y_AXIS | X_AXIS
/*
 * END OF POWER SETTINGS
 */

/*
 * HIGH PASS FILTER SETTINGS - REGISTER : CTRL_REG2_A 0x21
 */
#define CTRL_REG2_A_DEFAULT                         REGISTER_ZERO
#define HIGHPASS_MODE_NORMAL_WITH_RESET             REGISTER_ZERO
#define HIGHPASS_MODE_REFERENCE_SIGNAL              0b01000000
#define HIGHPASS_MODE_NORMAL                        0b10000000
#define HIGHPASS_MODE_AUTO_RESET_ON_INTERRUPT       0b11000000
#define HIGHPASS_CUTOFF_FREQ                        REGISTER_ZERO
/*
 \brief FDS = Filtered Data Selection
 */
#define HIGHPASS_FDS_INTERNAL_BYPASSED_ENABLED      0b00001000
#define HIGHPASS_FDS_INTERNAL_BYPASSED_DISABLED     REGISTER_ZERO
#define HIGHPASS_FILTER_ENABLED_FOR_CLICK           0b00000100
#define HIGHPASS_FILTER_DISABLED_FOR_CLICK          REGISTER_ZERO
#define HIGHPASS_FILTER_DISABLED_AOI_INT2           REGISTER_ZERO
#define HIGHPASS_FILTER_ENABLED_AOI_INT2            0b00000010
#define HIGHPASS_FILTER_ENABLED_AOI_INT1            0b00000001
#define HIGHPASS_FILTER_DISABLED_AOI_INT1           REGISTER_ZERO

#define CTRL_REG2_A_SETTINGS( HIGHPASS_MODE, HIGHPASS_FDS, HIGHPASS_CLICK_FILTER, HIGHPASS_AOI_INT2, HIGHPASS_AOI_INT1 ) HIGHPASS_MODE | HIGHPASS_CUTOFF_FREQ | HIGHPASS_FDS | HIGHPASS_CLICK_FILTER | HIGHPASS_AOI_INT2 | HIGHPASS_AOI_INT1
/*
 * END OF HIGH PASS FILTER SETTINGS
 */

/*
 * INTERRUPT SETTINGS - REGISTER : CTRL_REG3_A 0x22
 */
#define CTRL_REG3_A_DEFAULT                         REGISTER_ZERO
#define CLICK_INTERRUPT_ON_INT1_ENABLED             0b10000000
#define CLICK_INTERRUPT_ON_INT1_DISABLED            REGISTER_ZERO
#define AOI1_INTERRUPT_ON_INT1_ENABLED              0b01000000
#define AOI1_INTERRUPT_ON_INT1_DISABLED             REGISTER_ZERO
#define AOI2_INTERRUPT_ON_INT1_ENABLED              0b00100000
#define AOI2_INTERRUPT_ON_INT1_DISABLED             REGISTER_ZERO
#define DRDY1_INTERRUPT_ON_INT1_ENABLED             0b00010000
#define DRDY1_INTERRUPT_ON_INT1_DISABLED            REGISTER_ZERO
#define DRDY2_INTERRUPT_ON_INT1_ENABLED             0b00001000
#define DRDY2_INTERRUPT_ON_INT1_DISABLED            REGISTER_ZERO
#define FIFO_WTM_INTERRUPT_ON_INT1_ENABLED          0b00000100
#define FIFO_WTM_INTERRUPT_ON_INT1_DISABLED         REGISTER_ZERO
#define FIFO_OVERRUN_INTERRUPT_ON_INT1_ENABLED      0b00000010
#define FIFO_OVERRUN_INTERRUPT_ON_INT1_DISABLED     REGISTER_ZERO

#define CTRL_REG3_A_SETTINGS(CLICK, AOI1, AOI2, DRDY1, DRDY2, WTM, OVERRUN) CLICK | AOI1 | AOI2 | DRDY1 | DRDY2 | WTM | OVERRUN
/*
 * END OF INTERRUPT SETTINGS
 */

/*
 * RESOLUTION AND SCALE SETTINGS - REGISTER : CTRL_REG4_A 0x23
 */
#define CTRL_REG4_A_DEFAULT                         REGISTER_ZERO

#define BDU_UPDATE_REGISTERS_CONTINUOUSLY           REGISTER_ZERO
#define BDU_WAIT_UNTIL_REGISTERS_ARE_READ           0b10000000
#define BLE_DATA_LSB_AT_LOWER_ADDRESS               REGISTER_ZERO
#define BLE_DATA_MSB_AT_LOWER_ADDRESS               0b01000000
#define FS_SCALE_AT_PLUS_MINUS_2G                   REGISTER_ZERO
#define FS_SCALE_AT_PLUS_MINUS_4G                   0b00010000
#define FS_SCALE_AT_PLUS_MINUS_8G                   0b00100000
#define FS_SCALE_AT_PLUS_MINUS_16G                  0b00110000
#define HR_HI_RES_ENABLED                           0b00001000
#define HR_HI_RES_DISABLED                          REGISTER_ZERO
#define SIM_SERIAL_INTERFACE_4_WIRE                 REGISTER_ZERO
#define SIM_SERIAL_INTERFACE_3_WIRE                 0b00000001

#define CTRL_REG4_A_SETTINGS(BDU, BLE, FS, HR, SIM) BDU | BLE | FS | HR | REGISTER_ZERO | REGISTER_ZERO | SIM
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
 * CLICK_SRC_A 0x39 TODO : Add all click SRC events
 */
#define CLICK_SRC_A_DEFAULT         0x00
/*
 * END OF CLICK_SRC_A
 */

/*
 * CLICK_THS_A 0x3A TODO : Add all click THS events
 */
#define CLICK_THS_A_DEFAULT         0x00
/*
 * END OF CLICK_THS_A
 */

/*
 * TIME_LIMIT_A 0x3B TODO : Need to enable setting the time limit for interrupts
 */
#define TIME_LIMIT_A_DEFAULT        0x00
/*
 * END OF TIME_LIMIT_A
 */

/*
 * TIME_LATENCY_A 0x3C TODO : Need to enable setting the time latency for interrupts
 */
#define TIME_LATENCY_A_DEFAULT      0x00
/*
 * END OF TIME_LATENCY_A
 */

/*
 * TIME_WINDOW_A 0x3D TODO : Need to enable setting the time window for interrupts
 */
#define TIME_WINDOW_A_DEFAULT       0x00
/*
 * END OF TIME_WINDOW_A
 */

/*
 * CRA_REG_M 0x00
 *
#define CRA_REG_M_TEMP_OFF_0.75HZ   0x00
#define CRA_REG_M_TEMP_OFF_1.50HZ   0x04
#define CRA_REG_M_TEMP_OFF_3.00HZ   0x08
#define CRA_REG_M_TEMP_OFF_7.50HZ   0x0C
#define CRA_REG_M_TEMP_OFF_15.0HZ   0x10
#define CRA_REG_M_TEMP_OFF_30.0HZ   0x14
#define CRA_REG_M_TEMP_OFF_75.0HZ   0x18
#define CRA_REG_M_TEMP_OFF_220HZ    0x1C

#define CRA_REG_M_TEMP_ON_0.75HZ    0x80
#define CRA_REG_M_TEMP_ON_1.50HZ    0x84
#define CRA_REG_M_TEMP_ON_3.00HZ    0x88
#define CRA_REG_M_TEMP_ON_7.50HZ    0x8C
#define CRA_REG_M_TEMP_ON_15.0HZ    0x90
#define CRA_REG_M_TEMP_ON_30.0HZ    0x94
#define CRA_REG_M_TEMP_ON_75.0HZ    0x98
#define CRA_REG_M_TEMP_ON_220HZ     0x9C
*
 * END OF CRA_REG_M
 */

/*
 * CRB_REG_M 0x01
 */
#define CRB_REG_M_DEFAULT           0x20
/*
 * END OF CRB_REG_M
 */

/*
 * MR_REG_M 0x02
 */
#define MR_REG_M_DEFAULT                0x03
#define MR_REG_M_CONTINUOUS_CONVERSION  0x00
#define MR_REG_M_SINGLE_CONVERSION      0x01
#define MR_REG_M_SLEEP_MODE1            0x02
#define MR_REG_M_SLEEP_MODE2            0x03
/*
 * END OF MR_REG_M
 */

/**
 \brief BBBLSM303DLHC : Abstract class that provides control of the BBBLSM303DLHC, inherits I2C methods.
 \version   2.3
 \date      Oct-2015
 \copyright GNU Public License.
 */

class LSM303DLHC : public I2C::I2CDevice {

public:

    /**
     \brief BBBLSM303DLHC : A class that provides control of the BBBLSM303DLHC's accelerometer, magnetometer, temp and gyro.
     */
    LSM303DLHC( );

protected:

    void SetDeviceAddress( unsigned char _DeviceAddress ) { this->DeviceAddress = _DeviceAddress; }

    void SetBusId( int _BusId ) { this->BusId = _BusId; }

};

#endif /* SRC_LSM303DLHC_H_ */
