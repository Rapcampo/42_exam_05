FILES = *.cpp *.hpp

all:
	c++ -Wall -Wextra -Werror -std=c++98 -g -fsanitize=address $(FILES) -o vec

re: clean all

clean:
	rm *.o *.gch
	rm vec
