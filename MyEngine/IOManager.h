#pragma once
#include <vector>
#include <string>

namespace MyEngine{
	class IOManager
	{
	public:
		static bool ReadFileToBuffer(std::string& filepath, std::vector<unsigned char>& buffer);
	};
}
