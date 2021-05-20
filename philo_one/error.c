/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 11:01:01 by alilin            #+#    #+#             */
/*   Updated: 2021/05/20 13:16:03 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	clear(t_option *state)
{
	int	i;

	if (state->forks)
	{
		i = 0;
		while (i < state->nb_philosopher)
			pthread_mutex_destroy(&state->forks[i++]);
		free(state->forks);
	}
	if (state->philo)
	{
		i = 0;
		while (i < state->nb_philosopher)
		{
			pthread_mutex_destroy(&state->philo[i].mutex);
			pthread_mutex_destroy(&state->philo[i++].eat_message);
		}
		free(state->philo);
	}
	pthread_mutex_destroy(&state->message);
	pthread_mutex_destroy(&state->state);
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
