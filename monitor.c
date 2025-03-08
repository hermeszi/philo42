/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 22:08:21 by myuen             #+#    #+#             */
/*   Updated: 2025/03/08 20:04:09 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_philosopher *p)
{
	long long	current_time;
	long long	last_meal;
	int			time_to_die;
	int			result;

	current_time = get_current_time();
	pthread_mutex_lock(&(p->meal_time_lock));
	last_meal = p->last_meal_time;
	time_to_die = p->time_to_die;
	pthread_mutex_unlock(&(p->meal_time_lock));
	result = (current_time - last_meal) > time_to_die;
	return (result);
}

static int	check_any_philosopher_dead(t_table *p)
{
	int			i;
	long long	relative_time;

	i = 0;
	while (i < p->count)
	{
		if (check_death(&p->diner[i]))
		{
			relative_time = get_current_time() - p->start_time;
			pthread_mutex_lock(&p->print_lock);
			pthread_mutex_lock(&p->simulation_running_lock);
			p->simulation_running = 0;
			printf("%lld %d died\n", relative_time, p->diner[i].id + 1);
			pthread_mutex_unlock(&p->simulation_running_lock);
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
	int	meals_eaten;

	if (p->diner[0].times_must_eat <= 0)
		return (0);
	all_ate = 1;
	i = 0;
	while (i < p->count)
	{
		pthread_mutex_lock(&(p->diner[i].meal_time_lock));
		meals_eaten = p->diner[i].meals_eaten;
		pthread_mutex_unlock(&(p->diner[i].meal_time_lock));
		if (p->diner[i].times_must_eat > 0 && \
			meals_eaten < p->diner[i].times_must_eat)
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
/*
static int	check_death(t_philosopher *p)
{
	long long	current_time;
	long long	last_meal;
	int			result;

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

static int check_any_philosopher_dead(t_table *p)
{
	int 		i;
	long long	relative_time;
	i = 0;
	while (i < p->count)
	{
		if (check_death(&p->diner[i]))
		{
			relative_time = get_current_time() - p->start_time;
			pthread_mutex_lock(&p->print_lock);
			pthread_mutex_lock(&p->simulation_running_lock);
			p->simulation_running = 0;
			pthread_mutex_unlock(&p->simulation_running_lock);
			printf("%lld %d died\n", relative_time, p->diner[i].id + 1);
			pthread_mutex_unlock(&p->print_lock);
			return (1);
		}
		i++;
	}
	return (0);
}*/
