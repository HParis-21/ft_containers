NAME		=	ft_containers
SRC			=	main
SRCS		=	$(addsuffix .cpp, $(addprefix srcs/, $(SRC)))
OBJS		=	$(SRCS:.cpp=.o)
CC			=	clang++
FLAGS		=	-Wall -Wextra -Werror -std=c++98 -I includes/
HEADER		=	includes/vector.hpp \
				includes/iterators.hpp \
				includes/map.hpp \
				includes/RedBlackTree.hpp \
				includes/stack.hpp \
				includes/set.hpp

.cpp.o		:
			$(CC) $(FLAGS) -c $< -o ${<:.cpp=.o}

all			:	$(NAME)

$(NAME)		: 	$(OBJS) $(HEADER)
			$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean		:
			rm -f $(OBJS)

fclean		:	clean
			rm -f $(NAME)

re			:	fclean all
.PHONY		:	all clean fclean re