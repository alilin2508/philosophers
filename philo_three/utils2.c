/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 10:35:56 by alilin            #+#    #+#             */
/*   Updated: 2021/05/20 14:53:07 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	ft_usleep(long ms)
{
	long			start;

	start = get_time();
	while (get_time() < start + ms)
		usleep(50);
	return ;
}
