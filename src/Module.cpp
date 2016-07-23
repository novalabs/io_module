/* COPYRIGHT (c) 2016 Nova Labs SRL
 *
 * All rights reserved. All use of this software and documentation is
 * subject to the License Agreement located in the file LICENSE.
 */

#include <core/mw/Middleware.hpp>

#include "ch.h"
#include "hal.h"

#include <core/hw/EXT.hpp>
#include <core/hw/GPIO.hpp>
#include <core/hw/SPI.hpp>
#include <core/os/Thread.hpp>
#include <Module.hpp>


using LED_PAD = core::hw::Pad_<core::hw::GPIO_F, GPIOF_LED>;
static LED_PAD _led;

static core::hw::Pad_<core::hw::GPIO_A, 0> _d0;
static core::hw::Pad_<core::hw::GPIO_A, 1> _d1;
static core::hw::Pad_<core::hw::GPIO_A, 2> _d2;
static core::hw::Pad_<core::hw::GPIO_A, 3> _d3;
static core::hw::Pad_<core::hw::GPIO_B, 4> _d4;
static core::hw::Pad_<core::hw::GPIO_B, 5> _d5;
static core::hw::Pad_<core::hw::GPIO_B, 0> _d6;
static core::hw::Pad_<core::hw::GPIO_A, 6> _d7;

using PAD_CS = core::hw::Pad_<core::hw::GPIO_B, 12>;
static core::hw::SPIDevice_<core::hw::SPI_2, PAD_CS> _spi;

static THD_WORKING_AREA(wa_info, 1024);
static core::mw::RTCANTransport rtcantra(RTCAND1);

core::hw::Pad& Module::d0 = _d0;
core::hw::Pad& Module::d1 = _d1;
core::hw::Pad& Module::d2 = _d2;
core::hw::Pad& Module::d3 = _d3;
core::hw::Pad& Module::d4 = _d4;
core::hw::Pad& Module::d5 = _d5;
core::hw::Pad& Module::d6 = _d6;
core::hw::Pad& Module::d7 = _d7;

core::hw::SPIDevice& Module::spi = _spi;

RTCANConfig rtcan_config = {
	1000000, 100, 60
};

#ifndef core_MODULE_NAME
#define core_MODULE_NAME "IO"
#endif

core::mw::Middleware core::mw::Middleware::instance(core_MODULE_NAME, "BOOT_" core_MODULE_NAME);

static EXTConfig extcfg = {   {
                                 {EXT_CH_MODE_DISABLED, NULL},
                                 {EXT_CH_MODE_DISABLED, NULL},
                                 {EXT_CH_MODE_DISABLED, NULL},
                                 {EXT_CH_MODE_DISABLED, NULL},
                                 {EXT_CH_MODE_DISABLED, NULL},
                                 {EXT_CH_MODE_DISABLED, NULL},
                                 {EXT_CH_MODE_DISABLED, NULL},
                                 {EXT_CH_MODE_DISABLED, NULL},
                                 {EXT_CH_MODE_DISABLED, NULL},
                                 {EXT_CH_MODE_DISABLED, NULL},
                                 {EXT_CH_MODE_DISABLED, NULL},
                                 {EXT_CH_MODE_DISABLED, NULL},
                                 {EXT_CH_MODE_DISABLED, NULL},
                                 {EXT_CH_MODE_DISABLED, NULL},
                                 {EXT_CH_MODE_DISABLED, NULL}
                              }};

Module::Module()
{}

bool
Module::initialize()
{
//	core_ASSERT(core::mw::Middleware::instance.is_stopped()); // TODO: capire perche non va...

	static bool initialized = false;

	if (!initialized) {
		halInit();
		chSysInit();

		core::mw::Middleware::instance.initialize(wa_info, sizeof(wa_info), core::os::Thread::LOWEST);
		rtcantra.initialize(rtcan_config);
		core::mw::Middleware::instance.start();

		extStart(&EXTD1, &extcfg);


		initialized = true;
	}

	return initialized;
} // Board::initialize

// Leftover from coreBoard (where LED_PAD cannot be defined
void
core::mw::CoreModule::Led::toggle()
{
	_led.toggle();
}

void
core::mw::CoreModule::Led::write(
		unsigned on
)
{
	_led.write(on);
}
