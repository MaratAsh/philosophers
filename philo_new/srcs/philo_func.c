/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcierra <alcierra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 00:00:00 by alcierra          #+#    #+#             */
/*   Updated: 2022/06/26 00:00:00 by alcierra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int 	philo_need_stop(t_main *m, t_philo *p)
{
	int force_stop;

	pthread_mutex_lock(&(m->main_mutex));
	force_stop = m->force_stop;
	pthread_mutex_unlock(&(m->main_mutex));
	if (force_stop)
		return (1);
	pthread_mutex_lock(&(p->mutex));
	force_stop = p->status;
	pthread_mutex_unlock(&(p->mutex));
	if (force_stop & PHILOSOPHER_STOP)
		return (1);
	return (0);
}

void	*philo_func(t_philo *p)
{
	t_main			*m;
	int 			status;

	m = p->parent;
	while (!philo_need_stop(m, p))
	{
		pthread_mutex_lock(&(p->mutex));
		status = p->status;
		if (status & PHILOSOPHER_STOP || status & PHILOSOPHER_DIE)
		{
			pthread_mutex_unlock(&(p->mutex));
			break;
		}
		if (status == PHILOSOPHER_THINK)
		{
			philo_action_take_first_fork(m, p);
		}
		else if (status & PHILOSOPHER_EAT)
		{
			philo_action_sleep(m, p);
		}
		else if ((status & PHILOSOPHER_TAKE_FORK) && (status & FORK_2))
		{
			philo_action_eat(m, p);
		}
		else if ((status & PHILOSOPHER_TAKE_FORK) && (status & FORK_1))
		{
			philo_action_take_second_fork(m, p);
		}
		else if (status & PHILOSOPHER_SLEEP)
		{
			philo_action_think(m, p);
		}
		else
			pthread_mutex_unlock(&(p->mutex));
	}
	return (0);
}

void	*philo_func_void(void *ptr)
{
	t_philo	*p;

	p = (t_philo *) ptr;
	if (p->first_fork == p->second_fork)
	{
		print_philosopher(0, p->id, PHILOSOPHER_TAKE_FORK, p->parent);
		return (NULL);
	}
	return (philo_func(p));
}
