NAME	= philo_three

SRCS	= main.c \
				error.c \
				utils.c \
				init.c \
				eat.c \
				message.c \
				semaphore.c \
				thread.c \
				utils2.c

OBJS	= $(SRCS:.c=.o)

all			:	$(NAME)

$(NAME)	:	$(OBJS)
					gcc -Wall -Wextra -Werror -o $(NAME) $(SRCS) -lpthread

clean		:
					rm -rf $(OBJS)

fclean	:	clean
					rm -rf $(NAME)

re			:	fclean all
