#include <app/Config.hpp>

namespace game {

	std::ofstream debug("log/debug", std::ios_base::out);

    void write_binary(std::ostream& stream, const std::string& str)
	{
		size_t size = str.size();
		stream.write((char*)&size, sizeof(size_t));
		stream.write((char*)str.data(), size);
	}

    void read_binary(std::istream& stream, std::string& str)
	{
		size_t size;
		stream.read((char*)&size, sizeof(size_t));

        if (str.size() != size)
            str.resize(size);

		stream.read((char*)str.data(), size); // Read block of data directly into passive vector
	}
}

