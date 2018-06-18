/**
 * \file    port_manager.c
 * \author  MBorregoTrujillo
 * \date    08-March-2018
 * \brief   Configures the pins of the MCU
 */
#include "port_manager.h"

/**
 * \brief Macro to select specific bit
 */
#define SELECT_BIT(reg, bit)    ((reg & (1 << bit)) >> bit)

/**
 * \brief Pin configuration, i/o or peripheral
 */
#define PINCFG_IO           (0u)
#define PINCFG_PERIPHERAL   (1u)

/**
 * \brief Set of macros to configure specific I/O PIN
 *
 *                               DIR INEN PULLEN OUT
 *  IO_INPUT_DIGITAL_DISABLED     0    0    0     0
 *  IO_INPUT_DISABLED_PULLDOWN    0    0    1     0
 *  IO_INPUT_DISABLED_PULLUP      0    0    1     1
 *  IO_INPUT_DEFAULT              0    1    0     0
 *  IO_INPUT_PULLDOWN             0    1    1     0
 *  IO_INPUT_PULLUP               0    1    1     1
 *
 *  IO_OUTPUT_DEFAULT             1    0    0     X
 *  IO_OUTPUT_WITH_PULL           1    0    1     X
 *  IO_OUTPUT_READBACK            1    1    0     X
 *  IO_OUTPUT_WITH_PULL_READBACK  1    1    1     X
 */
#define IO_INPUT_DIGITAL_DISABLED          (0u)
#define IO_INPUT_DISABLED_PULLDOWN         (2u)
#define IO_INPUT_DISABLED_PULLUP           (3u)
#define IO_INPUT_DEFAULT                   (4u)
#define IO_INPUT_PULLDOWN                  (6u)
#define IO_INPUT_PULLUP                    (7u)

#define IO_OUTPUT_DEFAULT_LOW              (8u)
#define IO_OUTPUT_DEFAULT_HIGH             (9u)
#define IO_OUTPUT_WITH_PULL_LOW            (10u)
#define IO_OUTPUT_WITH_PULL_HIGH           (11u)
#define IO_OUTPUT_READBACK_LOW             (12u)
#define IO_OUTPUT_READBACK_HIGH            (13u)
#define IO_OUTPUT_WITH_PULL_READBACK_LOW   (14u)
#define IO_OUTPUT_WITH_PULL_READBACK_HIGH  (15u)


typedef struct pin_cfg {
    uint32_t pinid  : 8;    /* Pin configuration PA(0..31), PB(32..63) */
    uint32_t pincfg : 1;    /* 0-I/O, 1-Peripheral */
    uint32_t iocfg  : 4;    /* I/O configuration */
    uint32_t muxcfg : 4;    /* MUX peripheral configuration */
} T_pin_cfg;

/** Prototype declaration */
static void port_manager_config(const T_pin_cfg* pin);
static void port_manager_config_sleep(uint32_t pinid);

/* OLED_SDA */
const T_pin_cfg pin_oled_sda = {
    .pinid = PIN_PA04,
    .pincfg = PINCFG_PERIPHERAL,
    .iocfg = IO_INPUT_DEFAULT,
    .muxcfg = MUX_PA04D_SERCOM0_PAD0,
};
/* OLED_SCL */
const T_pin_cfg pin_oled_scl = {
    .pinid = PIN_PA05,
    .pincfg = PINCFG_PERIPHERAL,
    .iocfg = IO_INPUT_DEFAULT,
    .muxcfg = MUX_PA05D_SERCOM0_PAD1,
};
/* OLED_RES */
const T_pin_cfg pin_oled_res = {
    .pinid = PIN_PA06,
    .pincfg = PINCFG_IO,
    .iocfg = IO_OUTPUT_DEFAULT_LOW,
    .muxcfg = 0,
};

