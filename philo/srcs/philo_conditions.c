/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_conditions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcierra <alcierra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 00:00:00 by alcierra          #+#    #+#             */
/*   Updated: 2022/06/24 00:00:00 by alcierra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	philo_does_someone_dead(t_main *m)
{
	int	stop;

	pthread_mutex_lock(&(m->main_mutex));
	stop = m->stop;
	pthread_mutex_unlock(&(m->main_mutex));
	if (stop)
		return (1);
	return (0);
}

int	philo_need_stop(t_philo *p)
{
	if (p->status & PHILOSOPHER_STOP)
		return (1);
	if (philo_does_someone_dead(p->parent))
		return (1);
	return (0);
}

int	philo_check_force_stop(t_philo *p, int after)
{
	pthread_mutex_lock(&(p->mutex));
	if (philo_need_stop(p))
	{
		pthread_mutex_unlock(&(p->mutex));
		philo_func_force_stop(p, after);
		return (1);
	}
	pthread_mutex_unlock(&(p->mutex));
	return (0);
}
