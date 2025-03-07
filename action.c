/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 22:08:06 by myuen             #+#    #+#             */
/*   Updated: 2025/02/28 22:15:31 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philosopher *p)
{
	if (*(p->simulation_running))
	{
		print_state(p, "is thinking");
		usleep(WAIT);
	}
}

int	pickup_forks(t_philosopher *p)
{
	while (*(p->simulation_running))
	{
		pthread_mutex_lock((p->left_fork));
		if (*(p->simulation_running))
			print_state(p, "has taken a fork");
		else
			return (pthread_mutex_unlock(p->left_fork), 1);
		if (pthread_mutex_trylock(p->right_fork) == 0)
		{
			if (*(p->simulation_running))
				print_state(p, "has taken a fork");
			else
			{
				pthread_mutex_unlock(p->right_fork);
				pthread_mutex_unlock(p->left_fork);
				return (1);
			}
			return (0);
		}
		pthread_mutex_unlock(p->left_fork);
		usleep(WAIT);
	}
	return (1);
}

void	eat(t_philosopher *p)
{
	if (*(p->simulation_running))
	{
		p->last_meal_time = get_current_time();
		print_state(p, "is eating");
		usleep(p->time_to_eat);
		p->meals_eaten++;
	}
}

void	putdown_forks(t_philosopher *p)
{
	pthread_mutex_unlock(p->right_fork);
	pthread_mutex_unlock(p->left_fork);
}

void	sleep_philo(t_philosopher *p)
{
	if (*(p->simulation_running))
	{
		print_state(p, "is sleeping");
		usleep(p->time_to_sleep);
	}
}

/*alternative
int	pickup_forks(t_philosopher *p)
{
	if (!*(p->simulation_running))
		return (1);
	if (p->id % 2 == 0)
	{
		pthread_mutex_lock(p->right_fork);
		if (!*(p->simulation_running))
		{
			pthread_mutex_unlock(p->right_fork);
			return (1);
		}
		print_state(p, "has taken a fork");
		pthread_mutex_lock(p->left_fork);
		if (!*(p->simulation_running))
		{
			pthread_mutex_unlock(p->left_fork);
			pthread_mutex_unlock(p->right_fork);
			return (1);
		}
		print_state(p, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(p->left_fork);
		if (!*(p->simulation_running))
		{
			pthread_mutex_unlock(p->left_fork);
			return (1);
		}
		print_state(p, "has taken a fork");
		pthread_mutex_lock(p->right_fork);
		if (!*(p->simulation_running))
		{
			pthread_mutex_unlock(p->right_fork);
			pthread_mutex_unlock(p->left_fork);
			return (1);
		}
		print_state(p, "has taken a fork");
	}
	return (0);
}
*/
