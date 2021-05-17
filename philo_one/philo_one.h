/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 11:01:40 by alilin            #+#    #+#             */
/*   Updated: 2021/05/17 11:09:33 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

# define TYPE_EAT 	0
# define TYPE_SLEEP 1
# define TYPE_FORK 	2
# define TYPE_THINK	3
# define TYPE_DIED 	4
# define TYPE_OVER 	5

struct s_philo;

typedef struct		s_option
{
	int				nb_philosopher;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_time_must_eat;
	int				current_eat_count;
	long			start;
	struct s_philo	*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	message;
	pthread_mutex_t	state;
}					t_option;

typedef struct		s_philo
{
	t_option		*state;
	int				position;
	int				eating;
	long			limit;
	long			last_eat;
	int				left_fork;
	int				right_fork;
	int				eat_count;
	pthread_mutex_t	mutex;
	pthread_mutex_t	eat_message;
}					t_philo;

int					ft_isdigit(char *str);
int					ft_atoi(const char *str);
int					ft_error(int err_nb);
int					ft_checkerror(char **av);
int					init(t_option *state, int ac, char **av);
void				init_philo(t_option *state);
int					init_mutex(t_option *state);
int					clear(t_option *state);
void				eat(t_philo *philo);
void				take_forks(t_philo *philo);
void				put_down_forks(t_philo *philo);
int					ft_strlen(char *str);
void				ft_putnbr_fd(int n, int fd);
long				get_time(void);
char				*get_message(int type);
void				display_message(t_philo *philo, int type);

#endif
