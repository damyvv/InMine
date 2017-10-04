#pragma once

#include <string>
#include <fstream>

class FileLoader
{
public:
	enum Error
	{
		FILE_NOT_FOUND = -1,
		OK = 0
	};

	static int fileToString(const char* path, std::string& dest) {
		std::ifstream file(path);
		if (!file.is_open()) return FILE_NOT_FOUND;
		std::getline(file, dest, '\0');
		return OK;
	}
};
