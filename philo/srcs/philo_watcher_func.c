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


void	*philo_watcher_func(t_watcher *params)
{
	void 			*r;
	t_main			*m;
	struct timeval	curr_time;
	long long int	curr;
	int 			need_stop;

	m = params->parent;
	r = 0;
	need_stop = 0;
	while (1)
	{
		pthread_mutex_lock(&(params->philo->mutex));
		gettimeofday(&curr_time, NULL);
		curr = curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000;
		if (curr > params->philo->last_eaten + m->time_to_die)
		{
			params->philo->status = PHILOSOPHER_DIE;
			need_stop = 1;
		}
		if (m->philo_must_eat > 0 && params->philo->eaten >= m->philo_must_eat)
		{
			params->philo->status = PHILOSOPHER_STOP;
			need_stop = 1;
		}
		pthread_mutex_unlock(&(params->philo->mutex));
		if (need_stop)
		{
			pthread_join(*(params->thread), &r);
			break;
		}
	}
	return (r);
}

void	*philo_watcher_func_void(void *params)
{
	void *r;

	r = philo_watcher_func((t_watcher *) params);
	return (r);
}
