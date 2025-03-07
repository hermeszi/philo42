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
	t_philosopher	*philo;
	int				remaining_meals;

	philo = (t_philosopher *)arg;
	philo->last_meal_time = get_current_time();
	remaining_meals = philo->times_must_eat;
	if (philo->id % 2 == 0)
		usleep(WAIT);
	while (remaining_meals != 0 && *(philo->simulation_running))
	{
		think(philo);
		if (pickup_forks(philo))
			break ;
		eat(philo);
		putdown_forks(philo);
		sleep_philo(philo);
		remaining_meals--;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_table	*p;
	int		status;

	p = malloc(sizeof (t_table));
	if (!p)
		return (1);
	p->simulation_running = 1;
	p->diner = NULL;
	p->tid = NULL;
	if (argc < 5 || argc > 6)
		return (printf("Error: Wrong number of arguments\n"), free(p), 2);
	p->count = valid_input(argv);
	if (!p->count)
		return (printf("Error: Invalid arguments\n"), free(p), 2);
	if (allocate_memory(p, argv) != 0)
		return (free(p), 1);
	if (create_threads(p->tid, p->diner, p->count) != 0)
		return (clean_up(p), 1);
	status = monitor_philo(p);
	usleep(WAIT);
	wait_for_threads(p->tid, p->count);
	clean_up(p);
	if (status == 1)
		printf("Simulation ended: a philosopher died\n");
	else if (status == 2)
		printf("Simulation ended: all philosophers ate enough\n");
	return (0);
}
/*
valgrind --track-origins=yes --leak-check=full 
--show-leak-kinds=all --track-fds=yes ./philo
*/