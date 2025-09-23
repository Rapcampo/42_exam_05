#pragma once

#include <iostream>
#include <string>

class bigint{
	private:
		std::string bigdata;

	public:
		bigint();
		~bigint();
		bigint(unsigned int nb);
		bigint(const bigint &src);

		std::string getBigdata() const;

		bigint &operator=(const bigint &src);

		bigint operator+(const bigint &src) const;
		bigint &operator+=(const bigint &src);

		bool operator<(const bigint &src) const;
		bool operator>(const bigint &src) const;
		bool operator==(const bigint &src) const;
		bool operator<=(const bigint &src) const;
		bool operator>=(const bigint &src) const;
		bool operator!=(const bigint &src) const;

		bigint  &operator++();
		bigint  operator++(int);

		bigint operator<<(unsigned int) const;
		bigint operator>>(unsigned int) const;
		bigint &operator>>=(const bigint &src);
		bigint &operator<<=(const bigint &src);
};

std::ostream &operator<<(std::ostream &out, const bigint &big);
