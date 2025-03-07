/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosopher.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 22:08:06 by myuen             #+#    #+#             */
/*   Updated: 2025/02/28 22:15:31 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	allocate_philosophers(t_table *p)
{
	p->diner = malloc(p->count * sizeof(t_philosopher));
	if (!p->diner)
		return (printf("Memory Allocation Error\n"), 1);
	memset(p->diner, 0, p->count * sizeof(t_philosopher));
	return (0);
}

static void	init_philosopher(t_philosopher *philo, char **args, int i)
{
	philo->id = i;
	philo->last_meal_time = get_current_time();
	philo->time_to_die = (int)ft_strtol(args[2], NULL, 10);
	philo->time_to_eat = (int)ft_strtol(args[3], NULL, 10) * 1000;
	philo->time_to_sleep = (int)ft_strtol(args[4], NULL, 10) * 1000;
	if (args[5])
		philo->times_must_eat = (int)ft_strtol(args[5], NULL, 10);
	else
		philo->times_must_eat = -1;
	philo->meals_eaten = 0;
}

static void	assign_forks_and_locks(t_philosopher *philo, t_table *p, int i)
{
	philo->left_fork = &(p->fork[i]);
	philo->right_fork = &(p->fork[(i + 1) % p->count]);
	philo->print_lock = &(p->print_lock);
	philo->simulation_running = &(p->simulation_running);
}

int	init_philo(t_table *p, char **args)
{
	int	i;

	if (allocate_philosophers(p))
		return (1);
	i = 0;
	while (i < p->count)
	{
		init_philosopher(&p->diner[i], args, i);
		assign_forks_and_locks(&p->diner[i], p, i);
		i++;
	}
	return (0);
}
