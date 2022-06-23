/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   philo_action.c									 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: alcierra <alcierra@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/06/14 00:00:00 by alcierra		  #+#	#+#			 */
/*   Updated: 2022/06/14 00:00:00 by alcierra		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../philo.h"

int	philo_action_take_left_fork(t_philo *p, int flag)
{
	struct timeval	curr_time;

	pthread_mutex_lock(&(p->left->mutex));
	gettimeofday(&curr_time, NULL);
	if (flag)
	{
		pthread_mutex_lock(&(p->mutex));
		if (philo_need_stop(p))
		{
			philo_func_force_stop(p, PHILOSOPHER_TAKE_FORK);
			return (1);
		}
		pthread_mutex_unlock(&(p->mutex));
	}
	print_philosopher(milliseconds_from(&(p->parent->start), &curr_time),
					  p->id, PHILOSOPHER_TAKE_FORK, &(p->parent->out_mutex));
	return (0);
}

int	philo_action_take_right_fork(t_philo *p, int flag)
{
	struct timeval	curr_time;

	pthread_mutex_lock(&(p->right->mutex));
	gettimeofday(&curr_time, NULL);
	if (flag)
	{
		pthread_mutex_lock(&(p->mutex));
		if (philo_need_stop(p))
		{
			philo_func_force_stop(p, PHILOSOPHER_TAKE_FORK);
			return (1);
		}
		pthread_mutex_unlock(&(p->mutex));
	}
	print_philosopher(milliseconds_from(&(p->parent->start), &curr_time),
					  p->id, PHILOSOPHER_TAKE_FORK, &(p->parent->out_mutex));
	return (0);
}

int	philo_action_eat(t_philo *p, int *eaten, int i)
{
	struct timeval	curr_time;

	gettimeofday(&curr_time, NULL);
	print_philosopher(milliseconds_from(&(p->parent->start), &curr_time),
					  p->id, PHILOSOPHER_EAT, &(p->parent->out_mutex));
	gettimeofday(&curr_time, NULL);
	pthread_mutex_lock(&(p->mutex));
	p->last_eaten = curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000;
	p->eaten++;
	*eaten = p->eaten;
	p->status = PHILOSOPHER_SLEEP;
	pthread_mutex_unlock(&(p->mutex));
	ft_usleep(philo_get_time(p, p->parent, &curr_time, PHILOSOPHER_EAT));
	if (i == 1)
	{
		pthread_mutex_unlock(&(p->left->mutex));
		pthread_mutex_unlock(&(p->right->mutex));
	}
	else
	{
		pthread_mutex_unlock(&(p->right->mutex));
		pthread_mutex_unlock(&(p->left->mutex));
	}
	return (0);
}

void	philo_action_sleep(t_philo *p)
{
	struct timeval	curr_time;	

	gettimeofday(&curr_time, NULL);
	print_philosopher(milliseconds_from(&(p->parent->start), &curr_time),
					  p->id, PHILOSOPHER_SLEEP, &(p->parent->out_mutex));
	ft_usleep(philo_get_time(p, p->parent, &curr_time, PHILOSOPHER_SLEEP));
}

void	philo_action_think(t_philo *p)
{
	struct timeval	curr_time;

	gettimeofday(&curr_time, NULL);
	print_philosopher(milliseconds_from(&(p->parent->start), &curr_time),
					  p->id, PHILOSOPHER_THINK, &(p->parent->out_mutex));
}
