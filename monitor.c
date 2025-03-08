/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 22:08:21 by myuen             #+#    #+#             */
/*   Updated: 2025/02/28 22:08:27 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_philosopher *p)
{
	long long	current_time;

	current_time = get_current_time();
	pthread_mutex_lock(&(p->meal_time_lock));
	if ((current_time - p->last_meal_time) > p->time_to_die)
	{
		pthread_mutex_unlock(&(p->meal_time_lock));
		return (1);
	}
	pthread_mutex_unlock(&(p->meal_time_lock));
	return (0);
}

static int	check_any_philosopher_dead(t_table *p)
{
	int	i;

	i = 0;
	while (i < p->count)
	{
		if (check_death(&p->diner[i]))
		{
			pthread_mutex_lock(&p->print_lock);
			p->simulation_running = 0;
			printf("%lld %d died\n", get_current_time(), \
					p->diner[i].id + 1);
			pthread_mutex_unlock(&p->print_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_all_philosophers_ate(t_table *p)
{
	int	i;
	int	all_ate;

	all_ate = 1;
	i = 0;
	while (i < p->count)
	{
		if (p->diner[i].times_must_eat > 0 && \
			p->diner[i].meals_eaten < p->diner[i].times_must_eat)
			all_ate = 0;
		i++;
	}
	if (p->diner[0].times_must_eat > 0 && all_ate)
		return (1);
	return (0);
}

int	monitor_philo(t_table *p)
{
	while (1)
	{
		if (check_any_philosopher_dead(p))
			return (1);
		if (check_all_philosophers_ate(p))
			return (2);
		usleep(WAIT);
	}
}
