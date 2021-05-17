NAME	= philo_two

SRCS	= main.c \
				error.c \
				utils.c \
				init.c \
				eat.c \
				message.c \
				semaphore.c \

OBJS	= $(SRCS:.c=.o)

all			:	$(NAME)

$(NAME)	:	$(OBJS)
					gcc -Wall -Wextra -Werror -o $(NAME) $(SRCS) -lpthread

clean		:
					rm -rf $(OBJS)

fclean	:	clean
					rm -rf $(NAME)

re			:	fclean all
