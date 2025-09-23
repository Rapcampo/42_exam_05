#include "bigint.hpp"
#include <sstream>

bigint::bigint(): bigdata("0"){};

bigint::~bigint(){};

bigint::bigint(const bigint &src): bigdata(src.bigdata){}

bigint &bigint::operator=(const bigint &src){
    if (this != &src){
        this->bigdata = src.bigdata;
    }
    return *this;
}

bigint::bigint(unsigned int nb){
    std::stringstream ss;
    ss << nb;
    this->bigdata = ss.str();
}

std::string bigint::getBigdata() const{
    return (this->bigdata);
}

bigint bigint::operator+(const bigint &src) const{

}
