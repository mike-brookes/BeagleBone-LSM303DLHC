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
    unsigned short PowerSettings = SET_CTRL_REG1_A( ODR_400HZ, LP_LOW_POWER_DISABLED,
                                                    Z_AXIS_ENABLED,
                                                    Y_AXIS_ENABLED,
                                                    X_AXIS_ENABLED ); //0b0000000001110111

    unsigned short HighPassSettings = SET_CTRL_REG2_A( HIGHPASS_MODE_NORMAL_WITH_RESET, HIGHPASS_FDS_INTERNAL_BYPASSED_DISABLED,
                                                       HIGHPASS_FILTER_DISABLED_FOR_CLICK, HIGHPASS_FILTER_DISABLED_AOI_INT2,
                                                       HIGHPASS_FILTER_DISABLED_AOI_INT1 ); //0b0000000000000000

    unsigned short Int1Settings = SET_CTRL_REG3_A( CLICK_INTERRUPT_ON_INT1_DISABLED, AOI1_INTERRUPT_ON_INT1_DISABLED,
                                                   AOI2_INTERRUPT_ON_INT1_DISABLED, DRDY1_INTERRUPT_ON_INT1_DISABLED,
                                                   DRDY2_INTERRUPT_ON_INT1_DISABLED, FIFO_WTM_INTERRUPT_ON_INT1_DISABLED,
                                                   FIFO_OVERRUN_INTERRUPT_ON_INT1_DISABLED ); //0b0000000000000000

    unsigned short DataSettings = SET_CTRL_REG4_A( BDU_UPDATE_REGISTERS_CONTINUOUSLY, BLE_DATA_LSB_AT_LOWER_ADDRESS,
                                                   FS_SCALE_AT_PLUS_MINUS_16G, HR_HI_RES_ENABLED, SIM_SERIAL_INTERFACE_4_WIRE ); //0000000000111000

    unsigned short MemorySettings = SET_CTRL_REG5_A( BOOT_REBOOT_MEM_CONTENT_DISABLED, FIFO_DISABLED,
                                                     LIR_INT1_NOT_LATCHED, D4D_INT1_4D_DISABLED, LIR_INT2_NOT_LATCHED,
                                                     D4D_INT2_4D_DISABLED); //0b0000000000000000

    unsigned short InterruptSettings = SET_CTRL6_REG_A( I2_CLICK_INTERRUPT_ON_PAD2_DISABLED, I2_INTERRUPT_1_DISABLED,
                                                        I2_INTERRUPT_2_DISABLED, BOOT_I1_REBOOT_MEMORY_DISABLED,
                                                        P2_ACT_ACTIVE_FUNCTION_ON_PAD2_DISABLED, H_LACTIVE_INTERRUPT_ACTIVE_HIGH ); //0b0000000000000000

    unsigned short FIFOSettings = SET_FIFO_CTRL_REG_A( FM_BYPASS_MODE, TR_TRIGGER_LINKED_TO_INTERRUPT1 );

    unsigned short Interrupt1CRGSettings = SET_INT1_CRG_A( AOI_OR_COMBINATION,
                                                           ZHIE_INTERRUPT_ON_Z_HIGH_DISABLED, ZLIE_INTERRUPT_ON_Z_LOW_DISABLED,
                                                           YHIE_INTERRUPT_ON_Y_HIGH_DISABLED, YLIE_INTERRUPT_ON_Y_LOW_DISABLED,
                                                           XHIE_INTERRUPT_ON_X_HIGH_DISABLED, XLIE_INTERRUPT_ON_X_LOW_DISABLED );

    unsigned short Interrupt2CRGSettings = SET_INT2_CRG_A( AOI_OR_COMBINATION,
                                                           ZHIE_INTERRUPT_ON_Z_HIGH_DISABLED, ZLIE_INTERRUPT_ON_Z_LOW_DISABLED,
                                                           YHIE_INTERRUPT_ON_Y_HIGH_DISABLED, YLIE_INTERRUPT_ON_Y_LOW_DISABLED,
                                                           XHIE_INTERRUPT_ON_X_HIGH_DISABLED, XLIE_INTERRUPT_ON_X_LOW_DISABLED );

    unsigned short ClickCFGSettings = SET_CLICK_CFG_A( ZD_DOUBLECLICK_ON_Z_AXIS_DISABLED, ZS_SINGLECLICK_ON_Z_AXIS_DISABLED,
                                                       YD_DOUBLECLICK_ON_Y_AXIS_DISABLED, YS_SINGLECLICK_ON_Y_AXIS_DISABLED,
                                                       XD_DOUBLECLICK_ON_X_AXIS_DISABLED, XS_SINGLECLICK_ON_X_AXIS_DISABLED );

    unsigned short ClickSRCSettings = SET_CLICK_SRC_A( DCLICK_DOUBLE_CLICK_DETECTION_DISABLED, SCLICK_SINGLE_CLICK_DETECTION_DISABLED,
                                                       SIGN_POSITIVE_DETECTION );

    unsigned short MagnetometerDataRate = SET_CRA_REG_M( TEMP_ENABLED, DO2_220Hz );

    unsigned short GaussSettings = SET_CRB_REG_M( GAIN_RANGE_1_3_GAIN_X_Y_Z_1100_GAIN_Z_980 );

    unsigned short OperatingMode = SET_MR_REG_M( MD_CONTINUOUS_CONVERSION_MODE );
};

int main ( void ) {
    using namespace I2C;

    LSM303_Accelerometer *Accelerometer;

    Accelerometer = new LSM303_Accelerometer( ACCEL_ADDRESS, 1 );

    cout << "Power Settings = " << bitset<16>( Accelerometer->PowerSettings ) << endl;
    cout << "HighPass Settings = " << bitset<16>( Accelerometer->HighPassSettings ) << endl;
    cout << "Int1 Settings = " << bitset<16>( Accelerometer->Int1Settings ) << endl;
    cout << "Resolution and Scale Settings = " << bitset<16>( Accelerometer->DataSettings ) << endl;
    cout << "Memory Settings = " << bitset<16>( Accelerometer->MemorySettings ) << endl;
    cout << "Interrupt Settings = " << bitset<16>( Accelerometer->InterruptSettings ) << endl;
    cout << "FIFO Settings = " << bitset<16>( Accelerometer->FIFOSettings ) << endl;
    cout << "Interrupt1 CRG Settings = " << bitset<16>( Accelerometer->Interrupt1CRGSettings ) << endl;
    cout << "Interrupt2 CRG Settings = " << bitset<16>( Accelerometer->Interrupt2CRGSettings ) << endl;
    cout << "Click CFG Settings = " << bitset<16>( Accelerometer->ClickCFGSettings ) << endl;
    cout << "Click SRC Settings = " << bitset<16>( Accelerometer->ClickSRCSettings ) << endl;
    cout << "Magnetometer Settings = " << bitset<16>( Accelerometer->MagnetometerDataRate ) << endl;
    cout << "Magnetometer Gauss Settings = " << bitset<16>( Accelerometer->GaussSettings ) << endl;
    cout << "Magnetometer Operating Mode = " << bitset<16>( Accelerometer->OperatingMode ) << endl;

}