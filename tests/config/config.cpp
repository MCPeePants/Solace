#include <cassert>

#include "config/config.h"

int main()
{
	using Config::Config;
	Config config("config.lua");
	
	assert(config.get("nonExistant", "default") == "default");
	
	assert(config["bool"].boolean() == true);
	assert(config["str"].string() == "test");
	assert(config["int"].integer() == 10);
	assert(config["float"].number() == 5.5);
	
	Config tbl = config.getSub("tbl");
	assert(tbl["test"].string() == "Hello, world!");
}
