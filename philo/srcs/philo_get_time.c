/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcierra <alcierra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 00:00:00 by alcierra          #+#    #+#             */
/*   Updated: 2022/06/23 00:00:00 by alcierra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long long int	philo_get_time(t_philo *p, t_main *m,
		struct timeval *curr, int status)
{
	long long int	t;

	(void) p;
	(void) curr;
	t = 0;
	if (status == PHILOSOPHER_SLEEP)
		t = m->time_to_sleep;
	else if (status == PHILOSOPHER_EAT)
		t = m->time_to_eat;
	return (t);
}
