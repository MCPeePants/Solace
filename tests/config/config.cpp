#include <cassert>
#include <string>

#include "config/config.h"

int main()
{
	using config::Config;
	Config conf("config/config.lua");

    assert(conf.get("nonExistant", "default") == "default");

	assert(conf["bool"].boolean() == true);
	assert(conf["str"].string() == "test");
	assert(conf["int"].integer() == 10);
	assert(conf["float"].number() == 5.5);

	Config tbl = conf.getSub("tbl");
	assert(tbl["test"].string() == "Hello, world!");
}
