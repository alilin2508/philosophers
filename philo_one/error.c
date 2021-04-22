#include "philo_one.h"

int ft_error(int err_nb)
{
	if (err_nb == 0)
		write(2, "Error: wrong number of arguments\n", 33);
	if (err_nb == 1)
		write(2, "Error: wrong type of argument\n", 31);
	if (err_nb == 2)
		write(2, "Error: negative argument\n", 25);
	return (1);
}

int ft_checkerror(char **av)
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
