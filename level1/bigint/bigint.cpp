/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapcampo <rapcampo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 18:17:59 by rapcampo          #+#    #+#             */
/*   Updated: 2025/10/03 19:13:52 by rapcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.hpp"

bigint::bigint(){
    data.push_back(0);
}

bigint::~bigint(){}


bigint::bigint(const bigint &src): data(src.data){
    while (data.size() > 1 && data.back() == 0)
        data.pop_back();
}

bigint &bigint::operator=(const bigint &src){
    if (this != &src){
        this->data = src.data;
    }
    return *this;
}

bigint::bigint(unsigned long long nb){
    if (nb == 0)
        data.push_back(0);
    while (nb){
        data.push_back(nb %10);
        nb /= 10;
    }
}

std::string bigint::getData() const{
    std::string str;
    str.reserve(data.size());
    std::vector<unsigned int>::const_reverse_iterator rit;
    for (rit = data.rbegin(); rit != data.rend(); rit++){
        str += *rit +'0';
    }
    std::string::size_type pos = 0;
    if (str.size() > 1 && *data.begin() == '0'){
        pos = str.find_first_not_of('0');
        if (pos == str.npos)
            return "0";
        if (pos == 0)
            return str;
    }
    return str.substr(pos);
}

bigint &bigint::operator+=(const bigint &src){
    size_t biggest = (data.size() > src.data.size() ? data.size() : src.data.size());
    int carry = 0, a, b, sum;
    bigint temp;

    temp.data.clear();
    for (size_t i = 0; i < biggest; i++){
        a = i < data.size() ? data[i] : 0;
        b = i < src.data.size() ? src.data[i] : 0;
        sum = a + b + carry;
        sum > 9 ? (sum -= 10, carry = 1) : carry = 0;
        temp.data.push_back(sum);
    }
    if (carry)
        temp.data.push_back(carry);
    data = temp.data;
    return *this;
}

bigint bigint::operator+(const bigint &src) const{
    bigint temp(*this);
    temp += src;
    return temp;
}

bigint bigint::operator++(int){
    bigint temp(*this);
    *this += 1;
    return temp;
}

bigint &bigint::operator++(){
    *this += 1;
    return *this;
}

bigint &bigint::operator<<=(unsigned int n){
    for(; n; n--){
        data.insert(data.begin(), 0);
    }
    return *this;
}

bigint &bigint::operator>>=(const bigint &src){
    unsigned int n = 0;

    std::vector<unsigned int>::const_reverse_iterator rit = src.data.rbegin();
    for(; rit != src.data.rend(); rit++){
        n *=10;
        n += *rit;
    }
    data.erase(data.begin(), data.begin() + n);
    return *this;
}

bigint bigint::operator<<(unsigned int n) const{
    bigint temp(*this);
    for(; n; n--){
        temp.data.insert(temp.data.begin(), 0);
    }
    return temp;
}

bigint bigint::operator>>(unsigned int n) const{
    bigint temp(*this);
    temp >>= n;
    return temp;
}

bool bigint::operator==(const bigint &src) const{
    return this->data == src.data;
}
bool bigint::operator!=(const bigint &src) const{
    return !(this->data == src.data);
}
bool bigint::operator<(const bigint &src) const{
    return src > *this;
}
bool bigint::operator>(const bigint &src) const{
    if (data.size() > src.data.size())
        return true;
    if (data.size() < src.data.size())
        return false;
    for (size_t i = data.size(); i-- > 0;){
        if (data[i] != src.data[i])
            return data[i] > src.data[i];
    }
    return false;
}
bool bigint::operator<=(const bigint &src) const{
    return !(*this > src);

}
bool bigint::operator>=(const bigint &src) const{
    return !(*this < src);
}

std::ostream &operator<<(std::ostream &out, const bigint &src){
    return out << src.getData();
}
