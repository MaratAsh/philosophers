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
# include <sys/time.h>

typedef struct s_philo_fork
{
	pthread_mutex_t	mutex;
	unsigned int	id;
}				t_philo_fork;

typedef struct s_philo
{
	unsigned int	id;
	int				eaten;
	int				status;
	long long int	last_eaten;
	t_philo_fork	*left;
	t_philo_fork	*right;
	pthread_mutex_t	mutex;
	struct s_main	*parent;
}				t_philo;

typedef struct s_philo_watcher
{
	unsigned int	id;
	t_philo			*philo;
	pthread_t		*thread;
	struct s_main	*parent;
}				t_watcher;

enum {
	PHILOSOPHER_THINK = 0,
	PHILOSOPHER_EAT = 1,
	PHILOSOPHER_SLEEP = 2,
	PHILOSOPHER_TAKE_FORK = 4,
	PHILOSOPHER_STOP = 8,
	PHILOSOPHER_DIE = 16,
};
typedef struct s_main
{
	int				count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				philo_must_eat;
	t_philo			*philosophers;
	t_watcher		*watchers;
	t_philo_fork	*p_forks;
	pthread_t		*threads;
	pthread_t		*threads_watcher;
	long long		start_milliseconds;
	struct timeval	start;
	pthread_mutex_t	out_mutex;
}				t_main;

size_t	ft_strlen(char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
void	*philo_func(t_philo *params);
void	*philo_func_void(void *params);
void	*philo_watcher_func(t_watcher *params);
void	*philo_watcher_func_void(void *params);
int		ft_atoi(const char *str);
void	ft_usleep(long long millisecond);

#endif
