#include "philo_one.h"

int main(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (ft_error(0));
	ft_checkerror(&av[1]);
	return (0);
}
