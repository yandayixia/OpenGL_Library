#include "IOManager.h"
#include <fstream>
#include <string>

namespace MyEngine{
	bool IOManager::ReadFileToBuffer(std::string& filepath, std::vector<unsigned char>& buffer){
		std::ifstream file(filepath, std::ios::binary);
		if (file.fail()){
			perror(filepath.c_str());
			return false;
		}
		//seek to the end, put the cursor to 0 bytes of offset starting from the end. 
		file.seekg(0, std::ios::end);

		//Get the file size
		int fileSize = (int)file.tellg();
		file.seekg(0, std::ios::beg);

		//Reduce the file size by any header bytes that might be prescent 
		fileSize -= (int)file.tellg();

		buffer.resize(fileSize);
		file.read((char*)&(buffer[0]), fileSize);// this gives the c_str.

		file.close();
		return true;
	}
}