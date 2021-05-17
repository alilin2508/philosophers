/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 11:02:40 by alilin            #+#    #+#             */
/*   Updated: 2021/05/17 11:27:42 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*must_eat_count(void *state)
{
	t_option	*rstate;
	int			i;

	rstate = (t_option*)state;
	while (rstate->current_eat_count < rstate->nb_time_must_eat)
	{
		i = 0;
		while (i < rstate->nb_philosopher)
			sem_wait(rstate->philo[i++].eat_message);
		rstate->current_eat_count++;
	}
	display_message(&rstate->philo[0], TYPE_OVER);
	sem_post(rstate->state);
	return ((void*)0);
}

void	*monitor(void *philo)
{
	t_philo		*rphilo;

	rphilo = (t_philo*)philo;
	while (1)
	{
		sem_wait(rphilo->mutex);
		if (!rphilo->eating && get_time() > rphilo->limit)
		{
			display_message(rphilo, TYPE_DIED);
			sem_post(rphilo->mutex);
			sem_post(rphilo->state->state);
			return ((void*)0);
		}
		sem_post(rphilo->mutex);
		usleep(1000);
	}
	return ((void*)0);
}

void	*routine(void *philo)
{
	t_philo		*rphilo;
	pthread_t	tid;

	rphilo = (t_philo*)philo;
	rphilo->last_eat = get_time();
	rphilo->limit = rphilo->last_eat + rphilo->state->time_to_die;
	if (pthread_create(&tid, NULL, &monitor, rphilo) != 0)
		return ((void*)1);
	pthread_detach(tid);
	while (1)
	{
		take_forks(rphilo);
		eat(rphilo);
		put_down_forks(rphilo);
		display_message(rphilo, TYPE_THINK);
	}
	return ((void*)0);
}

int		start_threads(t_option *state)
{
	pthread_t	tid;

	if (state->nb_time_must_eat > 0)
	{
		if (pthread_create(&tid, NULL, &must_eat_count, (void*)state) != 0)
			return (1);
		pthread_detach(tid);
	}
	return (0);
}
