#pragma once

#include <exception>
#include "neural_random.h"

/* 
	Внимание: Не стоит использовать вот такую конструкцию
	matrix a = b * c;
	Это вызовет ошибку, чтобы этого избежать используйте копирование
	matrix a(b * c);
*/

// simple matrix for neural network
struct matrix
{
	friend class matrix_debug;
private:
	float** data_; // 2d array

	unsigned int rows_;
	unsigned int columns_;
	

public:
	matrix(const unsigned int& rows, const unsigned int& colums, bool defaultValue = true) : rows_(rows), columns_(colums) {
		data_ = new float*[rows];
		for (size_t i = 0; i < rows; ++i)
		{
			data_[i] = new float[colums];
		}

		if (defaultValue) {
			fillMatrix(0.0f);
		}
	}

	matrix(const matrix& copy) : rows_(copy.rows_), columns_(copy.columns_) {

		data_ = new float* [copy.rows_];
		for (size_t i = 0; i < copy.rows_; ++i)
		{
			data_[i] = new float[copy.columns_];
			for (size_t j = 0; j < copy.columns_; ++j)
			{
				data_[i][j] = copy.data_[i][j];
			}
		}

	}

	explicit matrix(const std::vector<float>& other) {
		this->rows_ = 1;
		this->columns_ = (unsigned int)other.size();

		// Выделение памяти для матрицы
		data_ = new float* [rows_];
		for (unsigned int i = 0; i < rows_; ++i) {
			data_[i] = new float[columns_];
		}

		for (unsigned int i = 0; i < columns_; ++i) {
			data_[0][i] = other[i];
		}
	}

	~matrix()
	{
		for (size_t i = 0; i < rows_; ++i)
		{
			delete[] data_[i];
		}
		delete[] data_;
	}

public:
	float* operator[](const size_t& i) {
		return data_[i];
	}

	const matrix operator*(const matrix& other) const {
		if (columns_ != other.rows_) {
			throw std::invalid_argument("The operation for these matrices is not possible, incompatible dimensions. \n");
		}

		matrix result(rows_, other.columns_);

		for (unsigned int i = 0; i < rows_; ++i) {
			for (unsigned int j = 0; j < other.columns_; ++j) {
				for (unsigned int k = 0; k < columns_; ++k) {
					result[i][j] += data_[i][k] * other.data_[k][j];
				}
			}
		}
		return result;
	}

	/// <summary>
	/// Try use copy, not operator.
	/// </summary>
	matrix& operator=(const matrix& other) {

		if (this == &other) {
			return *this;
		}

		rows_ = other.rows_;
		columns_ = other.columns_;

		for (size_t i = 0; i < rows_; ++i)
		{
			delete[] data_[i];
		}
		delete[] data_; // it can invoke error

		data_ = new float* [rows_];
		for (unsigned int i = 0; i < rows_; ++i) {
			data_[i] = new float[columns_];
		}

		// Копирование значений другой матрицы
		for (unsigned int i = 0; i < rows_; ++i) {
			for (unsigned int j = 0; j < columns_; ++j) {
				data_[i][j] = other.data_[i][j];
			}
		}
		return *this;
	}

public:
	matrix T() {
		matrix result(columns_, rows_);

		for (unsigned int i = 0; i < columns_; ++i) {
			for (unsigned int j = 0; j < rows_; ++j) {
				result[i][j] = data_[j][i];
			}
		}
		return result;
	}

	void fillRandom() {
		for (size_t r = 0; r < rows_; ++r)
		{
			for (size_t c = 0; c < columns_; ++c)
			{
				data_[r][c] = randomizer::random_float();
			}
		}
	}

	void fillMatrix(const float& value) {
		for (size_t r = 0; r < rows_; ++r)
		{
			for (size_t c = 0; c < columns_; ++c)
			{
				data_[r][c] = value;
			}
		}
	}

	static matrix randomMatrix(const unsigned int& rows, const unsigned int& columns) {
		matrix mat(rows, columns);
		for (size_t r = 0; r < rows; ++r)
		{
			for (size_t c = 0; c < columns; ++c)
			{
				mat[r][c] = randomizer::random_float();
			}
		}
		return mat;
	}

	const unsigned int& get_rows() const noexcept {
		return this->rows_;
	}
	const unsigned int& get_colums() const noexcept {
		return this->columns_;
	}
};

