#include "Module.hpp"

string CommonData(string file)
{
	string ret = DATA_PATH;
	ret.append(file);
	return ret;
}