#include "bigint.hpp"
#include <string>
#include <sstream>

bigint::bigint(){
    bigdata.push_back(0);
};

bigint::~bigint(){};

bigint::bigint(const bigint &src): bigdata(src.bigdata){
    while (bigdata.size() > 1 && bigdata.back() == 0)
        bigdata.pop_back();
}

bigint &bigint::operator=(const bigint &src){
    if (this != &src){
        this->bigdata = src.bigdata;
    }
    return *this;
}

bigint::bigint(unsigned long long nb){
    if (nb == 0)
        bigdata.push_back(0);
    while (nb){
        bigdata.push_back(nb % 10);
        nb /= 10;
    }
}

std::string bigint::getBigdata() const{
    std::string str;
    str.reserve(bigdata.size());
    std::vector<unsigned int>::const_reverse_iterator rit;

    for (rit = bigdata.rbegin(); rit != bigdata.rend(); rit++){
        str += *rit + '0';
    }
    std::string::size_type pos = str.find_last_not_of('0');
    if (pos == str.npos)
        return "0";
    if (pos == 0)
        return str;
    return str.substr(pos);
}

bigint &bigint::operator+=(const bigint &src){
    size_t biggest = (bigdata.size() > src.bigdata.size() ? bigdata.size() : src.bigdata.size());
    int carry = 0;
    bigint temp;

    for (size_t i = 0; i < biggest; i++){
        int a = i < bigdata.size() ? bigdata[i] : 0;
        int b = i < src.bigdata.size() ? src.bigdata[i] : 0;
        int sum = a + b + carry;
        sum > 9 ? (sum -= 10, carry = 1) : carry = 0;
        temp.bigdata.push_back(sum);
    }
    if (carry)
        temp.bigdata.push_back(carry);
    bigdata = temp.bigdata;
    return *this;
}

bigint bigint::operator+(const bigint &src) const{
    bigint temp(*this);
    temp += src;
    return temp;
}

bigint bigint::operator++(int){
    bigint temp(*this);
    temp += 1;
    return temp;
}

bigint &bigint::operator++(){
    *this += 1;
    return *this;
}

bigint bigint::operator<<(unsigned int nb) const{
    bigint temp(*this);
    for (; nb; nb--)
        temp.bigdata.insert(temp.bigdata.begin(), 0);
    return temp;
}

bigint &bigint::operator>>=(const bigint &src){
    unsigned int nb = 0;

    std::vector<unsigned int>::const_reverse_iterator rit = src.bigdata.rbegin();
    for (; rit != src.bigdata.rend(); rit++){
        nb *= 10;
        nb += *rit;
    }
    bigdata.erase(bigdata.begin(), bigdata.begin() + nb);
    return *this;
}

bigint &bigint::operator<<=(unsigned int nb){
    for(; nb; --nb)
        bigdata.insert(bigdata.begin(), 0);
    return *this;
}

bool bigint::operator!=(const bigint &src) const{
    return !(this->bigdata == src.bigdata);
}
bool bigint::operator==(const bigint &src) const{
    return this->bigdata == src.bigdata;
}
bool bigint::operator>(const bigint &src) const{
    if (bigdata.size() > src.bigdata.size())
        return true;
    if (bigdata.size() < src.bigdata.size())
        return false;
    for (size_t i = bigdata.size(); i-- > 0; ){
        if (bigdata[i] != src.bigdata[i])
            return bigdata[i] > src.bigdata[i];
    }
    return false;
}

bool bigint::operator<(const bigint &src) const{
    return src > *this;
}

bool bigint::operator<=(const bigint &src) const{
    return !(*this > src);
}

bool bigint::operator>=(const bigint &src) const{
    return !(*this < src);
}

std::ostream &operator<<(std::ostream &out, const bigint &bigsrc){
    return out << bigsrc.getBigdata();
}
