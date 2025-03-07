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
		printf("thread %d - closed with %d\n", i, pthread_join(tid[i], NULL));
		i++;
	}
}

void	clean_up(t_philosopher *diner, pthread_t *tid, \
		pthread_mutex_t *fork, int count)
{
	int	i;

	i = 0;
	while (i < count)
		pthread_mutex_destroy(&fork[i++]);
	free(diner);
	free(tid);
	free(fork);
}
