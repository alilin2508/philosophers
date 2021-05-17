/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 11:01:31 by alilin            #+#    #+#             */
/*   Updated: 2021/05/17 11:01:34 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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
		write(1, get_message(type), ft_strlen(get_message(type)));
	}
	pthread_mutex_unlock(&philo->state->message);
}
