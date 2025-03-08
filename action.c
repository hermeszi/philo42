/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 22:08:06 by myuen             #+#    #+#             */
/*   Updated: 2025/03/08 19:58:12 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philosopher *p)
{
	int	is_running;

	pthread_mutex_lock(p->simulation_running_lock);
	is_running = *(p->simulation_running);
	pthread_mutex_unlock(p->simulation_running_lock);
	if (is_running)
	{
		print_state(p, "is thinking");
		if (p->id % 2 != 0)
			usleep(WAIT);
	}
}

// int	pickup_forks(t_philosopher *p)
// {
// 	if (!*(p->simulation_running))
// 		return (1);
// 	if (p->left_fork == p->right_fork)
// 	{
// 		pthread_mutex_lock(p->left_fork);
// 		if (!*(p->simulation_running))
// 			return (pthread_mutex_unlock(p->left_fork), 1);
// 		print_state(p, "has taken a fork");
// 		while (*(p->simulation_running))
// 			usleep(WAIT);
// 		pthread_mutex_unlock(p->left_fork);
// 		return (1);
// 	}
// 	if (p->id % 2 == 0)
// 	{
// 		pthread_mutex_lock(p->right_fork);
// 		if (!*(p->simulation_running))
// 		{
// 			pthread_mutex_unlock(p->right_fork);
// 			return (1);
// 		}
// 		print_state(p, "has taken a fork");
// 		pthread_mutex_lock(p->left_fork);
// 		if (!*(p->simulation_running))
// 		{
// 			pthread_mutex_unlock(p->left_fork);
// 			pthread_mutex_unlock(p->right_fork);
// 			return (1);
// 		}
// 		print_state(p, "has taken a fork");
// 	}
// 	else
// 	{
// 		pthread_mutex_lock(p->left_fork);
// 		if (!*(p->simulation_running))
// 		{
// 			pthread_mutex_unlock(p->left_fork);
// 			return (1);
// 		}
// 		print_state(p, "has taken a fork");
// 		pthread_mutex_lock(p->right_fork);
// 		if (!*(p->simulation_running))
// 		{
// 			pthread_mutex_unlock(p->right_fork);
// 			pthread_mutex_unlock(p->left_fork);
// 			return (1);
// 		}
// 		print_state(p, "has taken a fork");
// 	}
// 	return (0);
// }

void	eat(t_philosopher *p)
{
	int	is_running;

	pthread_mutex_lock(p->simulation_running_lock);
	is_running = *(p->simulation_running);
	pthread_mutex_unlock(p->simulation_running_lock);
	if (is_running)
	{
		pthread_mutex_lock(&(p->meal_time_lock));
		p->last_meal_time = get_current_time();
		pthread_mutex_unlock(&(p->meal_time_lock));
		print_state(p, "is eating");
		usleep(p->time_to_eat);
		pthread_mutex_lock(&(p->meal_time_lock));
		p->meals_eaten++;
		pthread_mutex_unlock(&(p->meal_time_lock));
	}
}

void	putdown_forks(t_philosopher *p)
{
	pthread_mutex_unlock(p->right_fork);
	pthread_mutex_unlock(p->left_fork);
}

void	sleep_philo(t_philosopher *p)
{
	int	is_running;

	pthread_mutex_lock(p->simulation_running_lock);
	is_running = *(p->simulation_running);
	pthread_mutex_unlock(p->simulation_running_lock);
	if (is_running)
	{
		print_state(p, "is sleeping");
		usleep(p->time_to_sleep);
	}
}
