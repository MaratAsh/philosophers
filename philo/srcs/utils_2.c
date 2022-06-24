/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcierra <alcierra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 00:00:00 by alcierra          #+#    #+#             */
/*   Updated: 2022/06/24 00:00:00 by alcierra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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
