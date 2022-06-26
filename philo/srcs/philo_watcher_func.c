/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_watcher_func.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcierra <alcierra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 00:00:00 by alcierra          #+#    #+#             */
/*   Updated: 2022/06/21 00:00:00 by alcierra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_watcher_func_if_die(t_watcher *params, int need_stop)
{
	struct timeval	curr_time;

	if (need_stop == PHILOSOPHER_DIE)
	{
		gettimeofday(&curr_time, NULL);
		print_philosopher(milliseconds_from(&(params->parent->start),
				&curr_time),
			params->philo->id, PHILOSOPHER_DIE, &(params->parent->out_mutex));
		pthread_mutex_lock(&(params->parent->main_mutex));
		params->parent->stop = 1;
		params->parent->stopped++;
		pthread_mutex_unlock(&(params->parent->main_mutex));
	}
}

void	philo_watcher_func_loop(t_main *m, t_watcher *params, int *nd)
{
	struct timeval	curr_time;
	long long int	curr;

	pthread_mutex_lock(&(params->philo->mutex));
	gettimeofday(&curr_time, NULL);
	curr = curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000;
	if (params->philo->last_eaten && curr > params->philo->last_eaten
		+ m->time_to_die)
	{
		params->philo->status = PHILOSOPHER_DIE;
		*nd = PHILOSOPHER_DIE;
	}
	if (m->philo_must_eat > 0 && params->philo->eaten >= m->philo_must_eat)
	{
		params->philo->status = PHILOSOPHER_STOP;
		*nd = PHILOSOPHER_STOP;
	}
	pthread_mutex_unlock(&(params->philo->mutex));
}

void	*philo_watcher_func(t_watcher *params)
{
	int		need_stop;
	void	*r;

	params->philo->last_eaten = params->philo->parent->start.tv_sec * 1000
		+ params->philo->parent->start.tv_usec / 1000;
	pthread_create(params->thread, NULL,
		philo_func_void, (void *) params->philo);
	need_stop = 0;
	while (!philo_does_someone_dead(params->parent))
	{
		need_stop = 10000000;
		philo_watcher_func_loop(params->parent, params, &need_stop);
		if (need_stop & PHILOSOPHER_STOP)
		{
			philo_watcher_func_if_die(params, need_stop);
			break ;
		}
	}
	pthread_join(*(params->thread), &r);
	return (r);
}

void	*philo_watcher_func_void(void *params)
{
	void	*r;

	r = philo_watcher_func((t_watcher *) params);
	return (r);
}
