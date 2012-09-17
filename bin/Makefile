NAME		=		chess

INCLUDE		=		../includes

SOURCES		=		../sources

SRC		=		$(wildcard ../sources/*.cpp)

OBJ		=		$(SRC:.cpp=.o)

CC		=		g++

CXXFLAGS	=		-W -Wall -Werror -I $(INCLUDE)

all:				$(NAME)

$(NAME):			$(OBJ)
				$(CC) $(CXXFLAGS) -o $(NAME) $(OBJ)

clean:
				rm -rf ../*~ ../#*# $(OBJ)

fclean:				clean
				rm -f $(NAME)

re:				fclean all

.PHONY:				all clean fclean re $(NAME)
