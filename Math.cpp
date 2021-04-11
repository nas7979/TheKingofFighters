#include "DXUT.h"
#include "Math.h"


int Math::Random(int _Min, int _Max)
{
	return _Min + ((rand() | (rand() << 16)) % (_Max - _Min + 1));
}

float Math::Random(float _Min, float _Max)
{
	return _Min + ((rand() | (rand() << 16)) % (int)(_Max * 10000 - _Min * 10000 + 1)) * 0.0001;
}

float Math::Clamp(float _Val, float _Min, float _Max)
{
	return max(_Min, min(_Max, _Val));
}

float Math::Sign(float _Val)
{
	if (_Val > 0)
		return 1;
	if (_Val < 0)
		return -1;
	return 0;
}

char * Math::RandomText(char * _Text, int _Min, int _Max, bool _UnderBar)
{
	if(_UnderBar == false)
		sprintf(StaticText, "%s%d", _Text, Random(_Min, _Max));
	else
		sprintf(StaticText, "%s%d_", _Text, Random(_Min, _Max));

	return StaticText;
}
