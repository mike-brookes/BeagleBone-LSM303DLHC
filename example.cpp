/*
/*
Copyright (C) 2016 Michael Brookes

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
/*
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
        this->LoadRecommendedFlightSettings( );
        this->Init( );
    }

};

int main ( void ) {
    using namespace abI2C;

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

    while(1){
        cout << "Accelerometer - Current X val = " << Accelerometer->X << endl;
        cout << "Accelerometer - Current Y val = " << Accelerometer->Y << endl;
        cout << "Accelerometer - Current Z val = " << Accelerometer->Z << endl;
        usleep( Accelerometer->DataTimer + 1000000 ); //speed of data + 1 second for display purposes, (+1000000 not required for production).
    }

}