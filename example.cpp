/*
 * test.cpp
 *
 *  Created on: 25 Oct 2015
 *      Author: Michael Brookes
 *      Version 2.0 - 4/4/2016
 *
 *      Example of using the LSM303DLHC class
 *      The accelerometer class creates an object and initialises the accelerometer on the LSM303
 *      It then uses the Macros available from the LSM303DLHC.h to configure the device
 *      I have added a recommended flight settings as these are the settings I use on the device.
 *      This class is a basic class - it doesn't retrieve values from the accelerometer but this functionality will be
 *      added in a separate project shortly...
 */

#include "./Lib/LSM303/LSM303DLHC.h"
#include <bitset>

using namespace std;

class LSM303_Accelerometer : public LSM303DLHC {

public:
    LSM303_Accelerometer( unsigned char _DeviceAddress, int _BusId ) {
        this->SetDeviceAddress( _DeviceAddress );
        this->SetBusId( _BusId );
        this->InitDevice( );
    }

};

int main ( void ) {
    using namespace I2C;

    LSM303_Accelerometer *Accelerometer;

    Accelerometer = new LSM303_Accelerometer( ACCEL_ADDRESS, 1 );

    Accelerometer->LoadRecommendedFlightSettings( );

    cout << "Power Settings = " << bitset<8>( Accelerometer->GetPowerSettings( ) ) << endl;
    cout << "HighPass Settings = " << bitset<8>( Accelerometer->GetHighPassSettings( ) ) << endl;
    cout << "Int1 Settings = " << bitset<8>( Accelerometer->GetInt1Settings( ) ) << endl;
    cout << "Resolution and Scale Settings = " << bitset<8>( Accelerometer->GetDataSettings( ) ) << endl;
    cout << "Memory Settings = " << bitset<8>( Accelerometer->GetMemorySettings( ) ) << endl;
    cout << "Interrupt Settings = " << bitset<8>( Accelerometer->GetInterruptSettings( ) ) << endl;
    cout << "FIFO Settings = " << bitset<8>( Accelerometer->GetFIFOSettings( ) ) << endl;
    cout << "Interrupt1 CFG Settings = " << bitset<8>( Accelerometer->GetInterrupt1CFGSettings( ) ) << endl;
    cout << "Interrupt2 CFG Settings = " << bitset<8>( Accelerometer->GetInterrupt2CFGSettings( ) ) << endl;
    cout << "Click CFG Settings = " << bitset<8>( Accelerometer->GetClickCFGSettings( ) ) << endl;
    cout << "Click SRC Settings = " << bitset<8>( Accelerometer->GetClickSRCSettings( ) ) << endl;

}