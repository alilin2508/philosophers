NAME	= philo_one

SRCS	= main.c \
				error.c \
				utils.c \

OBJS	= $(SRCS:.c=.o)

all			:	$(NAME)

$(NAME)	:	$(OBJS)
					gcc -Wall -Wextra -Werror -o $(NAME) $(SRCS)

clean		:
					rm -rf $(OBJS)

fclean	:	clean
					rm -rf $(NAME)

re			:	fclean all
