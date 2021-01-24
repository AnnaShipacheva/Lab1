#pragma once
#include <iostream>

enum trit {
	False,
	Unknown,
	True
};

trit operator& (trit& a, trit& b);
trit operator| (trit& a, trit& b);
trit operator! (trit& a);
std::ostream& operator<< (std::ostream& out, trit a);
bool operator==(trit& a, trit& b);