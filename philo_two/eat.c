#include "philo_two.h"

int	eat(t_philo *philo)
{
	if (sem_wait(philo->mutex) != 0)
		return (1);
	philo->eating = 1;
	philo->last_eat = get_time();
	philo->limit = philo->last_eat + philo->state->time_to_die;
	if (display_message(philo, TYPE_EAT))
		return (1);
	usleep(philo->state->time_to_eat * 1000);
	philo->eat_count++;
	philo->eating = 0;
	if (sem_post(philo->mutex))
		return (1);
	if (sem_post(philo->eat_message))
		return (1);
	return (0);
}

int	take_forks(t_philo *philo)
{
	if (sem_wait(philo->state->forks))
		return (1);
	if (display_message(philo, TYPE_FORK))
		return (1);
	if (sem_wait(philo->state->forks))
		return (1);
	if (display_message(philo, TYPE_FORK))
		return (1);
	return (0);
}

int	put_down_forks(t_philo *philo)
{
	if (sem_post(philo->state->forks))
		return (1);
	if (sem_post(philo->state->forks))
		return (1);
	if (display_message(philo, TYPE_SLEEP))
		return (1);
	usleep(philo->state->time_to_sleep * 1000);
	return (0);
}
