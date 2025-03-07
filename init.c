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

int	init_fork(pthread_mutex_t **fork, int count)
{
	int	i;

	*fork = malloc(count * sizeof(pthread_mutex_t));
	if (!*fork)
		return (printf("Fork Memory Allocation Error\n"), 1);
	memset(*fork, 0, count * sizeof(pthread_mutex_t));
	i = 0;
	while (i < count)
	{
		if (pthread_mutex_init(&(*fork)[i], NULL) != 0)
		{
			printf("Mutex Initialization Error\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	allocate_memory(t_table *p, char **argv)
{
	p->tid = malloc(p->count * sizeof(pthread_t));
	if (!p->tid)
		return (printf("Thread Memory Allocation Error\n"), 1);
	if (pthread_mutex_init(&p->print_lock, NULL) != 0)
		return (printf("Mutex Initialization Error\n"), 1);
	if (init_fork(&(p->fork), p->count) != 0 || \
		init_philo(p, argv) != 0)
	{
		if (!p->diner)
			free(p->diner);
		if (!p->tid)
			free(p->tid);
		if (!p->fork)
			free(p->fork);
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
