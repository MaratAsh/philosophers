/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcierra <alcierra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 00:00:00 by alcierra          #+#    #+#             */
/*   Updated: 2022/06/26 00:00:00 by alcierra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_action_eat(t_main *m, t_philo *p)
{
	struct timeval	curr_time;

	sem_wait(p->sem_main);
	gettimeofday(&curr_time, NULL);
	print_philosopher(milliseconds_from(&(p->parent->start), &curr_time),
					  p->id, PHILOSOPHER_EAT, p->parent->sem_out);
	p->last_eaten = (curr_time.tv_sec - m->start.tv_sec) * 1000
					+ (curr_time.tv_usec - m->start.tv_usec) / 1000;
	p->eaten++;
	if (m->philo_must_eat > 0 && p->eaten == m->philo_must_eat)
	{
		sem_post(m->sem_enough_eaten);
	}
	sem_post(p->sem_main);
	ft_usleep(m->time_to_eat);
	sem_post(m->sem_get_forks);
	sem_post(m->sem_forks);
	sem_post(m->sem_forks);
}

void	philo_action_sleep(t_main *m, t_philo *p)
{
	struct timeval	curr_time;

	gettimeofday(&curr_time, NULL);
	print_philosopher(milliseconds_from(&(p->parent->start), &curr_time),
					  p->id, PHILOSOPHER_SLEEP, p->parent->sem_out);
	ft_usleep(m->time_to_sleep);
}
