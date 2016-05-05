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

    unsigned short PowerSettings = SET_CTRL_REG1_A( ODR_400HZ,
                                                    LP_LOW_POWER_DISABLED,
                                                    Z_AXIS_ENABLED,
                                                    Y_AXIS_ENABLED,
                                                    X_AXIS_ENABLED );

    unsigned short HighPassSettings = SET_CTRL_REG2_A( HIGHPASS_MODE_NORMAL_WITH_RESET,
                                                       HIGHPASS_FDS_INTERNAL_BYPASSED_DISABLED,
                                                       HIGHPASS_FILTER_DISABLED_FOR_CLICK,
                                                       HIGHPASS_FILTER_DISABLED_AOI_INT2,
                                                       HIGHPASS_FILTER_DISABLED_AOI_INT1 );

    unsigned short Int1Settings = SET_CTRL_REG3_A( CLICK_INTERRUPT_ON_INT1_DISABLED,
                                                   AOI1_INTERRUPT_ON_INT1_DISABLED,
                                                   AOI2_INTERRUPT_ON_INT1_DISABLED,
                                                   DRDY1_INTERRUPT_ON_INT1_DISABLED,
                                                   DRDY2_INTERRUPT_ON_INT1_DISABLED,
                                                   FIFO_WTM_INTERRUPT_ON_INT1_DISABLED,
                                                   FIFO_OVERRUN_INTERRUPT_ON_INT1_DISABLED );

    unsigned short DataSettings = SET_CTRL_REG4_A( BDU_UPDATE_REGISTERS_CONTINUOUSLY,
                                                   BLE_DATA_LSB_AT_LOWER_ADDRESS,
                                                   FS_SCALE_AT_PLUS_MINUS_16G,
                                                   HR_HI_RES_ENABLED,
                                                   SIM_SERIAL_INTERFACE_4_WIRE );

    unsigned short MemorySettings = SET_CTRL_REG5_A( BOOT_REBOOT_MEM_CONTENT_DISABLED,
                                                     FIFO_DISABLED,
                                                     LIR_INT1_NOT_LATCHED,
                                                     D4D_INT1_4D_DISABLED,
                                                     LIR_INT2_NOT_LATCHED,
                                                     D4D_INT2_4D_DISABLED);

    unsigned short InterruptSettings = SET_CTRL6_REG_A( I2_CLICK_INTERRUPT_ON_PAD2_DISABLED,
                                                        I2_INTERRUPT_1_DISABLED,
                                                        I2_INTERRUPT_2_DISABLED,
                                                        BOOT_I1_REBOOT_MEMORY_DISABLED,
                                                        P2_ACT_ACTIVE_FUNCTION_ON_PAD2_DISABLED,
                                                        H_LACTIVE_INTERRUPT_ACTIVE_HIGH );

    unsigned short FIFOSettings = SET_FIFO_CTRL_REG_A( FM_BYPASS_MODE,
                                                       TR_TRIGGER_LINKED_TO_INTERRUPT2 );

    unsigned short Interrupt1CFGSettings = SET_INT1_CFG_A( AOI_OR_COMBINATION,
                                                           ZHIE_INTERRUPT_ON_Z_HIGH_DISABLED,
                                                           ZLIE_INTERRUPT_ON_Z_LOW_DISABLED,
                                                           YHIE_INTERRUPT_ON_Y_HIGH_DISABLED,
                                                           YLIE_INTERRUPT_ON_Y_LOW_DISABLED,
                                                           XHIE_INTERRUPT_ON_X_HIGH_DISABLED,
                                                           XLIE_INTERRUPT_ON_X_LOW_DISABLED );

    unsigned short Interrupt2CFGSettings = SET_INT2_CFG_A( AOI_OR_COMBINATION,
                                                           ZHIE_INTERRUPT_ON_Z_HIGH_DISABLED,
                                                           ZLIE_INTERRUPT_ON_Z_LOW_DISABLED,
                                                           YHIE_INTERRUPT_ON_Y_HIGH_DISABLED,
                                                           YLIE_INTERRUPT_ON_Y_LOW_DISABLED,
                                                           XHIE_INTERRUPT_ON_X_HIGH_DISABLED,
                                                           XLIE_INTERRUPT_ON_X_LOW_DISABLED );

    unsigned short ClickCFGSettings = SET_CLICK_CFG_A( ZD_DOUBLECLICK_ON_Z_AXIS_DISABLED,
                                                       ZS_SINGLECLICK_ON_Z_AXIS_DISABLED,
                                                       YD_DOUBLECLICK_ON_Y_AXIS_DISABLED,
                                                       YS_SINGLECLICK_ON_Y_AXIS_DISABLED,
                                                       XD_DOUBLECLICK_ON_X_AXIS_DISABLED,
                                                       XS_SINGLECLICK_ON_X_AXIS_DISABLED );

    unsigned short ClickSRCSettings = SET_CLICK_SRC_A( DCLICK_DOUBLE_CLICK_DETECTION_DISABLED,
                                                       SCLICK_SINGLE_CLICK_DETECTION_DISABLED,
                                                       SIGN_POSITIVE_DETECTION );

    /*Settings for magnetometer
    unsigned short MagnetometerDataRate = SET_CRA_REG_M( TEMP_ENABLED,
                                                         DO2_220Hz );

    unsigned short GaussSettings = SET_CRB_REG_M( GAIN_RANGE_1_3_GAIN_X_Y_Z_1100_GAIN_Z_980 );

    unsigned short OperatingMode = SET_MR_REG_M( MD_CONTINUOUS_CONVERSION_MODE );
     */
};

