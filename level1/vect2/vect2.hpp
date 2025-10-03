#ifndef VECT2_HPP
# define VECT2_HPP

#include <utility>
#include <iostream>
#include <fstream>

class vect2{
	private:
		std::pair<int,int> p;

	public:
		vect2(); //done
		~vect2();//done
		vect2(const vect2 &src);//done
		vect2(int, int);//done
		vect2 &operator=(const vect2 &right);//done
		vect2 &operator-=(const vect2 &right);//done
		vect2 &operator+=(const vect2 &right);//done

		int &operator[](int);//done
		int operator[](int) const;//done

		vect2 operator*(int) const;//done
		vect2 &operator*=(int);//done

		vect2 operator+(const vect2 &right) const;//done
		vect2 operator-(const vect2 &right) const;//done

		vect2 operator++(int);//done
		vect2 operator--(int);//done
		vect2 &operator++();//done
		vect2 &operator--();//done

		vect2 operator-() const;//done

		bool operator==(const vect2 &right) const;//done
		bool operator!=(const vect2 &right) const;//done
};

std::ostream &operator<<(std::ostream &out, const vect2 vect2);//done
vect2 operator*(int, const vect2 &src);

#endif
