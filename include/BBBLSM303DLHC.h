//  BBBLSM303DLHC.h
//  BBBLSM303DLHC
//
//  Created by Michael Brookes on 25/10/2015.
//  Copyright © 2015 Michael Brookes. All rights reserved.
//

#ifndef SRC_BBBLSM303DLHC_H_
#define SRC_BBBLSM303DLHC_H_

#include "include/BBBI2CDevice.h"
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

//From Table 17. of the LSM303 Data sheet ( https://www.adafruit.com/datasheets/LSM303DLHC.PDF )
#define ACCEL_ADDRESS        0x19    //!< I2C Address of the accelerometer device.
#define CTRL_REG1_A         0x20    //!< Read/Write (power control) : Default - 00111
#define CTRL_REG2_A         0x21    //!< Read/Write (filter selection) : Default - 0
#define CTRL_REG3_A         0x22    //!< Read/Write (interrupt settings) : Default - 0
#define CTRL_REG4_A         0x23    //!< Read/Write (range/resolution settings) : Default - 0
#define CTRL_REG5_A         0x24    //!< Read/Write (FIFO setting | internal memory) : Default - 0
#define CTRL_REG6_A         0x25    //!< Read/Write (CLICK interupt setting) : Default - 0
#define REFERENCE_A         0x26    //!< Read/Write (Reference value for interrupt generation) : Default - 0
#define STATUS_REG_A        0x27    //!< Read Only  (Overrun trigger) : Default - 0
#define OUT_X_L_A           0x28    //!< Read Only  (X-axis acceleration data. The value is expressed in 2’s complement)
#define OUT_X_H_A           0x29    //!< Read Only  (X-axis acceleration data. The value is expressed in 2’s complement)
#define OUT_Y_L_A           0x2A    //!< Read Only  (Y-axis acceleration data. The value is expressed in 2’s complement)
#define OUT_Y_H_A           0x2B    //!< Read Only  (Y-axis acceleration data. The value is expressed in 2’s complement)
#define OUT_Z_L_A           0x2C    //!< Read Only  (Z-axis acceleration data. The value is expressed in 2’s complement)
#define OUT_Z_H_A           0x2D    //!< Read Only  (Z-axis acceleration data. The value is expressed in 2’s complement)
#define FIFO_CTRL_REG_A     0x2E    //!< Read/Write (FIFO mode selection) : Default - 0
#define FIFO_SRC_REG_A      0x2F    //!< Read Only  (FIFO register)
#define INT1_CFG_A          0x30    //!< Read/Write (interrupt 1 settings)
#define INT1_SOURCE_A       0x31    //!< Read Only  (interrupt 1 settings)
#define INT1_THS_A          0x32    //!< Read/Write (interrupt 1 settings)
#define INT1_DURATION_A     0x33    //!< Read/Write (interrupt 1 settings)
#define INT2_CFG_A          0x34    //!< Read/Write (interrupt 2 settings)
#define INT2_SOURCE_A       0x35    //!< Read 		(interrupt 2 settings)
#define INT2_THS_A          0x36    //!< Read/Write (interrupt 2 settings)
#define INT2_DURATION_A     0x37    //!< Read/Write (interrupt 2 settings)
#define CLICK_CFG_A         0x38    //!< Read/Write (interrupt double CLICK on Z axis) : Default - 0
#define CLICK_SRC_A         0x39    //!< Read/Write (interrupt double CLICK settings)
#define CLICK_THS_A         0x3A    //!< Read/Write (interrupt double CLICK settings)
#define TIME_LIMIT_A        0x3B    //!< Read/Write (interrupt double CLICK settings)
#define TIME_LATENCY_A      0x3C    //!< Read/Write (interrupt double CLICK settings)
#define TIME_WINDOW_A       0x3D    //!< Read/Write (interrupt double CLICK settings)

