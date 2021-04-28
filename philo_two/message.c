#include "philo_two.h"

char	*get_message(int type)
{
	if (type == TYPE_EAT)
		return (" is eating\n");
	else if (type == TYPE_SLEEP)
		return (" is sleeping\n");
	else if (type == TYPE_FORK)
		return (" has taken a fork\n");
	else if (type == TYPE_THINK)
		return (" is thinking\n");
	else if (type == TYPE_OVER)
		return ("number of times they must eat reached\n");
	return (" died\n");
}

int	display_message(t_philo *philo, int type)
{
	static int	done = 0;
	int			ret;

	if (sem_wait(philo->state->message) != 0)
		return (1);
	ret = 1;
	if (!done)
	{
		ft_putnbr_fd(get_time() - philo->state->start, 1);
		write(1, "\t", 1);
		if (type != TYPE_OVER)
			ft_putnbr_fd(philo->position + 1, 1);
		if (type >= TYPE_DIED)
			done = 1;
		write(1, get_message(type), ft_strlen(get_message(type)));
		ret = 0;
	}
	if (sem_post(philo->state->message))
		return (1);
	return (ret);
}
