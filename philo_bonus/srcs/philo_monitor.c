/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcierra <alcierra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 00:00:00 by alcierra          #+#    #+#             */
/*   Updated: 2022/06/24 00:00:00 by alcierra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	philo_check_stop_monitor(t_main *m)
{
	int	i;

	sem_wait(m->sem_need_stop);
	i = 0;
	while (i < m->count)
	{
		kill(m->pid_forks[i], SIGINT);
		i++;
	}
	return (0);
}

void	*philo_check_stop_monitor_void(void *m)
{
	philo_check_stop_monitor((t_main *) m);
	return (0);
}

void	*philo_monitor_enough(void *ptr)
{
	t_main	*m;
	int		stopped;

	m = (t_main *) ptr;
	sem_wait(m->sem_edit);
	stopped = m->stopped;
	sem_post(m->sem_edit);
	while (stopped < m->count)
	{
		sem_wait(m->sem_enough_eaten);
		sem_wait(m->sem_edit);
		m->stopped++;
		stopped = m->stopped;
		sem_post(m->sem_edit);
	}
	sem_post(m->sem_need_stop);
	return (0);
}

int	philo_monitor(t_main *m)
{
	pthread_t	p;
	int			p_w;
	void		*r;

	p_w = pthread_create(&p, 0, philo_check_stop_monitor_void, (void *) m);
	if (m->philo_must_eat > 0)
	{
		pthread_create(&(m->monitor_enough_thread), 0,
			philo_monitor_enough, (void *) m);
	}
	if (p_w == 0)
		pthread_join(p, &r);
	return (0);
}
