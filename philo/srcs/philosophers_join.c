/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_join.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcierra <alcierra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 00:00:00 by alcierra          #+#    #+#             */
/*   Updated: 2022/06/27 00:00:00 by alcierra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	philosophers_join(t_main *m)
{
	int		i;
	void	*r;

	i = 0;
	while (i < m->count)
	{
		pthread_join(m->threads_monitor[i], &r);
		i++;
	}
	return (0);
}
