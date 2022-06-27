/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcierra <alcierra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 00:00:00 by alcierra          #+#    #+#             */
/*   Updated: 2022/06/27 00:00:00 by alcierra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	philo_action_take_first_fork(t_main *m, t_philo *p)
{
	struct timeval	curr;

	p->status = PHILOSOPHER_TAKE_FORK | FORK_1;
	pthread_mutex_unlock(&(p->mutex));
	gettimeofday(&curr, NULL);
	pthread_mutex_lock(&(p->first_fork->mutex));
	gettimeofday(&curr, NULL);
	print_philosopher(milliseconds_from(&(p->parent->start), &curr),
		p->id, PHILOSOPHER_TAKE_FORK, m);
	return (0);
}

int	philo_action_take_second_fork(t_main *m, t_philo *p)
{
	struct timeval	curr;

	p->status = PHILOSOPHER_TAKE_FORK | FORK_2;
	pthread_mutex_unlock(&(p->mutex));
	pthread_mutex_lock(&(p->second_fork->mutex));
	gettimeofday(&curr, NULL);
	print_philosopher(milliseconds_from(&(p->parent->start), &curr),
		p->id, PHILOSOPHER_TAKE_FORK, m);
	return (0);
}

int	philo_action_eat(t_main *m, t_philo *p)
{
	struct timeval	curr;

	p->status = PHILOSOPHER_EAT;
	gettimeofday(&curr, NULL);
	p->last_eaten = curr.tv_sec * 1000 + curr.tv_usec / 1000;
	p->eaten++;
	print_philosopher(milliseconds_from(&(p->parent->start), &curr),
		p->id, PHILOSOPHER_EAT, m);
	if (p->eaten == m->philo_must_eat)
	{
		pthread_mutex_unlock(&(p->mutex));
		pthread_mutex_lock(&(m->main_mutex));
		m->enough_eaten_count++;
		if (m->enough_eaten_count == m->count)
			m->force_stop = 1;
		pthread_mutex_unlock(&(m->main_mutex));
	}
	else
		pthread_mutex_unlock(&(p->mutex));
	ft_usleep(m->time_to_eat);
	pthread_mutex_unlock(&(p->second_fork->mutex));
	pthread_mutex_unlock(&(p->first_fork->mutex));
	return (0);
}

int	philo_action_sleep(t_main *m, t_philo *p)
{
	struct timeval	curr;

	p->status = PHILOSOPHER_SLEEP;
	gettimeofday(&curr, NULL);
	print_philosopher(milliseconds_from(&(p->parent->start), &curr),
		p->id, PHILOSOPHER_SLEEP, m);
	pthread_mutex_unlock(&(p->mutex));
	ft_usleep(m->time_to_sleep);
	return (0);
}

int	philo_action_think(t_main *m, t_philo *p)
{
	struct timeval	curr;

	p->status = PHILOSOPHER_THINK;
	gettimeofday(&curr, NULL);
	print_philosopher(milliseconds_from(&(p->parent->start), &curr),
		p->id, PHILOSOPHER_THINK, m);
	pthread_mutex_unlock(&(p->mutex));
	return (0);
}
