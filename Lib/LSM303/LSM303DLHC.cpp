//
// Created by Michael Brookes on 05/05/2016.
//

#include "./LSM303DLHC.h"

using namespace I2C;

void LSM303DLHC::LoadRecommendedFlightSettings( ) {
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

uint8_t LSM303DLHC::CommitSetting( uint8_t RegisterAddress, uint8_t RegisterValue ){
    this->SetRegisterAddress( RegisterAddress );
    this->SetRegisterValue( RegisterValue );
    this->WriteToDevice( 2 );
    return RegisterValue;
}