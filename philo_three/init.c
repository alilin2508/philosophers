/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 11:02:01 by alilin            #+#    #+#             */
/*   Updated: 2021/05/20 14:48:45 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	init_semaphore(t_option *state)
{
	sem_unlink(SEMAPHORE_FORK);
	sem_unlink(SEMAPHORE_WRITE);
	sem_unlink(SEMAPHORE_DEAD);
	sem_unlink(SEMAPHORE_DEADM);
	state->forks = ft_sem_open(SEMAPHORE_FORK, state->nb_philosopher);
	state->message = ft_sem_open(SEMAPHORE_WRITE, 1);
	state->state = ft_sem_open(SEMAPHORE_DEAD, 0);
	state->dead_message = ft_sem_open(SEMAPHORE_DEADM, 1);
	if (!state->forks || !state->message || !state->state
		|| !state->dead_message)
		return (1);
	return (0);
}

int	init_philo(t_option *state)
{
	int		i;
	char	semaphore[255];

	i = 0;
	while (i < state->nb_philosopher)
	{
		state->philo[i].position = i;
		state->philo[i].eating = 0;
		state->philo[i].eat_count = 0;
		state->philo[i].state = state;
		make_semaphore_name(SEMAPHORE_PHILO, (char *)semaphore, i);
		sem_unlink(semaphore);
		state->philo[i].mutex = ft_sem_open(semaphore, 1);
		if (!state->philo[i].mutex)
			return (1);
		make_semaphore_name(SEMAPHORE_PHILOEAT, (char *)semaphore, i);
		sem_unlink(semaphore);
		state->philo[i].eat_message = ft_sem_open(semaphore, 0);
		if (!state->philo[i].eat_message)
			return (1);
		i++;
	}
	return (0);
}

int	init(t_option *state, int ac, char **av)
{
	state->nb_philosopher = ft_atoi(av[1]);
	state->time_to_die = ft_atoi(av[2]);
	state->time_to_eat = ft_atoi(av[3]);
	state->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		state->nb_time_must_eat = ft_atoi(av[5]);
	else
		state->nb_time_must_eat = -1;
	state->forks = NULL;
	state->philo = NULL;
	state->current_eat_count = 0;
	state->philo = (t_philo *)malloc(sizeof(*(state->philo))
			* state->nb_philosopher);
	if (!state->philo)
		return (1);
	if (init_philo(state) == 1)
		return (1);
	return (init_semaphore(state));
}
