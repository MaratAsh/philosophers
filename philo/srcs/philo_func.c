/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcierra <alcierra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 00:00:00 by alcierra          #+#    #+#             */
/*   Updated: 2022/06/14 00:00:00 by alcierra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*philo_func_force_stop(t_philo *p, int after)
{
	int	stoped;
	int	count;

	pthread_mutex_lock(&(p->parent->main_mutex));
	stoped = p->parent->stopped;
	count = p->parent->count;
	pthread_mutex_unlock(&(p->parent->main_mutex));
	if (stoped == count - 1)
		return (0);
	if (after == PHILOSOPHER_EAT)
	{
		philo_action_sleep(p);
		philo_action_think(p);
	}
	return (0);
}

int	philo_last_func_check_eaten(t_philo *p, int eaten)
{
	if (p->parent->philo_must_eat > 0 && eaten > p->parent->philo_must_eat)
	{
		p->status = PHILOSOPHER_STOP;
		pthread_mutex_unlock(&(p->mutex));
		return (1);
	}
	return (0);
}

void	*philo_last_func(t_philo *p)
{
	int	eaten;

	pthread_mutex_lock(&(p->mutex));
	while (!philo_need_stop(p))
	{
		p->status = PHILOSOPHER_THINK;
		pthread_mutex_unlock(&(p->mutex));
		philo_action_take_left_fork(p, 0);
		if (philo_action_take_right_fork(p, 1))
			return (NULL);
		philo_action_eat(p, &eaten, 0);
		if (philo_check_force_stop(p, PHILOSOPHER_EAT))
			return (0);
		philo_action_sleep(p);
		if (philo_check_force_stop(p, PHILOSOPHER_SLEEP))
			return (0);
		philo_action_think(p);
		if (philo_last_func_check_eaten(p, eaten))
			return (NULL);
		pthread_mutex_lock(&(p->mutex));
	}
	return (NULL);
}

void	*philo_func(t_philo *p)
{
	int	eaten;

	pthread_mutex_lock(&(p->mutex));
	while (!philo_need_stop(p))
	{
		p->status = PHILOSOPHER_THINK;
		pthread_mutex_unlock(&(p->mutex));
		philo_action_take_right_fork(p, 0);
		if (philo_action_take_left_fork(p, 1))
			return (NULL);
		philo_action_eat(p, &eaten, 1);
		if (philo_check_force_stop(p, PHILOSOPHER_EAT))
			return (0);
		philo_action_sleep(p);
		if (philo_check_force_stop(p, PHILOSOPHER_SLEEP))
			return (0);
		philo_action_think(p);
		if (philo_last_func_check_eaten(p, eaten))
			return (NULL);
		pthread_mutex_lock(&(p->mutex));
	}
	return (NULL);
}

void	*philo_func_void(void *params)
{
	void	*r;
	t_philo	*p;

	p = (t_philo *) params;
	if (p->left == p->right)
	{
		ft_usleep(p->parent->time_to_die);
		print_philosopher(0, p->id,
			PHILOSOPHER_TAKE_FORK, &(p->parent->out_mutex));
		return (NULL);
	}
	if (p->id == p->parent->count)
		r = philo_last_func((t_philo *) params);
	else
		r = philo_func((t_philo *) params);
	return (r);
}
