
#pragma once
#include <string>
#include <fstream>

namespace game {

    const static std::string log = "./log/game.log";
    const static std::string graphics = "./.resources/cards";
	const static std::string save = "./.resources/save.bin";

	extern std::ofstream debug;
    
    void write_binary(std::ostream& stream, const std::string& str);
    void read_binary(std::istream& stream, std::string& str);

}
