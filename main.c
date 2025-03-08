/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 22:08:06 by myuen             #+#    #+#             */
/*   Updated: 2025/03/08 20:10:58 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*do_philo(void *arg)
{
	t_philosopher	*philo;
	int				remaining_meals;
	int				should_continue;

	philo = (t_philosopher *)arg;
	pthread_mutex_lock(&(philo->meal_time_lock));
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&(philo->meal_time_lock));
	remaining_meals = philo->times_must_eat;
	usleep(WAIT * (philo->id % 2));
	should_continue = 1;
	while (remaining_meals != 0 && should_continue)
	{
		think(philo);
		if (pickup_forks(philo))
			break ;
		eat(philo);
		putdown_forks(philo);
		sleep_philo(philo);
		remaining_meals--;
		pthread_mutex_lock(philo->simulation_running_lock);
		should_continue = *(philo->simulation_running);
		pthread_mutex_unlock(philo->simulation_running_lock);
	}
	return (NULL);
}

static int	check_arguments(int argc, t_table **p)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (2);
	}
	*p = malloc(sizeof(t_table));
	if (!(*p))
		return (1);
	(*p)->simulation_running = 1;
	(*p)->diner = NULL;
	(*p)->tid = NULL;
	return (0);
}

static int	setup_simulation(t_table *p, char **argv)
{
	p->count = valid_input(argv);
	if (!p->count)
	{
		printf("Error: Invalid arguments\n");
		return (2);
	}
	p->start_time = get_current_time();
	if (allocate_memory(p, argv) != 0)
		return (1);
	return (0);
}

static int	run_simulation(t_table *p)
{
	int	status;

	if (create_threads(p->tid, p->diner, p->count) != 0)
		return (clean_up(p), 1);
	status = monitor_philo(p);
	usleep(WAIT);
	wait_for_threads(p->tid, p->count);
	return (status);
}

int	main(int argc, char **argv)
{
	t_table	*p;
	int		status;

	if (check_arguments(argc, &p) != 0)
		return (free(p), 2);
	if (setup_simulation(p, argv) != 0)
		return (free(p), 2);
	status = run_simulation(p);
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