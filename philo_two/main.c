#include "philo_two.h"

static void	*must_eat_count(void *state)
{
	t_option *rstate;
	int		i;

	rstate = (t_option*)state;
	while (rstate->current_eat_count < rstate->nb_time_must_eat)
	{
		i = 0;
		while (i < rstate->nb_philosopher)
			if (sem_wait(rstate->philo[i++].eat_message))
				return ((void*)0);
		rstate->current_eat_count++;
	}
	if (display_message(&rstate->philo[0], TYPE_OVER))
		return ((void*)0);
	if (sem_post(rstate->state))
		return ((void*)0);
	return ((void*)0);
}

static void	*monitor(void *philo)
{
	t_philo		*rphilo;

	rphilo = (t_philo*)philo;
	while (1)
	{
		if (sem_wait(rphilo->mutex))
			return ((void*)0);
		if (!rphilo->eating && get_time() > rphilo->limit)
		{
			if (display_message(rphilo, TYPE_DIED))
				return ((void*)0);
			if (sem_post(rphilo->mutex))
				return ((void*)0);
			if (sem_post(rphilo->state->state))
				return ((void*)0);
			return ((void*)0);
		}
		if (sem_post(rphilo->mutex))
			return ((void*)0);
	}
}

static void	*routine(void *philo)
{
	t_philo		*rphilo;
	pthread_t	tid;
	int				should_end;

	rphilo = (t_philo*)philo;
	rphilo->last_eat = get_time();
	rphilo->limit = rphilo->last_eat + rphilo->state->time_to_die;
	if (pthread_create(&tid, NULL, &monitor, rphilo) != 0)
		return ((void*)1);
	pthread_detach(tid);
	while (1)
	{
		if (take_forks(rphilo))
			return ((void*)0);
		should_end = eat(rphilo);
		if (put_down_forks(rphilo))
			return ((void*)0);
		if (should_end)
			return ((void*)0);
		if (display_message(rphilo, TYPE_THINK))
			return ((void*)0);
	}
	return ((void*)0);
}

static int	start_threads(t_option *state)
{
	int			i;
	pthread_t	tid;
	void			*philo;

	i = 0;
	state->start = get_time();
	if (state->nb_time_must_eat > 0)
	{
		if (pthread_create(&tid, NULL, &must_eat_count, (void*)state) != 0)
			return (1);
		pthread_detach(tid);
	}
	while (i < state->nb_philosopher)
	{
		philo = (void*)(&state->philo[i]);
		if (pthread_create(&tid, NULL, &routine, philo) != 0)
			return (1);
		pthread_detach(tid);
		usleep(10);
		i++;
	}
	return (0);
}

int main(int ac, char **av)
{
	t_option state;

	if (ac < 5 || ac > 6)
		return (ft_error(0));
	ft_checkerror(&av[1]);
	if (init(&state, ac, av) == 1 || start_threads(&state) == 1)
		return (clear(&state) && ft_error(3));
	sem_wait(state.state);
	clear(&state);
	return (0);
}
