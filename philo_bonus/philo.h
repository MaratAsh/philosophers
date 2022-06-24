/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcierra <alcierra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 00:00:00 by alcierra          #+#    #+#             */
/*   Updated: 2022/06/14 00:00:00 by alcierra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				eaten;
	int				status;
	long long int	last_eaten;
	pid_t			pid;
	struct s_main	*parent;
}				t_philo;


typedef struct s_main
{
	int				count;
	int				need_stop;
	int				stoped;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				philo_must_eat;
	t_philo			*philosophers;
	pid_t			*pid_forks;
	struct timeval	start;
	sem_t			out;
	sem_t			forks;
}				t_main;

enum {
	PHILOSOPHER_THINK = 0,
	PHILOSOPHER_EAT = 1,
	PHILOSOPHER_SLEEP = 2,
	PHILOSOPHER_TAKE_FORK = 4,
	PHILOSOPHER_STOP = 0b1000,
	PHILOSOPHER_DIE = 0b11000,
};

int				ft_atoi(const char *str);
size_t			ft_strlen(char *str);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
void			ft_usleep(long long millisecond);

// utils.c
int				set_long_long_in_string(char *str, long long int num);
long long int	ft_power(int num, int power);
long long int	milliseconds_from(struct timeval *since,
					struct timeval *current);

// print_philosopher.c
void			print_philosopher(long long int timestamp,
					int philo_id, int status, sem_t *sem_out);

long long int	philo_get_time(t_philo *p, t_main *m,
					struct timeval *curr, int status);

// parse.c
int				convert_parameter(int *ptr_num, char *name, char *arg);
int				parse(t_main *params, int count, char **argv);

// philo_action.c
int				philo_action_take_fork(t_philo *p, int flags);
int				philo_action_eat(t_philo *p);
int				philo_action_sleep(t_philo *p);
int				philo_action_think(t_philo *p);

int				philo_start(t_main *m);

void			philo_func(t_main *m, t_philo *p);
void			philo_last_func(t_main *m, t_philo *p);

int				philo_monitor(t_main *m);

#endif
