#include "philo_three.h"

int	clear(t_option *state)
{
	int		i;
	char	semaphore[255];

	sem_unlink(SEMAPHORE_FORK);
	sem_unlink(SEMAPHORE_WRITE);
	sem_unlink(SEMAPHORE_DEAD);
	sem_unlink(SEMAPHORE_DEADM);
	if (state->philo)
	{
		i = 0;
		while (i < state->nb_philosopher)
		{
			make_semaphore_name(SEMAPHORE_PHILO, (char*)semaphore, i);
			sem_unlink(semaphore);
			make_semaphore_name(SEMAPHORE_PHILOEAT, (char*)semaphore, i++);
			sem_unlink(semaphore);
		}
		free(state->philo);
	}
	return (1);
}

int	ft_error(int err_nb)
{
	if (err_nb == 0)
		write(2, "Error: wrong number of arguments\n", 33);
	else if (err_nb == 1)
		write(2, "Error: wrong type of argument\n", 31);
	else if (err_nb == 2)
		write(2, "Error: negative argument\n", 25);
	else if (err_nb == 3)
		write(2, "Error: fatal\n", 13);
	return (1);
}

int	ft_checkerror(char **av)
{
	int		i;

	i = 0;
	while (av[i])
	{
		if (ft_isdigit(av[i]))
			return (ft_error(1));
		if (ft_atoi(av[i]) < 0)
			return (ft_error(2));
		i++;
	}
	return (0);
}
