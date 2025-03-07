/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 22:08:21 by myuen             #+#    #+#             */
/*   Updated: 2025/02/28 22:08:27 by myuen            ###   ########.fr       */
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
			return (printf("Invalid: args not int: %s\n", args[i]), 0);
		value = (int) ft_strtol((const char *) args[i], NULL, 10);
		if (value < 0)
			return (printf("Invalid: args < 0: %s\n", args[i]), 0);
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

	timestamp = get_current_time();
	pthread_mutex_lock(p->print_lock);
	if (*(p->simulation_running) || !ft_strncmp(state, "died", sizeof("died")))
		printf("%lld %d %s\n", timestamp, p->id + 1, state);
	pthread_mutex_unlock(p->print_lock);
}

void	clean_up(t_table *p)
{
	int	i;

	i = 0;
	while (i < p->count)
		pthread_mutex_destroy(&(p->fork[i++]));
	free(p->diner);
	free(p->tid);
	free(p->fork);
	free(p);
}
