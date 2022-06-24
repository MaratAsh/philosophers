/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_philosopher.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcierra <alcierra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 00:00:00 by alcierra          #+#    #+#             */
/*   Updated: 2022/06/23 00:00:00 by alcierra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_philosopher(long long int timestamp, int philo_id, int status,
					sem_t *sem_out)
{
	char	str[21 + 1 + 12 + 1 + 17];
	int		len;

	(void) sem_out;
	len = set_long_long_in_string(str, timestamp);
	str[len] = ' ';
	len++;
	len += set_long_long_in_string(str + len, (long long int) philo_id);
	str[len] = ' ';
	if (status == PHILOSOPHER_TAKE_FORK)
		len += ft_strlcpy(str + len + 1, "has taken a fork\n", 18);
	else if (status == PHILOSOPHER_EAT)
		len += ft_strlcpy(str + len + 1, "is eating\n", 11);
	else if (status == PHILOSOPHER_SLEEP)
		len += ft_strlcpy(str + len + 1, "is sleeping\n", 13);
	else if (status == PHILOSOPHER_THINK)
		len += ft_strlcpy(str + len + 1, "is thinking\n", 13);
	else if (status == PHILOSOPHER_DIE)
		len += ft_strlcpy(str + len + 1, "died\n", 6);
	str[len + 1] = 0;
	// pthread_mutex_lock(mutex);
	write(1, str, ft_strlen(str));
	// pthread_mutex_unlock(mutex);
}
