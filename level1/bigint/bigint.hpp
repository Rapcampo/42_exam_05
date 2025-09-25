#ifndef BIGINT_HPP
# define BIGINT_HPP

#include <iostream>
#include <string>
#include <vector>
#include <ostream>

class bigint{
	private:
		std::vector<unsigned int> bigdata;

	public:
		bigint();
		~bigint();
		bigint(unsigned long long nb);
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
		bigint &operator<<=(unsigned int nb);
};

std::ostream &operator<<(std::ostream &out, const bigint &big);
#endif
