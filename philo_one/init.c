#include "philo_one.h"

int		init_mutex(t_option *state)
{
	int	i;

	i = -1;
	pthread_mutex_init(&state->message, NULL);
	pthread_mutex_init(&state->state, NULL);
	pthread_mutex_lock(&state->state);
	if (!(state->forks =
		(pthread_mutex_t*)malloc(sizeof(*(state->forks)) * state->nb_philosopher)))
		return (1);
	while (++i < state->nb_philosopher)
		pthread_mutex_init(&state->forks[i], NULL);
	return (0);
}

void	init_philo(t_option *state)
{
	int i;

	i = 0;
	while (i < state->nb_philosopher)
	{
		state->philo[i].position = i;
		state->philo[i].eating = 0;
		state->philo[i].left_fork = i;
		state->philo[i].right_fork = (i + 1) % state->nb_philosopher;
		state->philo[i].eat_count = 0;
		state->philo[i].state = state;
		pthread_mutex_init(&state->philo[i].mutex, NULL);
		pthread_mutex_init(&state->philo[i].eat_message, NULL);
		pthread_mutex_lock(&state->philo[i].eat_message);
		i++;
	}
}

int init(t_option *state, int ac, char **av)
{
	state->nb_philosopher = ft_atoi(av[1]);
	state->time_to_die = ft_atoi(av[2]);
	state->time_to_eat = ft_atoi(av[3]);
	state->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		state->nb_time_must_eat = ft_atoi(av[5]);
	else
		state->nb_time_must_eat = 0;
	state->forks = NULL;
	state->philo = NULL;
	if (!(state->philo =
		(t_philo*)malloc(sizeof(*(state->philo)) * state->nb_philosopher)))
		return (1);
	init_philo(state);
	return (init_mutex(state));
}