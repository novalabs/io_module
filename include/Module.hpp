#pragma once

#include <core/mw/CoreModule.hpp>
#include <modules/io/include/io/ModuleConfiguration.hpp>

namespace core {
namespace hw {
class Pad;
class SPIDevice;
class EXTChannel;
}
}

class Module:
	public core::mw::CoreModule
{
public:
	static bool
	initialize();

	static core::hw::Pad& d0;
	static core::hw::Pad& d1;
	static core::hw::Pad& d2;
	static core::hw::Pad& d3;
	static core::hw::Pad& d4;
	static core::hw::Pad& d5;
	static core::hw::Pad& d6;
	static core::hw::Pad& d7;

	static core::hw::SPIDevice& spi;
	//static core::hw::EXTChannel& ext;

	Module();
	virtual ~Module() {}
};

