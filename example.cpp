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
 *      added in a seperate project shortly...
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

    void LoadRecommendedFlightSettings( ) {
         this->PowerSettings =
                 this->CommitSetting(
                         CTRL_REG1_A,
                         SET_CTRL_REG1_A(
                                 ODR_400HZ,
                                 LP_LOW_POWER_DISABLED,
                                 Z_AXIS_ENABLED,
                                 Y_AXIS_ENABLED,
                                 X_AXIS_ENABLED
                         )
                 );

        this->HighPassSettings =
                this->CommitSetting(
                        CTRL_REG2_A,
                        SET_CTRL_REG2_A(
                                HIGHPASS_MODE_NORMAL_WITH_RESET,
                                HIGHPASS_FDS_INTERNAL_BYPASSED_DISABLED,
                                HIGHPASS_FILTER_DISABLED_FOR_CLICK,
                                HIGHPASS_FILTER_DISABLED_AOI_INT2,
                                HIGHPASS_FILTER_DISABLED_AOI_INT1
                        )
                );

        this->Int1Settings =
                this->CommitSetting(
                        CTRL_REG3_A,
                        SET_CTRL_REG3_A(
                                CLICK_INTERRUPT_ON_INT1_DISABLED,
                                AOI1_INTERRUPT_ON_INT1_DISABLED,
                                AOI2_INTERRUPT_ON_INT1_DISABLED,
                                DRDY1_INTERRUPT_ON_INT1_DISABLED,
                                DRDY2_INTERRUPT_ON_INT1_DISABLED,
                                FIFO_WTM_INTERRUPT_ON_INT1_DISABLED,
                                FIFO_OVERRUN_INTERRUPT_ON_INT1_DISABLED
                        )
        );

        this->DataSettings =
                this->CommitSetting(
                        CTRL_REG4_A,
                        SET_CTRL_REG4_A(
                                BDU_UPDATE_REGISTERS_CONTINUOUSLY,
                                BLE_DATA_LSB_AT_LOWER_ADDRESS,
                                FS_SCALE_AT_PLUS_MINUS_16G,
                                HR_HI_RES_ENABLED,
                                SIM_SERIAL_INTERFACE_4_WIRE
                        )
                );

        this->MemorySettings =
                this->CommitSetting(
                        CTRL_REG5_A,
                        SET_CTRL_REG5_A(
                                BOOT_REBOOT_MEM_CONTENT_DISABLED,
                                FIFO_DISABLED,
                                LIR_INT1_NOT_LATCHED,
                                D4D_INT1_4D_DISABLED,
                                LIR_INT2_NOT_LATCHED,
                                D4D_INT2_4D_DISABLED
                        )
                );

        this->InterruptSettings =
                this->CommitSetting(
                        CTRL_REG6_A,
                        SET_CTRL6_REG_A(
                                I2_CLICK_INTERRUPT_ON_PAD2_DISABLED,
                                I2_INTERRUPT_1_DISABLED,
                                I2_INTERRUPT_2_DISABLED,
                                BOOT_I1_REBOOT_MEMORY_DISABLED,
                                P2_ACT_ACTIVE_FUNCTION_ON_PAD2_DISABLED,
                                H_LACTIVE_INTERRUPT_ACTIVE_HIGH
                        )
                );

        this->FIFOSettings =
                this->CommitSetting(
                        FIFO_CTRL_REG_A,
                        SET_FIFO_CTRL_REG_A(
                                FM_BYPASS_MODE,
                                TR_TRIGGER_LINKED_TO_INTERRUPT2
                        )
                );

        this->Interrupt1CFGSettings =
                this->CommitSetting(
                        INT1_CFG_A,
                        SET_INT1_CFG_A(
                                AOI_OR_COMBINATION,
                                ZHIE_INTERRUPT_ON_Z_HIGH_DISABLED,
                                ZLIE_INTERRUPT_ON_Z_LOW_DISABLED,
                                YHIE_INTERRUPT_ON_Y_HIGH_DISABLED,
                                YLIE_INTERRUPT_ON_Y_LOW_DISABLED,
                                XHIE_INTERRUPT_ON_X_HIGH_DISABLED,
                                XLIE_INTERRUPT_ON_X_LOW_DISABLED
                        )
                );

        this->Interrupt2CFGSettings =
                this->CommitSetting(
                        INT2_CFG_A,
                        SET_INT2_CFG_A(
                                AOI_OR_COMBINATION,
                                ZHIE_INTERRUPT_ON_Z_HIGH_DISABLED,
                                ZLIE_INTERRUPT_ON_Z_LOW_DISABLED,
                                YHIE_INTERRUPT_ON_Y_HIGH_DISABLED,
                                YLIE_INTERRUPT_ON_Y_LOW_DISABLED,
                                XHIE_INTERRUPT_ON_X_HIGH_DISABLED,
                                XLIE_INTERRUPT_ON_X_LOW_DISABLED
                        )

                );

        this->ClickCFGSettings =
                this->CommitSetting(
                        CLICK_CFG_A,
                        SET_CLICK_CFG_A(
                                ZD_DOUBLECLICK_ON_Z_AXIS_DISABLED,
                                ZS_SINGLECLICK_ON_Z_AXIS_DISABLED,
                                YD_DOUBLECLICK_ON_Y_AXIS_DISABLED,
                                YS_SINGLECLICK_ON_Y_AXIS_DISABLED,
                                XD_DOUBLECLICK_ON_X_AXIS_DISABLED,
                                XS_SINGLECLICK_ON_X_AXIS_DISABLED
                        )
                );

        this->ClickSRCSettings =
                this->CommitSetting(
                        CLICK_SRC_A,
                        SET_CLICK_SRC_A(
                                DCLICK_DOUBLE_CLICK_DETECTION_DISABLED,
                                SCLICK_SINGLE_CLICK_DETECTION_DISABLED,
                                SIGN_POSITIVE_DETECTION
                        )
                );

    }

    uint8_t GetPowerSettings( ){ return this->PowerSettings; }
    uint8_t GetHighPassSettings( ){ return this->HighPassSettings; }
    uint8_t GetInt1Settings( ){ return this->Int1Settings; }
    uint8_t GetDataSettings( ){ return this->DataSettings; }
    uint8_t GetMemorySettings( ){ return this->MemorySettings; }
    uint8_t GetInterruptSettings( ){ return this->InterruptSettings; }
    uint8_t GetFIFOSettings( ){ return this->FIFOSettings; }
    uint8_t GetInterrupt1CFGSettings( ){ return this->Interrupt1CFGSettings; }
    uint8_t GetInterrupt2CFGSettings( ){ return this->Interrupt2CFGSettings; }
    uint8_t GetClickCFGSettings( ){ return this->ClickCFGSettings; }
    uint8_t GetClickSRCSettings( ){ return this->ClickSRCSettings; }

private:

    uint8_t CommitSetting( uint8_t RegisterAddress, uint8_t RegisterValue ){
        this->SetRegisterAddress( RegisterAddress );
        this->SetRegisterValue( RegisterValue );
        this->WriteToDevice( 2 );
        return RegisterValue;
    }

    uint8_t PowerSettings;
    uint8_t HighPassSettings;
    uint8_t Int1Settings;
    uint8_t DataSettings;
    uint8_t MemorySettings;
    uint8_t InterruptSettings;
    uint8_t FIFOSettings;
    uint8_t Interrupt1CFGSettings;
    uint8_t Interrupt2CFGSettings;
    uint8_t ClickCFGSettings;
    uint8_t ClickSRCSettings;
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