#pragma once

#include <random>

struct randomizer {

	/// <summary>
	/// ������: ����� ����� �� 0 �� 1!
	/// </summary>
	static const int random_int(const int& min, const int& max) { 
		static std::random_device rd;
		static std::default_random_engine eng(rd());
		static const std::uniform_int_distribution<int> di(min, max);

		return di(eng);
	}

	/// <summary>
	/// ����� ��������� ����� �� -1.0 �� 1.0.
	/// </summary>
	/// <returns></returns>
	static const float random_float() {
		static std::random_device rd;
		static std::default_random_engine eng(rd());
		static const std::uniform_real_distribution<float> di(-1, 1);

		return di(eng);
	}

	/// <summary>
	/// ����� ��������� ����� � ��������� [min;max].
	/// </summary>
	static const float random_float(const float& min, const float& max) {
		static std::random_device rd;
		static std::default_random_engine eng(rd());
		static const std::uniform_real_distribution<float> di(min, max);

		return di(eng);
	}
};