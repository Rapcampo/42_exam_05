all: do

#ommiting -Werror because of silly wsl compiler error with subject pragma once
do:
	c++ -Wall -Wextra -g -fsanitize=address *.cpp *.hpp -o set

clean:
	rm *.o
	rm set

re: clean do