int main ( void ) {
    using namespace I2C;

    LSM303_Accelerometer *Accelerometer;

    Accelerometer = new LSM303_Accelerometer( ACCEL_ADDRESS, 1 );

    /*Set accelerometer power configuration*/
    Accelerometer->SetRegisterAddress( CTRL_REG1_A );
    Accelerometer->SetRegisterValue( Accelerometer->PowerSettings );
    Accelerometer->WriteToDevice( 2 );
    cout << "Power Settings = " << bitset<16>( Accelerometer->PowerSettings ) << endl;
    /*End of power configuration*/

    /*Set high pass configuration*/
    Accelerometer->SetRegisterAddress( CTRL_REG2_A );
    Accelerometer->SetRegisterValue( Accelerometer->HighPassSettings );
    Accelerometer->WriteToDevice( 2 );
    cout << "HighPass Settings = " << bitset<16>( Accelerometer->HighPassSettings ) << endl;
    /*End of high pass configuration*/

    /*Set interrupt 1 configuration*/
    Accelerometer->SetRegisterAddress( CTRL_REG3_A );
    Accelerometer->SetRegisterValue( Accelerometer->Int1Settings );
    Accelerometer->WriteToDevice( 2 );
    cout << "Int1 Settings = " << bitset<16>( Accelerometer->Int1Settings ) << endl;
    /*End of interrupt 1 configuration*/

    /*Set range/resolution configuration*/
    Accelerometer->SetRegisterAddress( CTRL_REG4_A );
    Accelerometer->SetRegisterValue( Accelerometer->DataSettings );
    Accelerometer->WriteToDevice( 2 );
    cout << "Resolution and Scale Settings = " << bitset<16>( Accelerometer->DataSettings ) << endl;
    /*End of power configuration*/

    /*Set FIFO configuration*/
    Accelerometer->SetRegisterAddress( CTRL_REG5_A );
    Accelerometer->SetRegisterValue( Accelerometer->MemorySettings );
    Accelerometer->WriteToDevice( 2 );
    cout << "Memory Settings = " << bitset<16>( Accelerometer->MemorySettings ) << endl;
    /*End of power configuration*/

    /*Set click interrupt configuration*/
    Accelerometer->SetRegisterAddress( CTRL_REG6_A );
    Accelerometer->SetRegisterValue( Accelerometer->InterruptSettings );
    Accelerometer->WriteToDevice( 2 );
    cout << "Interrupt Settings = " << bitset<16>( Accelerometer->InterruptSettings ) << endl;
    /*End of power configuration*/

    /*Set FIFO mode configuration*/
    Accelerometer->SetRegisterAddress( FIFO_CTRL_REG_A );
    Accelerometer->SetRegisterValue( Accelerometer->FIFOSettings );
    Accelerometer->WriteToDevice( 2 );
    cout << "FIFO Settings = " << bitset<16>( Accelerometer->FIFOSettings ) << endl;
    /*End of power configuration*/

    /*Set Interrupt 1 configuration*/
    Accelerometer->SetRegisterAddress( INT1_CFG_A );
    Accelerometer->SetRegisterValue( Accelerometer->Interrupt1CRGSettings );
    Accelerometer->WriteToDevice( 2 );
    cout << "Interrupt1 CFG Settings = " << bitset<16>( Accelerometer->Interrupt1CFGSettings ) << endl;
    /*End of power configuration*/

    /*Set Interrupt 2 configuration*/
    Accelerometer->SetRegisterAddress( INT2_CFG_A );
    Accelerometer->SetRegisterValue( Accelerometer->Interrupt2CFGSettings );
    Accelerometer->WriteToDevice( 2 );
    cout << "Interrupt2 CFG Settings = " << bitset<16>( Accelerometer->Interrupt2CFGSettings ) << endl;
    /*End of power configuration*/

    /*Set Interrupt on Click configuration*/
    Accelerometer->SetRegisterAddress( CLICK_CFG_A );
    Accelerometer->SetRegisterValue( Accelerometer->ClickCFGSettings );
    Accelerometer->WriteToDevice( 2 );
    cout << "Click CFG Settings = " << bitset<16>( Accelerometer->ClickCFGSettings ) << endl;
    /*End of power configuration*/

    /*Set Interrupt on Double Click configuration*/
    Accelerometer->SetRegisterAddress( CLICK_SRC_A );
    Accelerometer->SetRegisterValue( Accelerometer->ClickSRCSettings );
    Accelerometer->WriteToDevice( 2 );
    cout << "Click SRC Settings = " << bitset<16>( Accelerometer->ClickSRCSettings ) << endl;
    /*End of power configuration*/

    /* Magnetometer Settings
    //Set data rate configuration
    Accelerometer->SetRegisterAddress( CRA_REG_M );
    Accelerometer->SetRegisterValue( Accelerometer->MagnetometerDataRate );
    Accelerometer->WriteToDevice( 2 );
    cout << "Magnetometer Settings = " << bitset<16>( Accelerometer->MagnetometerDataRate ) << endl;
    //End of power configuration

    //Set high pass configuration
    Accelerometer->SetRegisterAddress( CRB_REG_M );
    Accelerometer->SetRegisterValue( Accelerometer->GaussSettings );
    Accelerometer->WriteToDevice( 2 );
    cout << "Magnetometer Gauss Settings = " << bitset<16>( Accelerometer->GaussSettings ) << endl;
    //End of power configuration

    //Set high pass configuration
    Accelerometer->SetRegisterAddress( MR_REG_M );
    Accelerometer->SetRegisterValue( Accelerometer->OperatingMode );
    Accelerometer->WriteToDevice( 2 );
    cout << "Magnetometer Operating Mode = " << bitset<16>( Accelerometer->OperatingMode ) << endl;
    //End of power configuration
     */
}