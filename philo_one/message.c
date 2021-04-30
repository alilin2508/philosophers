#include "philo_one.h"

char	*get_message(int type)
{
	if (type == TYPE_EAT)
		return (" is eating");
	else if (type == TYPE_SLEEP)
		return (" is sleeping");
	else if (type == TYPE_FORK)
		return (" has taken a fork");
	else if (type == TYPE_THINK)
		return (" is thinking");
	else if (type == TYPE_OVER)
		return ("number of times they must eat reached");
	return (" died");
}

void	display_message(t_philo *philo, int type)
{
	static int	done = 0;

	pthread_mutex_lock(&philo->state->message);
	if (!done)
	{
		ft_putnbr_fd(get_time() - philo->state->start, 1);
		write(1, "\t", 1);
		if (type != TYPE_OVER)
			ft_putnbr_fd(philo->position + 1, 1);
		if (type >= TYPE_DIED)
			done = 1;
		printf("%s\n", get_message(type));
	}
	pthread_mutex_unlock(&philo->state->message);
}