#define MAG_ADDRESS            0x1E    //!< I2C Address of the magnetometer device.
#define CRA_REG_M           0x00    //!< Read/Write (0x94 or 10010100 Temp sensor on and 30 hz refresh rate.)
#define CRB_REG_M           0x01    //!< Read/Write
#define MR_REG_M            0x02    //!< Read/Write (0x00 or 00000000 Continuous conversion mode.)
#define OUT_X_H_M           0x03    //!< Read Only  (X-axis magnetometer data. The value is expressed in 2’s complement)
#define OUT_X_L_M           0x04    //!< Read Only  (X-axis magnetometer data. The value is expressed in 2’s complement)
#define OUT_Z_H_M           0x05    //!< Read Only  (Z-axis magnetometer data. The value is expressed in 2’s complement)
#define OUT_Z_L_M           0x06    //!< Read Only  (Z-axis magnetometer data. The value is expressed in 2’s complement)
#define OUT_Y_H_M           0x07    //!< Read Only  (Y-axis magnetometer data. The value is expressed in 2’s complement)
#define OUT_Y_L_M           0x08    //!< Read Only  (Y-axis magnetometer data. The value is expressed in 2’s complement)
#define SR_REG_Mg           0x09    //!< Read Only
#define IRA_REG_M           0x0A    //!< Read Only
#define IRB_REG_M           0x0B    //!< Read Only
#define IRC_REG_M           0x0C    //!< Read Only
#define TEMP_OUT_H_M        0x31    //!< Read Only  (Temp sensor data. The value is expressed in 2’s complement)
#define TEMP_OUT_L_M        0x32    //!< Read Only  (Temp sensor data. The value is expressed in 2’s complement)

#define OFFSET_X            25.5    //!< average of 2000 iterations on a flat floor not moving.
#define OFFSET_Y            55        //!< average of 2000 iterations on a flat floor not moving.

#define MAX_DATASTORE        15

/**
 \brief BBBLSM303DLHC : A class that provides control of the LSM303DLHC which contains : accelerometer, magnetometer.
 \author    Michael Brookes
 \version   1.0
 \date      Oct-2015
 \copyright GNU Public License.
 */
class BBBLSM303DLHC {

public:

    /**
     \brief Please refer to the documention provided for your LSM303DLHC for further details (CTRL_REG1_A pg 25 point 7.1.1)
     */
    enum _switch {
        ON = 0x77,        //!< 0x77 Normal / low-power mode off (200 Hz), X, Y and Z enabled
        OFF = 0x00        //!< 0x00 Off
    };

    /**
     \brief Please refer to the documention provided for your LSM303DLHC for further details (CTRL_REG4_A pg 27 point 7.1.4)
     */
    enum _range {
        HIGHRES_16G = 0x38, //!< 0x38 (accelerometer) continuous update (0b), data LSB @ lower address (0b), ±16 g (11b), high-resolution enable (1b), uneditable (00b), 4-wire interface (0b)
        LOWRES_2G = 0x00  //!< 0x00 (accelerometer) continuous update (0b), data LSB @ lower address (0b), ±2 g (00b), high-resolution disable (0b), uneditable (00b), 4-wire interface (0b)
    };

    /**
     \brief Please refer to the documention provided for your LSM303DLHC for further details (CRA_REG_M pg 37 point 7.2.1)
     */
    enum _data_rate {
        HZ_075 = 0x80, //!< 0x80 (magnetometer) data rate = 0.75 HZ and (temp_sensor) is on.
        HZ_150 = 0x84, //!< 0x84 (magnetometer) data rate = 1.50 HZ and (temp_sensor) is on.
        HZ_300 = 0x88, //!< 0x88 (magnetometer) data rate = 3.00 HZ and (temp_sensor) is on.
        HZ_750 = 0x8C, //!< 0x8C (magnetometer) data rate = 7.50 HZ and (temp_sensor) is on.
        HZ_1500 = 0x90, //!< 0x90 (magnetometer) data rate = 15.0 HZ and (temp_sensor) is on.
        HZ_3000 = 0x94, //!< 0x94 (magnetometer) data rate = 30.0 HZ and (temp_sensor) is on.
        HZ_7500 = 0x98, //!< 0x98 (magnetometer) data rate = 75.0 HZ and (temp_sensor) is on.
        HZ_22000 = 0x9C    //!< 0x9C (magnetometer) data rate = 220.0 HZ and (temp_sensor) is on.
    };

