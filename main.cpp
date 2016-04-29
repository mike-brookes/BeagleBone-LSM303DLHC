/*
 * test.cpp
 *
 *  Created on: 25 Oct 2015
 *      Author: michaelbrookes
 */

#include "./LSM303DLHC.h"
#include <bitset>

using namespace std;

class LSM303_Accelerometer : public LSM303DLHC {

public:
    LSM303_Accelerometer( unsigned char _DeviceAddress, int _BusId ) {
        this->SetDeviceAddress( _DeviceAddress );
        this->SetBusId( _BusId );
        this->InitDevice( );
    }
    unsigned long long int PowerSettings = CTRL_REG1_A_SETTINGS( DATA_RATE_400HZ, LOW_POWER_DISABLED,
                                                        Z_AXIS_ENABLED, Y_AXIS_ENABLED, X_AXIS_ENABLED ); //0b0000000001110111

    unsigned long long int HighPassSettings = CTRL_REG2_A_SETTINGS( HIGHPASS_MODE_NORMAL_WITH_RESET, HIGHPASS_FDS_INTERNAL_BYPASSED_DISABLED,
                                                              HIGHPASS_FILTER_DISABLED_FOR_CLICK, HIGHPASS_FILTER_DISABLED_AOI_INT2,
                                                              HIGHPASS_FILTER_DISABLED_AOI_INT1 ); //0b0000000000000000

    unsigned long long int Int1Settings = CTRL_REG3_A_SETTINGS( CLICK_INTERRUPT_ON_INT1_DISABLED, AOI1_INTERRUPT_ON_INT1_DISABLED,
                                                      AOI2_INTERRUPT_ON_INT1_DISABLED, DRDY1_INTERRUPT_ON_INT1_DISABLED,
                                                      DRDY2_INTERRUPT_ON_INT1_DISABLED, FIFO_WTM_INTERRUPT_ON_INT1_DISABLED,
                                                      FIFO_OVERRUN_INTERRUPT_ON_INT1_DISABLED ); //0b0000000000000000

    unsigned long long int DataSettings = CTRL_REG4_A_SETTINGS( BDU_UPDATE_REGISTERS_CONTINUOUSLY, BLE_DATA_LSB_AT_LOWER_ADDRESS,
                                              FS_SCALE_AT_PLUS_MINUS_16G, HR_HI_RES_ENABLED, SIM_SERIAL_INTERFACE_4_WIRE ); //0000000000111000
};

int main ( void ) {
    using namespace I2C;

    LSM303_Accelerometer *Accelerometer;

    Accelerometer = new LSM303_Accelerometer( ACCEL_ADDRESS, 1 );

    cout << "Power Settings = " << bitset<16>( Accelerometer->PowerSettings ) << endl;
    cout << "HighPass Settings = " << bitset<16>( Accelerometer->HighPassSettings ) << endl;
    cout << "Int1 Settings = " << bitset<16>( Accelerometer->Int1Settings ) << endl;
    cout << "Resolution and Scale Settings = " << bitset<16>( Accelerometer->DataSettings ) << endl;

}