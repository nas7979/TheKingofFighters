#pragma once
namespace Math
{
	static char StaticText[128];
	template<typename T>
	T Lerp(T _S, T _E, float _T)
	{
		return _S + (_E - _S) * _T * DT * 60;
	}

	int Random(int _Min, int _Max);
	float Random(float _Min, float _Max);
	float Clamp(float _Val, float _Min, float _Max);
	float Sign(float _Val);
	char* RandomText(char* _Text, int _Min, int _Max, bool _UnderBar = false);
}