    /**
     \brief Please refer to the documention provided for your LSM303DLHC for further details (MR_REG_M pg 38 point 7.2.3)
     */
    enum _operation_mode {
        Continuous = 0x00, //!< 0x00 Continuous-conversion mode (magnetometer)
        Single = 0x01, //!< 0x01 Single-conversion mode (magnetometer)
        SleepMode1 = 0x02, //!< 0x02 Sleep mode (magnetometer)
        SleepMode2 = 0x03  //!< 0x03 Sleep mode (magnetometer)
    };

    /**
     \brief BBBLSM303DLHC : A class that provides control of the LSM303DLHC's accelerometer, magnetometer, temp and gyro.
     */
    BBBLSM303DLHC( );

    /**
     \fn Public function SetPower( _switch AccelSwitch )
     \brief Sets the power on the accelerometer to either On or Off
     \param <_switch> AccelSwitch
     \return <int> -1 failure to open the bus, 0 success.
     */
    int SetPower( _switch AccelSwitch );

    /**
     \fn Public function SetRange( _range AccelRange )
     \brief Sets the range for the accelerometer on this device (see _range enum for options)
     \param <_range> AccelRange
     \return <int> -1 failure to open the bus, 0 success.
     */
    int SetRange( _range AccelRange );

    /**
	 \fn Public function SetDataRate( _data_rate MagDataRate )
	 \brief Sets the data rate for the magnetometer on this device (see _data_rate enum for options)
	 \param <_data_rate> MagDataRate
	 \return <int> -1 failure to open the bus, 0 success.
	 */
    int SetDataRate( _data_rate MagDataRate );

    /**
	 \fn Public function SetOperationMode( _operation_mode MagOperationMode )
	 \brief Sets the range for the accelerometer on this device to either 2G or 16G
	 \param <_range> AccelRange
	 \return <int> -1 failure to open the bus, 0 success.
	 */
    int SetOperationMode( _operation_mode MagOperationMode );

    /**
     \fn Public function GetRoll( void )
     \brief Returns the current Roll orientation of the accelerometer.
     \param <void>
     \return <double> this->Roll
     */
    double GetRoll( void );

    /**
     \fn Public function GetRollAndPitch( void )
     \brief Returns the current Roll and Pitch orientation of the accelerometer.
     \param <void>
     \return <void>
     */
    void GetPitchAndRoll( void );

    /**
     \fn Public function GetPitch( void )
     \brief Returns the current Pitch orientation of the accelerometer.
     \param <void>
     \return <double> this->Pitch
     */
    double GetPitch( void );

    /**
     \fn Public function GetHeading( void )
     \brief Returns the current heading from the magnetometer
     \param <void>
     \return <double> this->Heading
     */
    double GetHeading( void );

    /**
    \fn Public function SetPitchAndRollAverages( int iterations )
    \brief Reads the current Roll and Pitch values on this device X times and stores the average.
    \param <int>
    \return <void>
    */
    void SetPitchAndRollAverages( int iterations );

    /**
    \fn Public function SetHeadingAverages( int iterations )
    \brief Reads the current Heading value on this device X times and stores the average.
    \param <int>
    \return <void>
    */
    void SetHeadingAverages( int iterations );

    static void *GetPitchAndRollValues( void *accel_inst );

    static void *GetHeadingValues( void *accel_inst );

    double PitchDataStoredValues[MAX_DATASTORE];

    double RollDataStoredValues[MAX_DATASTORE];

    double HeadingDataStoredValues[MAX_DATASTORE];

    void StartRecordingPitchAndRoll( );

    void StartRecordingHeading( );

    double Heading;                            //!< Stores the Magnetometer Heading value calculated from the M_X, M_Y and M_Z values.
    double Roll;                            //!< Stores the Accelerometer Roll value calculated from the X, Y and Z values.
    double Pitch;                            //!< Stores the Accelerometer Pitch value calculated from the X, Y and Z values.
    double avgPitch;
    double avgRoll;
    double avgHeading;

protected:

