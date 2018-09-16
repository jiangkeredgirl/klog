#pragma once
#include <string>
class GenerateDumpInfo
{
public:
	GenerateDumpInfo();
	~GenerateDumpInfo();
public:
	static GenerateDumpInfo& instance();
	int Generate(const std::string dumpFileName);
};

