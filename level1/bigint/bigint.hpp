/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint2.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:54:18 by rapcampo          #+#    #+#             */
/*   Updated: 2025/09/30 18:17:27 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIGINT2_HPP
# define BIGINT2_HPP
#include <iostream>
#include <fstream>
#include <ostream>
#include <vector>
#include <string>

class bigint{
	private:
		std::vector<unsigned int> data;

	public:
		bigint();
		~bigint();
		bigint(const bigint &);
		bigint(unsigned long long nb);
		bigint &operator=(const bigint &);

		std::string getData() const;

		bigint &operator+=(const bigint &);
		bigint operator+(const bigint &) const;
		bigint operator++(int) const;
		bigint &operator++();

		bool operator<(const bigint &) const;
		bool operator>(const bigint &) const;
		bool operator==(const bigint &) const;
		bool operator!=(const bigint &) const;
		bool operator<=(const bigint &) const;
		bool operator>=(const bigint &) const;

		bigint operator<<(unsigned int) const;
		bigint operator>>(unsigned int) const;
		bigint &operator<<=(unsigned int);
		bigint &operator>>=(const bigint &src);
};

std::ostream &operator<<(std::ostream &out, const bigint &bigint);
#endif
