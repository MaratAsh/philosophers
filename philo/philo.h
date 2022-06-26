/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   philo.h											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: alcierra <alcierra@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/06/14 00:00:00 by alcierra		  #+#	#+#			 */
/*   Updated: 2022/06/14 00:00:00 by alcierra		 ###   ########.fr	   */
/*																			*/
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
	int				id;
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
	PHILOSOPHER_STOP = 0b1000,
	PHILOSOPHER_DIE = 0b11000,
};

typedef struct s_main
{
	int				count;
	int				stopped;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				philo_must_eat;
	int				stop;
	t_philo			*philosophers;
	t_watcher		*watchers;
	t_philo_fork	*p_forks;
	pthread_t		*threads;
	pthread_t		*threads_watcher;
	long long		start_milliseconds;
	struct timeval	start;
	pthread_mutex_t	out_mutex;
	pthread_mutex_t	main_mutex;
}				t_main;

size_t			ft_strlen(char *str);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
void			*philo_func(t_philo *params);
void			*philo_func_void(void *params);
void			*philo_watcher_func(t_watcher *params);
void			*philo_watcher_func_void(void *params);
int				ft_atoi(const char *str);
void			ft_usleep(long long millisecond);

void			*philo_func_force_stop(t_philo *p, int after);

// utils.c
int				set_long_long_in_string(char *str, long long int num);
long long int	ft_power(int num, int power);
long long int	milliseconds_from(struct timeval *since,
					struct timeval *current);

// philo_conditions.c
int				philo_need_stop(t_philo *p);
int				philo_does_someone_dead(t_main *m);
int				philo_check_force_stop(t_philo *p, int after);

// print_philosopher.c
void			print_philosopher(long long int timestamp,
					int philo_id, int status, pthread_mutex_t *mutex);

long long int	philo_get_time(t_philo *p, t_main *m,
					struct timeval *curr, int status);

// philo_action.c
int				philo_action_take_left_fork(t_philo *p, int flags);
int				philo_action_take_right_fork(t_philo *p, int flags);
int				philo_action_eat(t_philo *p, int *eaten, int i);
void			philo_action_sleep(t_philo *p);
void			philo_action_think(t_philo *p);

// parse.c
int				convert_parameter(int *ptr_num, char *name, char *arg);
int				parse(t_main *params, int count, char **argv);

// utils_2.c
void			philosophers_start(t_main *params);
void			philosophers_join(t_main *params);
void			philosophers_destroy(t_main *params);

#endif
