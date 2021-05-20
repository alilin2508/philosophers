/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 11:02:08 by alilin            #+#    #+#             */
/*   Updated: 2021/05/20 11:50:07 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int	start_process(t_option *state)
{
	int			i;

	state->start = get_time();
	i = 0;
	while (i < state->nb_philosopher)
	{
		state->philo[i].pid = fork();
		if (state->philo[i].pid < 0)
			return (1);
		else if (state->philo[i].pid == 0)
		{
			routine(&state->philo[i]);
			exit(0);
		}
		ft_usleep(1 / 10);
		i++;
	}
	return (0);
}

int			main(int ac, char **av)
{
	t_option	state;
	int			i;

	if (ac < 5 || ac > 6)
		return (ft_error(0));
	if (ft_checkerror(&av[1]))
		return (1);
	if (init(&state, ac, av) == 1 || start_threads(&state) == 1
	|| start_process(&state) == 1)
		return (clear(&state) && ft_error(3));
	sem_wait(state.state);
	i = 0;
	while (i < state.nb_philosopher)
		kill(state.philo[i++].pid, SIGKILL);
	clear(&state);
	return (0);
}
