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

static int	handle_single_fork(t_philosopher *p)
{
	pthread_mutex_lock(p->left_fork);
	if (!*(p->simulation_running))
		return (pthread_mutex_unlock(p->left_fork), 1);
	print_state(p, "has taken a fork");
	while (*(p->simulation_running))
		usleep(WAIT);
	pthread_mutex_unlock(p->left_fork);
	return (1);
}

static int	take_first_fork(t_philosopher *p, pthread_mutex_t *first_fork)
{
	pthread_mutex_lock(first_fork);
	if (!*(p->simulation_running))
	{
		pthread_mutex_unlock(first_fork);
		return (1);
	}
	print_state(p, "has taken a fork");
	return (0);
}

static int	take_second_fork(t_philosopher *p, pthread_mutex_t *first_fork, \
		pthread_mutex_t *second_fork)
{
	pthread_mutex_lock(second_fork);
	if (!*(p->simulation_running))
	{
		pthread_mutex_unlock(second_fork);
		pthread_mutex_unlock(first_fork);
		return (1);
	}
	print_state(p, "has taken a fork");
	return (0);
}

int	pickup_forks(t_philosopher *p)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (!*(p->simulation_running))
		return (1);
	if (p->left_fork == p->right_fork)
		return (handle_single_fork(p));
	if (p->id % 2 == 0)
	{
		first_fork = p->right_fork;
		second_fork = p->left_fork;
	}
	else
	{
		first_fork = p->left_fork;
		second_fork = p->right_fork;
	}
	if (take_first_fork(p, first_fork))
		return (1);
	if (take_second_fork(p, first_fork, second_fork))
		return (1);
	return (0);
}

/*alternative*/
/*
int	pickup_forks(t_philosopher *p)
{
	int	should_eat;

	while (*(p->simulation_running))
	{
		pthread_mutex_lock(p->round_lock);
		should_eat = (p->id % 2 == *(p->current_round) % 2);
		pthread_mutex_unlock(p->round_lock);
		if (should_eat)
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
		}
		usleep(WAIT);
	}
	return (1);
}
*/