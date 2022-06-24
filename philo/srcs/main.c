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

void	allocate_memory(t_main *m)
{
	m->philosophers = (t_philo *) malloc(sizeof(t_philo) * m->count);
	m->watchers = (t_watcher *) malloc(sizeof(t_watcher) * m->count);
	m->p_forks = (t_philo_fork *) malloc(sizeof(t_philo_fork) * m->count);
	m->threads = (pthread_t *) malloc(sizeof(pthread_t) * m->count);
	m->threads_watcher = (pthread_t *) malloc(sizeof(pthread_t) * m->count);
}

void	create_philosophers_and_check_loop(t_main *params, int i)
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
}

int	create_philosophers_and_check(t_main *params)
{
	int	i;

	allocate_memory(params);
	if (!params->philosophers || !params->threads || !params->threads_watcher
		|| !params->p_forks || !params->watchers)
	{
		printf("Error: Malloc: cannot allocate memory\n");
		return (1);
	}
	memset((void *) params->philosophers, 0, sizeof(t_philo) * params->count);
	memset((void *) params->watchers, 0, sizeof(t_watcher) * params->count);
	memset((void *) params->p_forks, 0, sizeof(t_philo_fork) * params->count);
	i = 0;
	while (i < params->count)
	{
		create_philosophers_and_check_loop(params, i);
		i++;
	}
	return (0);
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
	memset((void *) &params, 0, sizeof(t_main));
	pthread_mutex_init(&(params.out_mutex), NULL);
	pthread_mutex_init(&(params.main_mutex), NULL);
	if (parse(&params, argc - 1, argv))
		return (0);
	if (create_philosophers_and_check(&params))
		return (0);
	philosophers_start(&params);
	philosophers_join(&params);
	philosophers_destroy(&params);
	pthread_mutex_destroy(&(params.out_mutex));
	pthread_mutex_destroy(&(params.main_mutex));
	return (0);
}
