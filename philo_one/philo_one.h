#ifndef PHILO_ONE
# define PHILO_ONE
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct		s_option
{
	int	nb_philosopher;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_time_must_eat;
}									t_option;

int		ft_isdigit(char *str);
int		ft_atoi(const char *str);
int		ft_error(int err_nb);
int		ft_checkerror(char **av);

#endif
