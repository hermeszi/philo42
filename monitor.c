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

int	check_death(t_philosopher *p)
{
	long long	current_time;

	current_time = get_current_time();
	if ((current_time - p->last_meal_time) > p->time_to_die)
	{
		return (1);
	}
	return (0);
}

int	monitor_philo(t_table *p)
{
	int	i;
	int	all_ate;

	while (1)
	{
		i = 0;
		all_ate = 1;
		while (i < p->count)
		{
			if (check_death(&p->diner[i]))
			{
				pthread_mutex_lock(&p->print_lock);
				p->simulation_running = 0;
				printf("%lld %d died\n", get_current_time(), p->diner[i].id + 1);
				pthread_mutex_unlock(&p->print_lock);
				return (1);
			}
			if (p->diner[i].times_must_eat > 0 && \
				p->diner[i].meals_eaten < p->diner[i].times_must_eat)
				all_ate = 0;
			i++;
		}
		if (p->diner[0].times_must_eat > 0 && all_ate)
			return (2);
		usleep(WAIT);
	}
}
