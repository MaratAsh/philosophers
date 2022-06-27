/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcierra <alcierra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 00:00:00 by alcierra          #+#    #+#             */
/*   Updated: 2022/06/26 00:00:00 by alcierra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	philo_monitor_loop(t_main *m, t_philo *p)
{
	struct timeval	curr_time;
	long long int	curr;
	long long int	last_eaten;

	if (m->enough_eaten_count == m->count)
		return (1);
	pthread_mutex_unlock(&(m->main_mutex));
	pthread_mutex_lock(&(p->mutex));
	gettimeofday(&curr_time, NULL);
	curr = curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000;
	last_eaten = p->last_eaten;
	if (p->last_eaten + m->time_to_die < curr)
	{
		print_philosopher(milliseconds_from(&(m->start), &curr_time),
			p->id, PHILOSOPHER_DIE, m);
		p->status = PHILOSOPHER_DIE;
		pthread_mutex_lock(&(m->main_mutex));
		m->force_stop = 1;
		pthread_mutex_unlock(&(m->main_mutex));
	}
	pthread_mutex_unlock(&(p->mutex));
	pthread_mutex_lock(&(m->main_mutex));
	return (0);
}

void	philo_monitor(t_philo *p)
{
	t_main			*m;

	m = p->parent;
	pthread_mutex_lock(&(m->main_mutex));
	while (m->force_stop == 0)
	{
		if (philo_monitor_loop(m, p))
		{
			m->force_stop = 1;
			break ;
		}
	}
	pthread_mutex_unlock(&(m->main_mutex));
	pthread_mutex_lock(&(p->mutex));
	p->status = PHILOSOPHER_STOP;
	pthread_mutex_unlock(&(p->mutex));
}

void	philo_monitor_sleep(t_main *m)
{
	struct timeval	curr_time;
	long long int	l;

	gettimeofday(&curr_time, NULL);
	l = curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000;
	l = m->start_milliseconds - l;
	if (m->time_to_eat + m->time_to_sleep > m->time_to_die)
		l = (m->time_to_die - l) / 2;
	else
		l = (m->time_to_eat + m->time_to_sleep - l) / 2 ;
	if (l > 0)
		ft_usleep(l);
}

void	*philo_monitor_void(void *ptr)
{
	t_philo	*p;
	int		run;
	void	*r;

	p = (t_philo *) ptr;
	p->last_eaten = p->parent->start_milliseconds;
	run = pthread_create(p->thread_main, NULL, philo_func_void, ptr);
	philo_monitor_sleep(p->parent);
	philo_monitor(p);
	if (run == 0)
		pthread_join(*p->thread_main, &r);
	return (NULL);
}
