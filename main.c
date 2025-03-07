/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 22:08:06 by myuen             #+#    #+#             */
/*   Updated: 2025/02/28 22:15:31 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*do_philo(void *arg)
{
	t_philosopher	*diner;
	int				cycle;

	cycle = 0;
	diner = (t_philosopher *)arg;
	while (cycle < 3)
	{
		printf("[Philosopher %d] is thinking...\n", diner->id);
		pthread_mutex_lock(diner->left_fork);
		printf("[Philosopher %d] took left fork\n", diner->id);
		pthread_mutex_lock(diner->right_fork);
		printf("[Philosopher %d] took right fork - eating\n", diner->id);
		diner->last_meal_time = get_current_time();
		usleep(diner->time_to_eat);
		pthread_mutex_unlock(diner->right_fork);
		pthread_mutex_unlock(diner->left_fork);
		printf("[Philosopher %d] put down forks - sleeping\n", diner->id);
		usleep(diner->time_to_sleep);
	}
	printf("[Philosopher %d] Finished cycles.\n", diner->id);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philosopher	*diner;
	pthread_t		*tid;
	pthread_mutex_t	*fork;
	int				count;

	diner = NULL;
	tid = NULL;
	fork = NULL;
	if (argc < 5 || argc > 6)
		return (printf("Error: Wrong number of arguments\n"), 2);
	count = valid_input(argv);
	if (!count)
		return (printf("Error: Invalid arguments\n"), 2);
	if (allocate_memory(&diner, &tid, &fork, argv) != 0)
		return (1);
	if (create_threads(tid, diner, count) != 0)
		return (clean_up(diner, tid, fork, count), 1);
	wait_for_threads(tid, count);
	clean_up(diner, tid, fork, count);
	return (printf("Exit\n"), 0);
}
/*
valgrind --track-origins=yes --leak-check=full 
--show-leak-kinds=all --track-fds=yes ./philo
*/