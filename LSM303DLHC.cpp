//
//  LSM303DLHC.cpp
//  LSM303DLHC
//
//  Created by Michael Brookes on 25/10/2015.
//  Copyright © 2015 Michael Brookes. All rights reserved.
//

#include "LSM303DLHC.h"

/**
 \brief LSM303DLHC : A class that provides control of the accelerometer LSM303DLHC and extends I2C devices on the Beaglebone Black.
  BBBI2CDevice : A low level control of I2C devices on the Beaglebone Black. requires :
 \param <int> I2C_DeviceAddress (obtained from your I2C device data sheet, usually passed in hex (e.g 0x19)
 \param <I2CBus> I2C_BusAddress (the Beaglebone has two I2C buses, either I2C1 or I2C2 both relate to their respective files in /dev/itc-#)
 */
LSM303DLHC::LSM303DLHC( ) {
    int u = 0;
    if( this->SetRange( _range::HIGHRES_16G ) < 0 ) {
        cerr << "Critical Error 1 : LSM303DLHC - Attempted to set the Accelerometers Range to : " << this->AccelRange << " | This action failed." << endl;
        exit( 1 );
    }

    if( this->SetPower( _switch::ON ) < 0 ) {
        cerr << "Critical Error 1 : LSM303DLHC - Attempted to set the Accelerometers Power State to : " << this->AccelSwitch << " | This action failed." << endl;
        exit( 1 );
    }

    if( this->SetDataRate( _data_rate::HZ_3000 ) < 0 ) {
        cerr << "Critical Error 1 : LSM303DLHC - Attempted to set the Magnetometers Data Rate to : " << this->MagDataRate << " | This action failed." << endl;
        exit( 1 );
    }

    if( this->SetOperationMode( _operation_mode::Continuous ) < 0 ) {
        cerr << "Critical Error 1 : LSM303DLHC - Attempted to set the Magnetometers Operation Mode to : " << this->MagOperationMode << " | This action failed." << endl;
        exit( 1 );
    }

    this->SetAllCurrentValues( );

}

/**
 \fn Public function SetPower( _switch AccelSwitch )
 \brief Sets the power on this device to either On or Off
 \param <_switch> AccelSwitch
 \return <int> -1 failure to open the bus, 0 success.
 */
int LSM303DLHC::SetPower( _switch AccelSwitch ) {
    this->AccelSwitch = AccelSwitch;
    return this->Accelerometer.I2C_WriteToReg( CTRL_REG1_A, AccelSwitch );
}

/**
 \fn Public function SetRange( _range AccelRange )
 \brief Sets the range on this device to either 2G or 16G
 \param <_range> AccelRange
 \return <int> -1 failure to open the bus, 0 success.
 */
int LSM303DLHC::SetRange( _range AccelRange ) {
    this->AccelRange = AccelRange;
    return this->Accelerometer.I2C_WriteToReg( CTRL_REG4_A, AccelRange );
}

/**
 \fn Public function SetDataRate( _data_rate MagDataRate )
 \brief Sets the Data Rate for the Magnetometer. Continous, Single read, off.
 \param <_data_rate> DataRate
 \return <int> -1 failure to open the bus, 0 success.
 */
int LSM303DLHC::SetDataRate( _data_rate MagDataRate ) {
    this->MagDataRate = MagDataRate;
    return this->Magnetometer.I2C_WriteToReg( CRA_REG_M, MagDataRate );
}

/**
 \fn Public function SetOperationMode( _operation_mode MagOperationMode )
 \brief Sets the Operation mode for the Magnetometer. Refresh rate.
 \param <_operation_mode> OperationMode
 \return <bool>.
 */
bool LSM303DLHC::SetOperationMode( operation_mode _MagOperationMode ) {
    this->SetRegisterAddress( MR_REG_M );
    this->SetRegisterValue( _MagOperationMode );
    return ( this->WriteToDevice( 2 ) == EXIT_SUCCESS );
}

/**
 \fn Protected function GetPowerStatus( void ) const
 \brief Returns the current Power setting of the device.
 \param <void>
 \return <_switch> this->Switch
 */
LSM303DLHC::POWER_SWITCH LSM303DLHC::GetPowerStatus( void ) const { return this->AccelSwitch; }

/**
 \fn Protected function GetRangeSetting( void ) const
 \brief Returns the current Range setting of the device.
 \param <void>
 \return <_range> this->Range
 */
LSM303DLHC::_range LSM303DLHC::GetRangeSetting( void ) const { return this->AccelRange; }

