/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 22:08:06 by myuen             #+#    #+#             */
/*   Updated: 2025/02/28 22:15:31 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_philosopher *diner, int count, \
		char **args, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < count)
	{
		diner[i].id = i;
		diner[i].last_meal_time = 0;
		diner[i].time_to_die = (int)ft_strtol(args[2], NULL, 10);
		diner[i].time_to_eat = (int)ft_strtol(args[3], NULL, 10);
		diner[i].time_to_sleep = (int)ft_strtol(args[4], NULL, 10);
		if (args[5])
			diner[i].times_must_eat = (int)ft_strtol(args[5], NULL, 10);
		else
			diner[i].times_must_eat = -1;
		diner[i].left_fork = &forks[i];
		diner[i].right_fork = &forks[(i + 1) % count];
		i++;
	}
}

int	init_forks(pthread_mutex_t **forks, int count)
{
	int	i;

	*forks = malloc(count * sizeof(pthread_mutex_t));
	if (!*forks)
		return (printf("Fork Mutex Allocation Error\n"), 1);
	i = 0;
	while (i < count)
	{
		if (pthread_mutex_init(&(*forks)[i], NULL) != 0)
		{
			printf("Mutex Initialization Error\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	allocate_memory(t_philosopher **diner, pthread_t **tid, \
		pthread_mutex_t **forks, int count)
{
	*diner = malloc(count * sizeof(t_philosopher));
	if (!*diner)
		return (printf("Memory Allocation Error\n"), 1);
	*tid = malloc(count * sizeof(pthread_t));
	if (!*tid)
	{
		free(*diner);
		return (printf("Memory Allocation Error\n"), 1);
	}
	if (init_forks(forks, count) != 0)
	{
		free(*diner);
		free(*tid);
		return (1);
	}
	return (0);
}

int	create_threads(pthread_t *tid, t_philosopher *diner, int count)
{
	int	i;
	int	err;

	i = 0;
	while (i < count)
	{
		err = pthread_create(&tid[i], NULL, do_philo, (void *)&diner[i]);
		if (err != 0)
			return (printf("Thread Creation Error\n"), 1);
		i++;
	}
	return (0);
}
