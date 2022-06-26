/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcierra <alcierra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 00:00:00 by alcierra          #+#    #+#             */
/*   Updated: 2022/06/24 00:00:00 by alcierra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_die_check(t_main *m, t_philo *p)
{
	struct timeval	curr_time;
	long long int	curr;

	gettimeofday(&curr_time, NULL);
	curr = (curr_time.tv_sec - m->start.tv_sec) * 1000
		+ (curr_time.tv_usec - m->start.tv_usec) / 1000;
	if (p->last_eaten + m->time_to_die < curr)
	{
		print_philosopher(milliseconds_from(&(m->start), &curr_time),
			p->id, PHILOSOPHER_DIE, p->parent->sem_out);
		sem_post(m->sem_need_stop);
		exit(0);
	}
}

void	*philo_monitor_func(void *pptr)
{
	t_philo	*p;
	t_main	*m;
	struct timeval	curr_time;
	long long int	t;

	p = (t_philo *) pptr;
	m = p->parent;
	while (1)
	{
		sem_wait(p->sem_main);
		philo_die_check(m, p);
		sem_post(p->sem_main);
		sem_wait(p->sem_main);
		gettimeofday(&curr_time, NULL);
		t = m->time_to_die - ((curr_time.tv_sec - m->start.tv_sec) * 1000
		+ (curr_time.tv_usec - m->start.tv_usec) / 1000 - p->last_eaten);
		sem_post(p->sem_main);
		if (t < 0)
			t = 0;
		ft_usleep(t);
	}
	return (0);
}

void	philo_func(t_main *m, t_philo *p)
{
	struct timeval	curr_time;

	if (pthread_create(&(p->monitor_die), 0, philo_monitor_func, (void *) p) == 0)
		pthread_detach(p->monitor_die);
	p->eaten = 0;
	while (1)
	{
		sem_wait(m->sem_get_forks);
		sem_wait(m->sem_forks);
		gettimeofday(&curr_time, NULL);
		print_philosopher(milliseconds_from(&(p->parent->start), &curr_time),
			p->id, PHILOSOPHER_TAKE_FORK, p->parent->sem_out);
		sem_wait(m->sem_forks);
		gettimeofday(&curr_time, NULL);
		print_philosopher(milliseconds_from(&(p->parent->start), &curr_time),
			p->id, PHILOSOPHER_TAKE_FORK, p->parent->sem_out);
		philo_action_eat(m, p);
		philo_action_sleep(m, p);
		gettimeofday(&curr_time, NULL);
		print_philosopher(milliseconds_from(&(p->parent->start), &curr_time),
			p->id, PHILOSOPHER_THINK, p->parent->sem_out);
	}
}
