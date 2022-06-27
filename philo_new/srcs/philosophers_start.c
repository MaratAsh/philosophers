/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_start.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcierra <alcierra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 00:00:00 by alcierra          #+#    #+#             */
/*   Updated: 2022/06/26 00:00:00 by alcierra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	philosophers_start_monitor(t_main *m, int i)
{
	pthread_create(m->threads_monitor + i, NULL,
		philo_monitor_void, (void *)(m->philosophers + i));
	return (0);
}

void	philosophers_wait(t_main *m)
{
	struct timeval	current_time;
	long long int	l;

	gettimeofday(&current_time, NULL);
	l = (current_time.tv_sec - m->start.tv_sec) * 1000
		+ (current_time.tv_usec - m->start.tv_usec) / 1000;
	if (m->time_to_eat > m->time_to_die)
	{
		l = m->time_to_die - l;
		if (l > 0)
			l = l / 2;
		else
			l = 0;
	}
	else
		l = m->time_to_eat - l;
	if (l > 0)
		ft_usleep(l);
}

int	philosophers_start_print_think(t_main *m)
{
	int	i;

	i = 1;
	while (i < m->count)
	{
		print_philosopher(0, m->philosophers[i].id,
			PHILOSOPHER_THINK, m);
		i += 2;
	}
	if (m->count % 2 == 1)
		print_philosopher(0, m->philosophers[m->count - 1].id,
			PHILOSOPHER_THINK, m);
	return (0);
}

int	philosophers_start(t_main *m)
{
	int	i;

	i = 0;
	philosophers_start_print_think(m);
	gettimeofday(&(m->start), NULL);
	m->start_milliseconds = m->start.tv_sec * 1000 + m->start.tv_usec / 1000;
	while (i < m->count)
	{
		philosophers_start_monitor(m, i);
		i += 2;
	}
	if (m->count == 1)
		return (0);
	philosophers_wait(m);
	i = 1;
	while (i < m->count)
	{
		philosophers_start_monitor(m, i);
		i += 2;
	}
	return (0);
}
