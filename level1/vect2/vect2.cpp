#include "vect2.hpp"

vect2::vect2(){
	p.first = 0;
	p.second = 0;
}

vect2::~vect2(){}

vect2::vect2(int n, int n2){
	p.first = n;
	p.second = n2;
}

vect2::vect2(const vect2 &src){
	*this = src;
}

vect2 &vect2::operator=(const vect2 &src){
	if (this != &src){
		p.first = src.p.first;
		p.second = src.p.second;
	}
	return *this;
}

int	vect2::operator[](int n) const{
	if (!n)
		return p.first;
	return p.second;
}

vect2 vect2::operator+(const vect2 &right) const{
	vect2 temp(*this);
	temp[0] += right[0];
	temp[1] += right[1];
	return temp;
}

vect2 &vect2::operator+=(const vect2 &right){
	this->p.first += right[0];
	this->p.second  += right[1];
	return *this;
}

vect2 vect2::operator-(const vect2 &right) const{
	vect2 temp(*this);
	temp[0] -= right[0];
	temp[1] -= right[1];
	return temp;
}

vect2 &vect2::operator-=(const vect2 &right){
	this->p.first -= right[0];
	this->p.second  -= right[1];
	return *this;
}

vect2 vect2::operator*(int n) const{
	vect2 temp(*this);
	temp.p.first *= n;
	temp.p.second *= n;
	return temp;
}

vect2 &vect2::operator*=(int n){
	p.first *= n;
	p.second *= n;
	return *this;
}

int	&vect2::operator[](int n){
	if (!n)
		return p.first;
	return p.second;
}

vect2 &vect2::operator++(){
	p.first++;
	p.second++;
	return *this;
}

vect2 vect2::operator++(int){
	vect2 temp(*this);
	++(*this);
	return temp;
}

vect2 &vect2::operator--(){
	p.first--;
	p.second--;
	return *this;
}

vect2 vect2::operator--(int){
	vect2 temp(*this);
	--(*this);
	return temp;
}

vect2 vect2::operator-() const{
	vect2 temp(*this);
	temp[0] = -temp[0];
	temp[1] = -temp[1];
	return temp;
}

bool vect2::operator==(const vect2 &right) const{
	return (this->p == right.p);
}

bool vect2::operator!=(const vect2 &right) const{
	return !(this->p == right.p);
}

std::ostream &operator<<(std::ostream &out, const vect2& vec){
	return (out << "{" << vec[0] << ", " << vec[1] << "}");
}

vect2 operator*(int n, const vect2 &src){
	vect2 temp(src);
	temp *= n;
	return temp;
}
