#include "philo_three.h"

void	eat(t_philo *philo)
{
	sem_wait(philo->mutex);
	philo->eating = 1;
	philo->last_eat = get_time();
	philo->limit = philo->last_eat + philo->state->time_to_die;
	display_message(philo, TYPE_EAT);
	usleep(philo->state->time_to_eat * 1000);
	philo->eat_count++;
	philo->eating = 0;
	sem_post(philo->mutex);
	sem_post(philo->eat_message);
}

void	take_forks(t_philo *philo)
{
	sem_wait(philo->state->forks);
	display_message(philo, TYPE_FORK);
	sem_wait(philo->state->forks);
	display_message(philo, TYPE_FORK);
}

void	put_down_forks(t_philo *philo)
{
	sem_post(philo->state->forks);
	sem_post(philo->state->forks);
	display_message(philo, TYPE_SLEEP);
	usleep(philo->state->time_to_sleep * 1000);
}
