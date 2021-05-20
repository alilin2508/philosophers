/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 11:02:30 by alilin            #+#    #+#             */
/*   Updated: 2021/05/20 14:50:27 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <fcntl.h>
# include <semaphore.h>
# include <pthread.h>
# include <signal.h>

# define TYPE_EAT 	0
# define TYPE_SLEEP 1
# define TYPE_FORK 	2
# define TYPE_THINK	3
# define TYPE_DIED 	4
# define TYPE_OVER 	5

# define SEMAPHORE_FORK		"SemaphoreFork"
# define SEMAPHORE_WRITE	"SemaphoreWrite"
# define SEMAPHORE_DEAD		"SemaphoreDead"
# define SEMAPHORE_DEADM	"SemaphoreDeadMessage"
# define SEMAPHORE_PHILO	"SemaphorePhilo"
# define SEMAPHORE_PHILOEAT	"SemaphorePhiloEat"

struct	s_philo;

typedef struct s_option
{
	int				nb_philosopher;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_time_must_eat;
	int				current_eat_count;
	long			start;
	struct s_philo	*philo;
	sem_t			*forks;
	sem_t			*message;
	sem_t			*dead_message;
	sem_t			*state;
}					t_option;

typedef struct s_philo
{
	t_option		*state;
	pid_t			pid;
	int				position;
	int				eating;
	long			limit;
	long			last_eat;
	int				eat_count;
	sem_t			*mutex;
	sem_t			*eat_message;
}					t_philo;

int					ft_isdigit(char *str);
int					ft_atoi(const char *str);
int					ft_error(int err_nb);
int					ft_checkerror(char **av);
int					init(t_option *state, int ac, char **av);
int					init_philo(t_option *state);
int					init_semaphore(t_option *state);
int					clear(t_option *state);
void				eat(t_philo *philo);
void				take_forks(t_philo *philo);
void				put_down_forks(t_philo *philo);
int					ft_strlen(char *str);
void				ft_putnbr_fd(int n, int fd);
long				get_time(void);
char				*get_message(int type);
void				display_message(t_philo *philo, int type);
sem_t				*ft_sem_open(char const *name, int value);
int					ft_strcpy(char *dst, const char *src);
char				*make_semaphore_name(char const *base, char *buffer, \
		int position);
void				*must_eat_count(void *state);
void				*monitor(void *philo);
void				*routine(void *philo);
int					start_threads(t_option *state);
void				ft_usleep(long ms);

#endif
