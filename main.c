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
		printf("[Philosopher %d] Cycle: %d\n", diner->id, cycle);
		printf("  Last meal time: %lld\n", diner->last_meal_time);
		printf("  Time to die: %d\n", diner->time_to_die);
		printf("  Time to eat: %d\n", diner->time_to_eat);
		printf("  Time to sleep: %d\n", diner->time_to_sleep);
		printf("  Must eat: %d\n", diner->times_must_eat);
		usleep(500000);
		cycle++;
	}
	printf("[Philosopher %d] Finished cycles.\n", diner->id);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philosopher	*diner;
	pthread_t		*tid;
	pthread_mutex_t	*forks;
	int				count;

	if (argc < 5 || argc > 6)
		return (printf("Error: Wrong number of arguments\n"), 2);
	count = valid_input(argv);
	if (!count)
		return (printf("Error: Invalid arguments\n"), 2);
	if (allocate_memory(&diner, &tid, &forks, count) != 0)
		return (1);
	init_philo(diner, count, argv, forks);
	if (create_threads(tid, diner, count) != 0)
	{
		clean_up(diner, tid, forks, count);
		return (1);
	}
	wait_for_threads(tid, count);
	clean_up(diner, tid, forks, count);
	return (printf("Exit\n"), 0);
}
/*
valgrind --track-origins=yes --leak-check=full 
--show-leak-kinds=all --track-fds=yes ./philo
*/