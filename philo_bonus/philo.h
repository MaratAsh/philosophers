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
# include <sys/shm.h>
# include <sys/types.h>
# include <signal.h>

# define SEMAPHORE_EDIT "philo_edit"
# define SEMAPHORE_NEED_STOP "philo_need_stop"
# define SEMAPHORE_OUT "philo_out"
# define SEMAPHORE_GET_FORKS "philo_get_forks"
# define SEMAPHORE_FORKS "philo_forks"
# define SEMAPHORE_ENOUGH_EATEN "philo_enough_eaten"

typedef struct s_philo
{
	int				id;
	int				eaten;
	int				status;
	long long int	last_eaten;
	sem_t			*sem_main;
	char			name_sem_main[20];
	pthread_t		monitor_die;
	struct s_main	*parent;
}				t_philo;

typedef struct s_main
{
	int				count;
	int				need_stop;
	int				stopped;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				philo_must_eat;
	t_philo			*philosophers;
	pid_t			*pid_forks;
	struct timeval	start;
	sem_t			*sem_edit;
	sem_t			*sem_get_forks;
	sem_t			*sem_out;
	sem_t			*sem_need_stop;
	sem_t			*sem_forks;
	sem_t			*sem_enough_eaten;
	pthread_t		monitor_enough_thread;
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
void			philo_action_eat(t_main *m, t_philo *p);
void			philo_action_sleep(t_main *m, t_philo *p);

int				philosophers_start(t_main *m);

void			philo_func(t_main *m, t_philo *p);

int				philo_monitor(t_main *m);

void			philosophers_init(t_main *m);
void			philosophers_destroy(t_main *m);
void			philosophers_destroy_semaphores(t_main *m);

#endif