/* LED1 */
const T_pin_cfg pin_led1 = {
    .pinid = PIN_PB22,
    .pincfg = PINCFG_IO,
    .iocfg = IO_OUTPUT_DEFAULT_HIGH,
    .muxcfg = 0,
};
/* LED2 */
const T_pin_cfg pin_led2 = {
    .pinid = PIN_PB23,
    .pincfg = PINCFG_IO,
    .iocfg = IO_OUTPUT_DEFAULT_HIGH,
    .muxcfg = 0,
};

/**
 * \fn      port_manager_init
 * \brief   Initializes MCU Port configuration
 */
void port_manager_init(void){
    port_manager_config(&pin_oled_sda);
    port_manager_config(&pin_oled_scl);
    port_manager_config(&pin_oled_res);
    port_manager_config(&pin_led1);
    port_manager_config(&pin_led2);
}

/**
 * \fn      port_manager_deinit
 * \brief   de-initialize MCU Port configuration to enter sleep
 */
void port_manager_deinit(void){

    // I2C Init
    port_manager_config_sleep(pin_oled_sda.pinid);
    port_manager_config_sleep(pin_oled_scl.pinid);
    port_manager_config_sleep(pin_oled_res.pinid);
    port_manager_config_sleep(pin_led1.pinid);
    port_manager_config_sleep(pin_led2.pinid);
}

/**
 * \fn      port_manager_config
 * \brief   Configures an specific Mcu pin based on pin
 *          configuration parameter
 * \param   pin     Pointer to pin configuration
 */
static void port_manager_config(const T_pin_cfg* pin){
    PORT_WRCONFIG_Type wrconfig_tmp;
    uint32_t pinmask;
    uint8_t groupid;
    uint8_t pinid;

    /* Initialize Internal vars */
    groupid = pin->pinid / 32;
    pinid = pin->pinid % 32;
    pinmask = (1UL << pinid);

    /* use WRCONFIG to configure PMUX and PINCFG */
    wrconfig_tmp.bit.DRVSTR = 0;
    wrconfig_tmp.bit.PMUXEN = pin->pincfg;
    wrconfig_tmp.bit.PULLEN = SELECT_BIT(pin->iocfg, 1);
    wrconfig_tmp.bit.INEN = SELECT_BIT(pin->iocfg, 2);
    wrconfig_tmp.bit.WRPINCFG = 1;

    wrconfig_tmp.bit.PMUX = pin->muxcfg;
    wrconfig_tmp.bit.WRPMUX = 1;

    if(pinid < 16){
        wrconfig_tmp.bit.PINMASK = (uint16_t)(1 << pinid);
        wrconfig_tmp.bit.HWSEL = 0;
    } else{
        wrconfig_tmp.bit.PINMASK = (uint16_t)(1 << (pinid-16));
        wrconfig_tmp.bit.HWSEL = 1;
    }

    /* Clear Dir before configuring */
    PORT->Group[groupid].DIRCLR.reg = pinmask;

    /* Write Configuration to update PMUX and PINCFG */
    PORT->Group[groupid].WRCONFIG.reg = wrconfig_tmp.reg;

    /* DIR */
    if(SELECT_BIT(pin->iocfg, 3)){
        PORT->Group[groupid].DIRSET.reg = pinmask;
    } else{
        PORT->Group[groupid].DIRCLR.reg = pinmask;
    }
    /* OUT */
    if(SELECT_BIT(pin->iocfg, 0)){
        PORT->Group[groupid].OUTSET.reg = pinmask;
    } else{
        PORT->Group[groupid].OUTCLR.reg = pinmask;
    }

}

/**
 * \fn      port_manager_config_sleep
 * \brief   Configures an specific Mcu pin to sleep
 * \param   pin     Pointer to pin configuration
 */
static void port_manager_config_sleep(uint32_t pinid){
    T_pin_cfg pin_sleep_cfg = {
        .pinid = pinid,
        .pincfg = PINCFG_IO,
        .iocfg = IO_INPUT_DEFAULT,
        .muxcfg = 0,
    };

    port_manager_config(&pin_sleep_cfg);
}


