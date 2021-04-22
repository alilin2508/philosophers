#include "philo_one.h"

int	ft_atoi(const char *str)
{
	int		n;
	int		i;
	int		signe;

	n = 0;
	i = 0;
	signe = 1;
	while (str[i] && (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r' || str[i] == ' '))
		i++;
	while (str[i] && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			signe = signe * -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		n = n * 10 + (str[i] - '0');
		i++;
	}
	return (n * signe);
}

int ft_isdigit(char *str)
{
	int		i;

	i = 0;
	if (str[0] == '-')
	{
		if (!str[1])
			return (1);
		i++;
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}
