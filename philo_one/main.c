#include "philo_one.h"

static void	*must_eat_count(void *state)
{
	t_option *rstate;
	int		i;
	int		total;

	rstate = (t_option*)state;
	total = 0;
	while (total < rstate->nb_time_must_eat)
	{
		i = 0;
		while (i < rstate->nb_philosopher)
			pthread_mutex_lock(&rstate->philo[i++].eat_message);
		total++;
	}
	display_message(&rstate->philo[0], TYPE_OVER);
	pthread_mutex_unlock(&rstate->state);
	return ((void*)0);
}

static void	*monitor(void *philo)
{
	t_philo		*rphilo;

	rphilo = (t_philo*)philo;
	while (1)
	{
		pthread_mutex_lock(&rphilo->mutex);
		if (!rphilo->eating && get_time() > rphilo->limit)
		{
			display_message(rphilo, TYPE_DIED);
			pthread_mutex_unlock(&rphilo->mutex);
			pthread_mutex_unlock(&rphilo->state->state);
			return ((void*)0);
		}
		pthread_mutex_unlock(&rphilo->mutex);
		usleep(100);
	}
}

static void	*routine(void *philo)
{
	t_philo		*rphilo;
	pthread_t	tid;

	rphilo = (t_philo*)philo;
	rphilo->last_eat = get_time();
	rphilo->limit = rphilo->last_eat + rphilo->state->time_to_die;
	if (pthread_create(&tid, NULL, &monitor, philo) != 0)
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
	pthread_mutex_lock(&state.state);
	pthread_mutex_unlock(&state.state);
	clear(&state);
	return (0);
}
