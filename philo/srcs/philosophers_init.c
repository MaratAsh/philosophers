/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcierra <alcierra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 00:00:00 by alcierra          #+#    #+#             */
/*   Updated: 2022/06/25 00:00:00 by alcierra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	philosophers_init_loop(t_main *m, int i)
{
	m->philosophers[i].id = i + 1;
	m->p_forks[i].id = i + 1;
	m->philosophers[i].thread_main = m->threads + i;
	m->philosophers[i].thread_monitor = m->threads_monitor + i;
	m->philosophers[i].right = m->p_forks + i;
	if (i + 1 == m->count)
		m->philosophers[i].left = m->p_forks;
	else
		m->philosophers[i].left = m->p_forks + i + 1;
	if (m->philosophers[i].left < m->philosophers[i].right)
	{
		m->philosophers[i].first_fork = m->philosophers[i].left;
		m->philosophers[i].second_fork = m->philosophers[i].right;
	}
	else
	{
		m->philosophers[i].first_fork = m->philosophers[i].right;
		m->philosophers[i].second_fork = m->philosophers[i].left;
	}
	m->philosophers[i].status = PHILOSOPHER_THINK;
	m->philosophers[i].parent = m;
	m->philosophers[i].eaten = 0;
	pthread_mutex_init(&(m->p_forks[i].mutex), NULL);
	pthread_mutex_init(&(m->philosophers[i].mutex), NULL);
	return (0);
}

int	philosophers_init(t_main *m)
{
	int	i;

	pthread_mutex_init(&(m->out_mutex), NULL);
	pthread_mutex_init(&(m->main_mutex), NULL);
	memset((void *) m->philosophers, 0, sizeof(t_philo) * m->count);
	memset((void *) m->p_forks, 0, sizeof(t_philo_fork) * m->count);
	i = 0;
	m->p_forks[m->count - 1].id = m->count;
	while (i < m->count)
	{
		philosophers_init_loop(m, i);
		i++;
	}
	return (0);
}
