//
//  BBBLSM303DLHC.cpp
//  BBBLSM303DLHC
//
//  Created by Michael Brookes on 25/10/2015.
//  Copyright © 2015 Michael Brookes. All rights reserved.
//

#include "BBBLSM303DLHC.h"

/**
 \brief BBBLSM303DLHC : A class that provides control of the accelerometer LSM303DLHC and extends I2C devices on the Beaglebone Black.
  BBBI2CDevice : A low level control of I2C devices on the Beaglebone Black. requires :
 \param <int> I2C_DeviceAddress (obtained from your I2C device data sheet, usually passed in hex (e.g 0x19)
 \param <I2CBus> I2C_BusAddress (the Beaglebone has two I2C busses, either I2C1 or I2C2 both relate to their respective files in /dev/itc-#)
 */
BBBLSM303DLHC::BBBLSM303DLHC( ) {

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

void* BBBLSM303DLHC::GetPitchAndRollValues(  void *accel_inst  ) {
    BBBLSM303DLHC* accel = (BBBLSM303DLHC*)accel_inst;
    while( 1 ) {
        accel->GetPitchAndRoll( );
        accel->AddToPitchAndRollDataStore( );
        usleep( 5000 );
    }
}

void* BBBLSM303DLHC::GetHeadingValues(  void *accel_inst  ) {
    BBBLSM303DLHC* accel = (BBBLSM303DLHC*)accel_inst;
    while( 1 ) {
        accel->GetHeading( );
        accel->AddToHeadingDataStore( );
        usleep( 5000 );
    }
}

void BBBLSM303DLHC::AddToPitchAndRollDataStore( ) {
    for( int i = 0; i < ( MAX_DATASTORE - 1 ); i++ ) {
        int NextIndex = (i + 1);
        this->PitchDataStoredValues[ i ] = this->PitchDataStoredValues[ NextIndex ];
        this->RollDataStoredValues[ i ] = this->RollDataStoredValues[ NextIndex ];
    }

    this->PitchDataStoredValues[ ( MAX_DATASTORE - 1 ) ] = this->Pitch;
    this->RollDataStoredValues[ ( MAX_DATASTORE - 1 ) ] = this->Roll;
}

void BBBLSM303DLHC::AddToHeadingDataStore( ) {
    for( int i = 0; i < ( MAX_DATASTORE - 1 ); i++ ) {
        int NextIndex = (i + 1);
        this->HeadingDataStoredValues[ i ] = this->HeadingDataStoredValues[ NextIndex ];
    }
    this->HeadingDataStoredValues[ ( MAX_DATASTORE - 1 ) ] = this->Heading;
}

void BBBLSM303DLHC::StartRecordingPitchAndRoll( ) {
    pthread_create( &this->AccelNotifyer, NULL, BBBLSM303DLHC::GetPitchAndRollValues, this );
}

void BBBLSM303DLHC::StartRecordingHeading( ) {
    pthread_create( &this->MagnetNotifyer, NULL, BBBLSM303DLHC::GetHeadingValues, this );
}

/**
 \fn Public function SetPower( _switch AccelSwitch )
 \brief Sets the power on this device to either On or Off
 \param <_switch> AccelSwitch
 \return <int> -1 failure to open the bus, 0 success.
 */
int BBBLSM303DLHC::SetPower( _switch AccelSwitch ) {
    this->AccelSwitch = AccelSwitch;
    return this->Accelerometer.I2C_WriteToReg( CTRL_REG1_A, AccelSwitch );
}

/**
 \fn Public function SetRange( _range AccelRange )
 \brief Sets the range on this device to either 2G or 16G
 \param <_range> AccelRange
 \return <int> -1 failure to open the bus, 0 success.
 */
int BBBLSM303DLHC::SetRange( _range AccelRange ) {
    this->AccelRange = AccelRange;
    return this->Accelerometer.I2C_WriteToReg( CTRL_REG4_A, AccelRange );
}

/**
 \fn Public function SetDataRate( _data_rate MagDataRate )
 \brief Sets the Data Rate for the Magnetometer. Continous, Single read, off.
 \param <_data_rate> DataRate
 \return <int> -1 failure to open the bus, 0 success.
 */
int BBBLSM303DLHC::SetDataRate( _data_rate MagDataRate ) {
    this->MagDataRate = MagDataRate;
    return this->Magnetometer.I2C_WriteToReg( CRA_REG_M, MagDataRate );
}

/**
 \fn Public function SetOperationMode( _operation_mode MagOperationMode )
 \brief Sets the Operation mode for the Magnetometer. Refresh rate.
 \param <_operation_mode> OperationMode
 \return <int> -1 failure to open the bus, 0 success.
 */
int BBBLSM303DLHC::SetOperationMode( _operation_mode MagOperationMode ) {
    this->MagOperationMode = MagOperationMode;
    return this->Magnetometer.I2C_WriteToReg( MR_REG_M, MagOperationMode );
}

/**
 \fn Public function GetRollAndPitch( void )
 \brief Returns the current Roll and Pitch orientation of the accelerometer.
 \param <void>
 \return <void>
 */
void BBBLSM303DLHC::GetPitchAndRoll( void ) {
    this->GetAccelX( );
    this->GetAccelY( );
    this->GetAccelZ( );
    this->SetPitchAndRoll( );
}

/**
 \fn Public function GetRoll( void )
 \brief Returns the current Roll orientation of the accelerometer.
 \param <void>
 \return <double> this->Roll
 */
double BBBLSM303DLHC::GetRoll( void ) {
    this->GetAccelX( );
    this->GetAccelY( );
    this->GetAccelZ( );
    this->SetPitchAndRoll( );
    return this->Roll;
}

/**
 \fn Public function GetPitch( void )
 \brief Returns the current Pitch orientation of the accelerometer.
 \param <void>
 \return <double> this->Pitch
 */
double BBBLSM303DLHC::GetPitch( void ) {
    this->GetAccelX( );
    this->GetAccelY( );
    this->GetAccelZ( );
    this->SetPitchAndRoll( );
    return this->Pitch;
}

/**
 \fn Public function GetHeading( void )
 \brief Returns the current heading from the magnetometer
 \param <void>
 \return <double> this->Heading
 */
double BBBLSM303DLHC::GetHeading( void ) {
    this->GetMagX( );
    this->GetMagY( );
    this->GetMagZ( );
    this->SetHeading();
    return this->Heading;
}

/**
\fn Protected function SetAllCurrentValues( void )
\brief Reads and stores the current accelerometer X, Y, Z, Roll and Pitch values and magnetometers X, Y, Z and heading.
\param <void>
\return <void>
*/
void BBBLSM303DLHC::SetAllCurrentValues( void ) {
    this->GetAccelX( );
    this->GetAccelY( );
    this->GetAccelZ( );
    this->SetPitchAndRoll( );
    this->GetMagX( );
    this->GetMagY( );
    this->GetMagZ( );
    this->SetHeading();
}

/**
 \fn Protected function GetPowerStatus( void ) const
 \brief Returns the current Power setting of the device.
 \param <void>
 \return <_switch> this->Switch
 */
BBBLSM303DLHC::_switch BBBLSM303DLHC::GetPowerStatus( void ) const {
    return this->AccelSwitch;
}

/**
 \fn Protected function GetRangeSetting( void ) const
 \brief Returns the current Range setting of the device.
 \param <void>
 \return <_range> this->Range
 */
BBBLSM303DLHC::_range BBBLSM303DLHC::GetRangeSetting( void ) const {
    return this->AccelRange;
}

/**
 \fn Public function SetAverages( int iterations = 50 )
 \brief Reads the current X, Y, Z, Roll and Pitch values on this device 50 times and stores the average.
 \param <void>
 \return <void>
 */
void BBBLSM303DLHC::SetPitchAndRollAverages( int iterations = 50 ) {
    int i = 0, total_roll = 0, total_pitch = 0;
    while (i < iterations) {
        total_roll += this->Roll;
        total_pitch += this->Pitch;
        usleep(5000);
        i++;
    }
    this->avgRoll = total_roll / iterations;
    this->avgPitch = total_pitch / iterations;
}

/**
 \fn Public function SetAverages( int iterations = 50 )
 \brief Reads the current X, Y, Z, Roll and Pitch values on this device 50 times and stores the average.
 \param <void>
 \return <void>
 */
void BBBLSM303DLHC::SetHeadingAverages( int iterations = 50 ) {
    int i = 0, total_heading = 0;
    while (i < iterations) {
        total_heading += this->Heading;
        usleep(5000);
        i++;
    }
    this->avgHeading = total_heading / iterations;
}

/**
 \fn Protected function SetRollAndPitch( void )
 \brief Runs an algorithm to determine the Pitch and Roll from the accelerometers X, Y and Z values.
 \param <void>
 \return <void>
 */
void BBBLSM303DLHC::SetPitchAndRoll( void ) {
    this->Pitch  = ( atan2 ( ( double ) this->a.Y, ( double ) this->a.Z ) * 180.0 ) / M_PI;
    this->Roll = (( atan2 ( ( double ) this->a.X, sqrt( ( double ) this->a.Y * ( double ) this->a.Y + ( double ) this->a.Z * ( double ) this->a.Z ) ) * 180.0 ) / M_PI);
}

/**
 \fn Protected function SetHeading( void )
 \brief Sets the current heading (this->Heading) from the magnetometer. With thanks to Adafruit for this algorythm.
 \param <void>
 \return <void>
 */
void BBBLSM303DLHC::SetHeading( void ) {
    double x2 = 0, y2 = 0;

    double t_roll = this->a.X * this->a.X + this->a.Z * this->a.Z;
    float rollRadians = ( float ) atan2( this->a.Y, sqrt( t_roll ) );

    double t_pitch = this->a.Y * this->a.Y + this->a.Z * this->a.Z;
    float pitchRadians = ( float ) atan2( this->a.X, sqrt( t_pitch ) );

    float cosRoll = ( float ) cos( rollRadians );
    float sinRoll = ( float ) sin( rollRadians );

    float cosPitch = ( float ) cos( -1 * pitchRadians );
    float sinPitch = ( float ) sin( -1 * pitchRadians );

    this->m.X = ( this->m.X ) * cosPitch + ( this->m.Z ) * sinPitch;
    this->m.Y = ( this->m.X ) * sinRoll * sinPitch + ( this->m.Y ) * cosRoll - ( this->m.Z ) * sinRoll * cosPitch;

    x2 = this->m.X;
    y2 = this->m.Y;

    this->Heading = ( atan2 ( this->m.X, this->m.Y ) * 180 ) / M_PI;
}

/**
 \fn Protected function GetAccelX( void )
 \brief Reads the two registers that contain the X value on the LSM303DLHC accelerometer.
 \param <void>
 \return <short> this->X
 */
double BBBLSM303DLHC::GetAccelX( void ) {
    this->a.X = ( ( short ) this->Accelerometer.I2C_GetValue( OUT_X_H_A ) << 8 ) | ( short ) this->Accelerometer.I2C_GetValue( OUT_X_L_A );
    this->a.X -= OFFSET_X;
    return this->a.X;
}

/**
 \fn Protected function GetAccelY( void )
 \brief Reads the two registers that contain the Y value on the LSM303DLHC accelerometer.
 \param <void>
 \return <short> this->Y
 */
double BBBLSM303DLHC::GetAccelY( void ) {
    this->a.Y = ( ( short ) this->Accelerometer.I2C_GetValue( OUT_Y_H_A ) << 8 ) | ( short ) this->Accelerometer.I2C_GetValue( OUT_Y_L_A );
    this->a.Y -= OFFSET_Y;
    return this->a.Y;
}

/**
 \fn Protected function GetAccelZ( void )
 \brief Reads the two registers that contain the Z value on the LSM303DLHC accelerometer.
 \param <void>
 \return <short> this->Z
 */
double BBBLSM303DLHC::GetAccelZ( void ) {
    this->a.Z = ( ( short ) this->Accelerometer.I2C_GetValue( OUT_Z_H_A ) << 8 ) | ( short ) this->Accelerometer.I2C_GetValue( OUT_Z_L_A );
    return this->a.Z;
}

/**
 \fn Protected function GetMagX( void )
 \brief Reads the two registers that contain the X value on the LSM303DLHC magnetometer.
 \param <void>
 \return <short> this->M_X
 */
double BBBLSM303DLHC::GetMagX( void ) {
    this->m.X = ( ( ( short ) this->Magnetometer.I2C_GetValue( OUT_X_H_M ) << 8 ) | ( short ) this->Magnetometer.I2C_GetValue( OUT_X_L_M ) );// /1100;
    return this->m.X;
}

/**
 \fn Protected function GetMagY( void )
 \brief Reads the two registers that contain the Y value on the LSM303DLHC magnetometer.
 \param <void>
 \return <short> this->M_Y
 */
double BBBLSM303DLHC::GetMagY( void ) {
    this->m.Y = ( ( ( short ) this->Magnetometer.I2C_GetValue( OUT_Y_H_M ) << 8 ) | ( short ) this->Magnetometer.I2C_GetValue( OUT_Y_L_M ) ); // /1100;
    return this->m.Y;
}

/**
 \fn Protected function GetMagZ( void )
 \brief Reads the two registers that contain the Z value on the LSM303DLHC magnetometer.
 \param <void>
 \return <short> this->M_Z
 */
double BBBLSM303DLHC::GetMagZ( void ) {
    this->m.Z = ( ( ( short ) this->Magnetometer.I2C_GetValue( OUT_Z_H_M ) << 8 ) | ( short ) this->Magnetometer.I2C_GetValue( OUT_Z_L_M ) ); // /980;
    return this->m.Z;
}
