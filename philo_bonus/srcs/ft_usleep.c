/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcierra <alcierra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 00:00:00 by alcierra          #+#    #+#             */
/*   Updated: 2022/06/21 00:00:00 by alcierra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_usleep(long long millisecond)
{
	struct timeval	current_time;
	struct timeval	start_time;
	long long		time;

	gettimeofday(&current_time, NULL);
	gettimeofday(&start_time, NULL);
	time = 0;
	while (time < millisecond)
	{
		usleep(300);
		gettimeofday(&current_time, NULL);
		time = (current_time.tv_sec - start_time.tv_sec) * 1000
			+ (current_time.tv_usec - start_time.tv_usec) / 1000;
	}
}
