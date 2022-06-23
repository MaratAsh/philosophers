/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcierra <alcierra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 00:00:00 by alcierra          #+#    #+#             */
/*   Updated: 2022/06/14 00:00:00 by alcierra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	create_philosophers_and_check(t_main *params)
{
	int	i;

	params->philosophers = (t_philo *) malloc(sizeof(t_philo) * params->count);
	params->watchers = (t_watcher *) malloc(sizeof(t_watcher) * params->count);
	params->p_forks = (t_philo_fork *) malloc(sizeof(t_philo_fork) * params->count);
	params->threads = (pthread_t *) malloc(sizeof(pthread_t) * params->count);
	params->threads_watcher = (pthread_t *) malloc(sizeof(pthread_t)
		* params->count);
	if (!params->philosophers || !params->threads || !params->threads_watcher
		|| !params->p_forks || !params->watchers)
	{
		printf("Error: Malloc: cannot allocate memory\n");
		exit(0);
	}
	memset((void *) params->philosophers, 0, sizeof(t_philo) * params->count);
	memset((void *) params->watchers, 0, sizeof(t_watcher) * params->count);
	memset((void *) params->p_forks, 0, sizeof(t_philo_fork) * params->count);
	i = 0;
	while (i < params->count)
	{
		params->watchers[i].id = i + 1;
		params->watchers[i].parent = params;
		params->watchers[i].philo = &(params->philosophers[i]);
		params->philosophers[i].parent = params;
		params->philosophers[i].eaten = 0;
		params->philosophers[i].id = i + 1;
		params->philosophers[i].left = &(params->p_forks[i]);
		if (i == 0)
			params->philosophers[i].right = params->p_forks + params->count - 1;
		else
			params->philosophers[i].right = &(params->p_forks[i - 1]);
		params->p_forks[i].id = i + 1;
		pthread_mutex_init(&(params->p_forks[i].mutex), NULL);
		pthread_mutex_init(&(params->philosophers[i].mutex), NULL);
		i++;
	}
}

void	philosophers_start_philo(t_main *params, int i)
{
	params->watchers[i].thread = params->threads + i;
	pthread_create(params->threads_watcher + i, NULL,
				   philo_watcher_func_void, (void *) &(params->watchers[i]));
}

void	philo_print_all(t_main *m)
{
	int	i;

	i = 0;
	while (i < m->count)
	{
		print_philosopher(0, m->philosophers[i].id,
						  PHILOSOPHER_THINK, &(m->out_mutex));
		i++;
	}
}

void	philosophers_start(t_main *params)
{
	int				i;
	struct timeval	current_time;
	long long int	l;

	i = 0;
	gettimeofday(&(params->start), NULL);
	philo_print_all(params);
	while (i < params->count)
	{
		philosophers_start_philo(params, i);
		i += 2;
	}
	i = 1;
	gettimeofday(&current_time, NULL);
	l = (current_time.tv_sec - params->start.tv_sec) * 1000
			+ (current_time.tv_usec - params->start.tv_usec) / 1000;
	ft_usleep((long long int) params->time_to_eat - l);
	while (i < params->count)
	{
		philosophers_start_philo(params, i);
		i += 2;
	}
}

void	philosophers_join(t_main *params)
{
	int		i;
	void	*result;

	i = 0;
	while (i < params->count)
	{
		pthread_join(params->threads_watcher[i], &result);
		pthread_mutex_destroy(&(params->p_forks->mutex));
		i++;
	}
}

void	philosophers_destroy(t_main *params)
{
	free(params->philosophers);
	free(params->watchers);
	free(params->p_forks);
	free(params->threads);
	free(params->threads_watcher);
}

void convert_parameter(int *ptr_num, char *name, char *arg)
{
	*ptr_num = ft_atoi(arg);
	if (*ptr_num <= 0)
	{
		printf("Error: Arguments: %s is cannot be negative\n", name);
		exit(0);
	}
}

int	main(int argc, char *argv[])
{
	t_main	params;

	if (argc != 5 && argc != 6)
	{
		printf("Usage:\n%s number_of_philosophers "
			   "time_to_die time_to_eat time_to_sleep "
			   "[number_of_times_each_philosopher_must_eat]\n", argv[0]);
		return (0);
	}
    params.stop = 0;
	pthread_mutex_init(&(params.out_mutex), NULL);
	pthread_mutex_init(&(params.main_mutex), NULL);
	convert_parameter(&(params.count), "count", argv[1]);
	convert_parameter(&(params.time_to_die), "time_to_die", argv[2]);
	convert_parameter(&(params.time_to_eat), "time_to_eat", argv[3]);
	convert_parameter(&(params.time_to_sleep), "time_to_sleep", argv[4]);
	if (argc == 6)
		convert_parameter(&(params.philo_must_eat), "philo_must_eat", argv[5]);
	else
		params.philo_must_eat = -1;
	create_philosophers_and_check(&params);
	philosophers_start(&params);
	philosophers_join(&params);
	philosophers_destroy(&params);
	pthread_mutex_destroy(&(params.out_mutex));
	pthread_mutex_destroy(&(params.main_mutex));
	return (0);
}
