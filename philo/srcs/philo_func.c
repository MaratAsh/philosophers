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

int 	get_long_long_(long long int num)
{
	int digits;

	digits = 0;
	if (num == 0)
		return (1);
	while (num)
	{
		num = num / 10;
		digits++;
	}
	return (digits);
}

long long int	ft_power(int num, int power)
{
	long long int	result;
	int 			i;

	result = 1;
	i = 0;
	while (i < power)
	{
		result *= num;
		i++;
	}
	return (result);
}

int 	set_long_long_in_string(char *str, long long int num)
{
	if (num < 0)
	{
		return (0);
	}
	int i;
	int	len = get_long_long_(num);

	if (num == 0)
	{
		str[0] = '0';
		str[1] = 0;
		return (1);
	}
	i = 0;
	while (i < len)
	{
		str[i] = '0' + (num / ft_power(10, (len - i - 1))) % 10;
		i++;
	}
	str[i] = 0;
	return (len);
}

void	print_philosopher(long long int timestamp, int philo_id, int status,
						pthread_mutex_t *mutex)
{
	char	str[21 + 1 + 12 + 1 + 17];
	int 	len;

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
	pthread_mutex_lock(mutex);
	write(1, str, ft_strlen(str));
	pthread_mutex_unlock(mutex);
}

long long int milliseconds_from(struct timeval *since, struct timeval *current)
{
	if (since->tv_sec == current->tv_sec)
		return ((current->tv_usec - since->tv_usec) / 1000);
	return ((current->tv_sec - since->tv_sec) * 1000
			+ (current->tv_usec - since->tv_usec) / 1000);
}

/*
void	ft_usleep(long long millisecond)
{
	struct timeval current_time;
	struct timeval start_time;

	gettimeofday(&current_time, NULL);
	gettimeofday(&start_time, NULL);
	while (start_time.tv_usec + millisecond * 1000 > current_time.tv_usec)
	{
		usleep(1000);
		gettimeofday(&current_time, NULL);
	}
}
*/

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

void	*philo_func(void *params)
{
	t_philo			*p;
	struct timeval	current_time;

	p = (t_philo *) params;
	if (p->id % 2 == 0)
		ft_usleep((long long int) p->parent->time_to_eat);
	// pthread_mutex_lock(&(p->parent->out_mutex));
	// pthread_mutex_unlock(&(p->parent->out_mutex));
	while (1)
	{
		gettimeofday(&current_time, NULL);
		pthread_mutex_lock(&(p->left->mutex));
		print_philosopher(milliseconds_from(&(p->parent->start), &current_time),
			p->id, PHILOSOPHER_TAKE_FORK, &(p->parent->out_mutex));
		pthread_mutex_lock(&(p->right->mutex));
		gettimeofday(&current_time, NULL);
		print_philosopher(milliseconds_from(&(p->parent->start), &current_time),
			p->id, PHILOSOPHER_TAKE_FORK, &(p->parent->out_mutex));
		print_philosopher(milliseconds_from(&(p->parent->start), &current_time),
			p->id, PHILOSOPHER_EAT, &(p->parent->out_mutex));
		gettimeofday(&current_time, NULL);
		ft_usleep((long long int) p->parent->time_to_eat);
		pthread_mutex_unlock(&(p->left->mutex));
		pthread_mutex_unlock(&(p->right->mutex));
		gettimeofday(&current_time, NULL);
		print_philosopher(milliseconds_from(&(p->parent->start), &current_time),
			p->id, PHILOSOPHER_SLEEP, &(p->parent->out_mutex));
		ft_usleep((long long int) p->parent->time_to_sleep);
		gettimeofday(&current_time, NULL);
		print_philosopher(milliseconds_from(&(p->parent->start), &current_time),
			p->id, PHILOSOPHER_THINK, &(p->parent->out_mutex));
	}
	return (NULL);
}
