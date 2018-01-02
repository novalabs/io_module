/* COPYRIGHT (c) 2016-2018 Nova Labs SRL
 *
 * All rights reserved. All use of this software and documentation is
 * subject to the License Agreement located in the file LICENSE.
 */

#include <core/snippets/CortexMxFaultHandlers.h>

#include <core/mw/Middleware.hpp>
#include <core/mw/transport/RTCANTransport.hpp>

#include <core/hw/EXT.hpp>
#include <core/hw/GPIO.hpp>
#include <core/hw/SPI.hpp>
#include <core/hw/I2C.hpp>
#include <core/hw/SD.hpp>
#include <core/hw/IWDG.hpp>
#include <core/os/Thread.hpp>

#include <Module.hpp>

// LED
using LED_PAD = core::hw::Pad_<core::hw::GPIO_F, LED_PIN>;
static LED_PAD _led;

// DIGITAL I/O
static core::hw::Pad_<core::hw::GPIO_A, 0> _d0;
static core::hw::Pad_<core::hw::GPIO_A, 1> _d1;
static core::hw::Pad_<core::hw::GPIO_A, 2> _d2;
static core::hw::Pad_<core::hw::GPIO_A, 3> _d3;
static core::hw::Pad_<core::hw::GPIO_B, 4> _d4;
static core::hw::Pad_<core::hw::GPIO_B, 5> _d5;
static core::hw::Pad_<core::hw::GPIO_B, 0> _d6;
static core::hw::Pad_<core::hw::GPIO_A, 6> _d7;

// EXT
static core::hw::EXTController_<core::hw::EXT_1> _ext;

// SPI
using PAD_CS = core::hw::Pad_<core::hw::GPIO_B, 12>;
static core::hw::SPIDevice_<core::hw::SPI_2, PAD_CS> _spi;

// I2C
static core::hw::I2CMaster_<core::hw::I2C_2> _i2c;

// SERIAL1
using SD_1_STREAM = core::os::SDChannelTraits<core::hw::SD_1>;
using SERIAL1     = core::os::IOChannel_<SD_1_STREAM, core::os::IOChannel::DefaultTimeout::INFINITE>;
static SERIAL1 _serial1;

// SERIAL2
using SD_3_STREAM = core::os::SDChannelTraits<core::hw::SD_3>;
using SERIAL3     = core::os::IOChannel_<SD_3_STREAM, core::os::IOChannel::DefaultTimeout::INFINITE>;
static SERIAL3 _serial3;

// MODULE DEVICES
core::hw::Pad& Module::d0 = _d0;
core::hw::Pad& Module::d1 = _d1;
core::hw::Pad& Module::d2 = _d2;
core::hw::Pad& Module::d3 = _d3;
core::hw::Pad& Module::d4 = _d4;
core::hw::Pad& Module::d5 = _d5;
core::hw::Pad& Module::d6 = _d6;
core::hw::Pad& Module::d7 = _d7;
core::hw::EXTController& Module::ext = _ext;
core::hw::SPIDevice&     Module::spi = _spi;
core::hw::I2CMaster&     Module::i2c = _i2c;
core::os::IOChannel&     Module::u1  = _serial1;
core::os::IOChannel&     Module::u2  = _serial3;


// SYSTEM STUFF
static core::os::Thread::Stack<1024> management_thread_stack;
static core::mw::RTCANTransport      rtcantra(&RTCAND1);

RTCANConfig rtcan_config = {
    1000000, 100, 60
};


Module::Module()
{}

bool
Module::initialize()
{
#ifdef _DEBUG
    FAULT_HANDLERS_ENABLE(true);
#else
    FAULT_HANDLERS_ENABLE(false);
#endif

    static bool initialized = false;

    if (!initialized) {
        core::mw::CoreModule::initialize();

        core::mw::Middleware::instance().initialize(name(), management_thread_stack, management_thread_stack.size(), core::os::Thread::LOWEST);
        rtcantra.initialize(rtcan_config, canID());
        core::mw::Middleware::instance().start();

        initialized = true;
    }

    return initialized;
} // Board::initialize

// ----------------------------------------------------------------------------
// CoreModule STM32FlashConfigurationStorage
// ----------------------------------------------------------------------------
#include <core/snippets/CoreModuleSTM32FlashConfigurationStorage.hpp>
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// CoreModule HW specific implementation
// ----------------------------------------------------------------------------
#include <core/snippets/CoreModuleHWSpecificImplementation.hpp>
// ----------------------------------------------------------------------------
