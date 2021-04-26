#include "philo_one.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	philo->eating = 1;
	philo->last_eat = get_time();
	philo->limit = philo->last_eat + philo->state->time_to_die;
	display_message(philo, TYPE_EAT);
	usleep(philo->state->time_to_eat * 1000);
	philo->eat_count++;
	philo->eating = 0;
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_unlock(&philo->eat_message);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->state->forks[philo->left_fork]);
	display_message(philo, TYPE_FORK);
	pthread_mutex_lock(&philo->state->forks[philo->right_fork]);
	display_message(philo, TYPE_FORK);
}

void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->state->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->state->forks[philo->right_fork]);
	display_message(philo, TYPE_SLEEP);
	usleep(philo->state->time_to_sleep * 1000);
}