    /**
     \brief Creates a new object containing communication and the setup of the accelerometer.
     */
    BBBI2CDevice Accelerometer = *new BBBI2CDevice( ACCEL_ADDRESS, BBBI2CDevice::I2C1 );

    /**
     \brief Creates a new object containing communication and the setup of the magentometer.
     */
    BBBI2CDevice Magnetometer = *new BBBI2CDevice( MAG_ADDRESS, BBBI2CDevice::I2C1 );

    _switch AccelSwitch;                    //!< enum value for the Accelerometer power status.
    _range AccelRange;                        //!< enum value for the Accelerometer range/resolution value.
    _data_rate MagDataRate;                    //!< enum value for the Magnetometer data rate value.
    _operation_mode MagOperationMode;        //!< enum value for the Magnetometer operation mode value.

    int ThreadRet;

    pthread_t AccelNotifyer, MagnetNotifyer;

    /**
     \brief Creates the template for vector, used by the accelerometer and magnetometer.
     */
    template<typename T>
    struct vector {
        T X, Y, Z;
    };

    vector<double> a; //!< accelerometer vector (X, Y, Z)
    vector<double> m; //!< magnetometer vector (X, Y, Z)

    /**
    \fn Protected function SetAllCurrentValues( void )
    \brief Reads and stores the current accelerometer X, Y, Z, Roll and Pitch values and magnetometers X, Y, Z and heading.
    \param <void>
    \return <void>
    */
    void SetAllCurrentValues( void );

    /**
    \fn Protected function GetPowerStatus( void ) const
    \brief Returns the current Power setting of the device.
    \param <void>
    \return <_switch> this->AccelSwitch
    */
    _switch GetPowerStatus( void ) const;

    /**
    \fn Protected function GetRangeSetting( void ) const
    \brief Returns the current Range setting of the device.
    \param <void>
    \return <_range> this->AccelRange
    */
    _range GetRangeSetting( void ) const;

    /**
    \fn Protected function SetPitchAndRoll( void )
    \brief Runs an algorithm to determine the Pitch and Roll from the current X, Y and Z values.
    \param <void>
    \return <void>
    */
    void SetPitchAndRoll( void );

    /**
    \fn Protected function SetHeading( void )
    \brief Sets the current heading (this->Heading) from the magnetometer. With thanks to Adafruit for this algorythm.
    \param <void>
    \return <void>
    */
    void SetHeading( void );

    /**
     \fn Protected function GetAccelX( void )
     \brief Reads the two registers that contain the X value on the LSM303DLHC accelerometer.
     \param <void>
     \return <short> this->X
     */
    double GetAccelX( void );

    /**
     \fn Protected function GetAccelY( void )
     \brief Reads the two registers that contain the Y value on the LSM303DLHC accelerometer.
     \param <void>
     \return <short> this->Y
     */
    double GetAccelY( void );

    /**
     \fn Protected function GetAccelZ( void )
     \brief Reads the two registers that contain the Z value on the LSM303DLHC accelerometer.
     \param <void>
     \return <short> this->Z
     */
    double GetAccelZ( void );

    /**
     \fn Protected function GetMagX( void )
     \brief Reads the two registers that contain the X value on the LSM303DLHC magnetometer.
     \param <void>
     \return <short> this->M_X
     */
    double GetMagX( void );

    /**
     \fn Protected function GetMagY( void )
     \brief Reads the two registers that contain the Y value on the LSM303DLHC magnetometer.
     \param <void>
     \return <short> this->M_Y
     */
    double GetMagY( void );

    /**
     \fn Protected function GetMagZ( void )
     \brief Reads the two registers that contain the Z value on the LSM303DLHC magnetometer.
     \param <void>
     \return <short> this->M_Z
     */
    double GetMagZ( void );

    void AddToPitchAndRollDataStore( );

    void AddToHeadingDataStore( );

};

#endif /* SRC_BBBLSM303DLHC_H_ */
