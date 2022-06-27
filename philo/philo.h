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
	t_philo_fork	*first_fork;
	t_philo_fork	*second_fork;
	pthread_mutex_t	mutex;
	pthread_t		*thread_monitor;
	pthread_t		*thread_main;
	struct s_main	*parent;
}				t_philo;

enum {
	PHILOSOPHER_THINK =		0,
	PHILOSOPHER_EAT =		0b00001,
	PHILOSOPHER_SLEEP =		0b00010,
	PHILOSOPHER_TAKE_FORK =	0b00100,
	FORK_1 =			0b100000000,
	FORK_2 =			0b010000000,
	PHILOSOPHER_STOP =		0b01000,
	PHILOSOPHER_DIE =		0b11000,
};

typedef struct s_main
{
	int				count;
	int				enough_eaten_count;
	int				stopped;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				philo_must_eat;
	int				force_stop;
	int				stop;
	int				die;
	t_philo			*philosophers;
	t_philo_fork	*p_forks;
	pthread_t		*threads;
	pthread_t		*threads_monitor;
	long long		start_milliseconds;
	struct timeval	start;
	pthread_mutex_t	out_mutex;
	pthread_mutex_t	main_mutex;
}				t_main;

size_t			ft_strlen(char *str);
int				ft_atoi(const char *str);
void			ft_usleep(long long millisecond);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);

void			*philo_monitor_void(void *p);
void			*philo_func(t_philo *p);
void			*philo_func_void(void *params);

void			*philo_watcher_func_void(void *params);

void			*philo_func_force_stop(t_philo *p, int after);

// utils.c
int				set_long_long_in_string(char *str, long long int num);
long long int	ft_power(int num, int power);
long long int	milliseconds_from(struct timeval *since,
					struct timeval *current);

// philo_conditions.c
int				philo_need_stop(t_main *m, t_philo *p);

// print_philosopher.c
void			print_philosopher(long long int timestamp,
					int philo_id, int status, t_main *m);

long long int	philo_get_time(t_philo *p, t_main *m,
					struct timeval *curr, int status);

// philo_action.c
int				philo_action_take_first_fork(t_main *m, t_philo *p);
int				philo_action_take_second_fork(t_main *m, t_philo *p);
int				philo_action_eat(t_main *m, t_philo *p);
int				philo_action_sleep(t_main *m, t_philo *p);
int				philo_action_think(t_main *m, t_philo *p);

// parse.c
int				convert_parameter(int *ptr_num, char *name, char *arg);
int				parse(t_main *params, int count, char **argv);

// philosophers_init.c
int				philosophers_init(t_main *m);

// philosophers_start.c
int				philosophers_start(t_main *m);

// philosophers_join.c
int				philosophers_join(t_main *m);

// philosophers_destroy.c
int				philosophers_destroy(t_main *m);
int				philosophers_destroy_free_memory(t_main *m);

void			*philo_monitor_void(void *ptr);

#endif
