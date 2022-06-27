/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_print.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcierra <alcierra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 00:00:00 by alcierra          #+#    #+#             */
/*   Updated: 2022/06/23 00:00:00 by alcierra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	print_philosopher_check_die(t_main *m, int status)
{
	pthread_mutex_lock(&(m->main_mutex));
	if (m->die)
	{
		pthread_mutex_unlock(&(m->main_mutex));
		return (1);
	}
	else if (status == PHILOSOPHER_DIE)
		m->die = 1;
	pthread_mutex_unlock(&(m->main_mutex));
	return (0);
}

void	print_philosopher(long long int timestamp, int philo_id, int status,
					t_main *m)
{
	char	str[21 + 1 + 12 + 1 + 17];
	int		len;

	if (print_philosopher_check_die(m, status))
		return ;
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
	pthread_mutex_lock(&(m->out_mutex));
	write(1, str, ft_strlen(str));
	pthread_mutex_unlock(&(m->out_mutex));
}
