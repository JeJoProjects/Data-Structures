#include <iostream>
#include <vector>
#include <type_traits>
#include <utility>
#include <stdexcept>  // 
#include <cstddef>
#include <cassert>


template<typename T> class Matrix2D;
template<typename Type>
std::ostream& operator<<(std::ostream& out, const Matrix2D<Type>& mat) noexcept;


template<typename T> class Matrix2D final
{
private:
	const std::size_t _row;
	const std::size_t _col;
	std::vector<T> _storage;

public:
	constexpr explicit Matrix2D(
		const std::size_t row, const std::size_t col)
		: _row{ row }
		, _col{ col }
	{
		_storage.reserve(_row * _col);
	}

	template<typename... Args>
	constexpr void emplace_row(Args&& ... args)
	{
		static_assert((std::is_constructible_v<T, Args&&> && ...));
		assert(sizeof...(Args) <= this->_row);
		//assert(_storage.size() <= this->_row); // check col exceeds the size
		(_storage.emplace_back(std::forward<Args>(args)), ...);
	}

	T& operator()(const std::size_t row, const std::size_t col)
	{
		if (row < 0 || _row <= row  || col < 0 || _col <= col)
			throw std::out_of_range{ "Not valid range!" };
		return this->_storage[(row * _col) + col];
	}

	T operator()(const std::size_t row, const std::size_t col) const
	{
		if (row < 0 || _row <= row || col < 0 || _col <= col)
			throw std::out_of_range{ "Not valid range!" };
		return this->_storage[(row * _col) + col];
	}

	template<typename Type>
	friend std::ostream& operator<< <>(std::ostream& out, const Matrix2D<Type>& mat) noexcept;
};

template<typename Type>
std::ostream& operator<< <>(std::ostream& out, const Matrix2D<Type>& mat) noexcept
{
	for (std::size_t row{ 0 }; row < mat._row; ++row)
	{
		for (std::size_t col{ 0 }; col < mat._col; ++col)
			out << mat._storage[(row * mat._col) + col] << ' ';
		out << '\n';
	}
	return out;
}