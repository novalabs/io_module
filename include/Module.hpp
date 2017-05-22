/* COPYRIGHT (c) 2016-2017 Nova Labs SRL
 *
 * All rights reserved. All use of this software and documentation is
 * subject to the License Agreement located in the file LICENSE.
 */

#pragma once

#include <core/mw/CoreModule.hpp>
#include <ModuleConfiguration.hpp>
#include <core/os/IOChannel.hpp>


namespace core {
namespace hw {
class Pad;
class SPIDevice;
class I2CMaster;
class EXTController;
}
}

class Module:
    public core::mw::CoreModule
{
public:
// --- DEVICES ----------------------------------------------------------------
    static core::hw::Pad& d0;
    static core::hw::Pad& d1;
    static core::hw::Pad& d2;
    static core::hw::Pad& d3;
    static core::hw::Pad& d4;
    static core::hw::Pad& d5;
    static core::hw::Pad& d6;
    static core::hw::Pad& d7;

    static core::hw::EXTController& ext;

    static core::hw::SPIDevice& spi;
    static core::hw::I2CMaster& i2c;

    static core::os::IOChannel& u1;
    static core::os::IOChannel& u2;
// ----------------------------------------------------------------------------

    static bool
    initialize();


    Module();
    virtual ~Module() {}
};
