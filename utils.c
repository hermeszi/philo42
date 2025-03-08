/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 22:08:21 by myuen             #+#    #+#             */
/*   Updated: 2025/03/08 20:49:40 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	valid_input(char **args)
{
	int	i;
	int	value;

	i = 1;
	value = -1;
	while (args[i])
	{
		if (!ft_isvalid_integer((const char *) args[i], 10))
			return (printf("Invalid: arg not valid interger: %s\n", args[i]), 0);
		value = (int) ft_strtol((const char *) args[i], NULL, 10);
		if (value < 0)
			return (printf("Invalid: arg < 0: %s\n", args[i]), 0);
		i++;
	}
	value = (int) ft_strtol((const char *) args[1], NULL, 10);
	return (value);
}

long long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

void	wait_for_threads(pthread_t *tid, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pthread_join(tid[i], NULL) != 0)
			printf("Error joining thread %d\n", i);
		i++;
	}
}

void	print_state(t_philosopher *p, char *state)
{
	long long	timestamp;
	int			is_running;

	pthread_mutex_lock(p->simulation_running_lock);
	is_running = *(p->simulation_running);
	pthread_mutex_unlock(p->simulation_running_lock);
	timestamp = get_current_time() - p->start_time;
	pthread_mutex_lock(p->print_lock);
	if (is_running || !ft_strncmp(state, "died", sizeof("died")))
		printf("%lld %d %s\n", timestamp, p->id + 1, state);
	pthread_mutex_unlock(p->print_lock);
}

void	clean_up(t_table *p)
{
	int	i;

	i = 0;
	while (i < p->count)
	{
		pthread_mutex_destroy(&(p->fork[i]));
		pthread_mutex_destroy(&p->diner[i].meal_time_lock);
		i++;
	}
	pthread_mutex_destroy(&p->simulation_running_lock);
	pthread_mutex_destroy(&p->print_lock);
	if (p->diner)
		free(p->diner);
	if (p->tid)
		free(p->tid);
	if (p->fork)
		free(p->fork);
	free(p);
}
