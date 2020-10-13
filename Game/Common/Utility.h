#pragma once

namespace Utility
{
	// Å‘å’l‚ğ§ŒÀ‚·‚é
	template <typename T>
	T Max(T _x, T _max)
	{
		if (_x > _max)
		{
			return _max;
		}
		return _x;
	}

	// Å¬’l‚ğ§ŒÀ‚·‚é
	template <typename T>
	T Min(T _x, T _min)
	{
		if (_x < _min)
		{
			return _min;
		}
		return _x;
	}

	// ”ÍˆÍ“à‚Éû‚ß‚é
	template <typename T>
	T Clamp(T _min, T _x, T _max)
	{
		T result = Min(_x, _min);
		result = Max(result, _max);

		return result;
	}
}