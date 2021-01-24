#include "Trit.h"

trit operator&(trit& a, trit& b)
{
	switch (a)
	{
	case False:
		return False;
	case Unknown:
		switch (b) 
		{
		case False:
			return False;
		case Unknown:
		case True:
			return Unknown;
		}
	case True:
		switch (b)
		{
		case False:
			return False;
		case Unknown:
			return Unknown;
		case True:
			return True;
		}
	default :
		return Unknown;
	}
}

trit operator|(trit& a, trit& b)
{
	switch (a)
	{
	case False:
		switch (b)
		{
		case False:
			return False;
		case Unknown:
			return Unknown;
		case True:
			return True;
		default:
			return Unknown;
		}
	case Unknown:
		switch (b)
		{
		case False:
		case Unknown:
			return Unknown;
		case True:
			return True;
		default:
			return Unknown;
		}
	case True:
		return True;
	default:
		return Unknown;
	}
}

trit operator!(trit& a) 
{
	switch (a) {
	case False:
		return True;
	case Unknown:
		return Unknown;
	case True:
		return False;
	default:
		return Unknown;
	}
}

std::ostream& operator<<(std::ostream &out, trit a)
{
	switch (a)
	{
	case False:
		return (out << "False");
	case Unknown:
		return (out << "Unknown");
	case True:
		return (out << "True");
	default:
		return (out << "Unknown");
	}
}

bool operator==(trit& a, trit& b)
{
	switch (a)
	{
	case False:
		switch (b)
		{
			case False:
				return 1;
			default:
				return 0;
		}
	case Unknown:
		switch (b)
		{
		case Unknown:
			return 1;
		default:
			return 0;
		}
	case True:
		switch (b)
		{
		case True:
			return 1;
		default:
			return 0;
		}
	}
}