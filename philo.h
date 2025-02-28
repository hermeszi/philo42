/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 22:07:52 by myuen             #+#    #+#             */
/*   Updated: 2025/02/28 22:19:06 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
# define PHILO_H

/************************************/
/*			System includes			*/
/************************************/
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

// philo.h - Basic structure definition
typedef struct s_philosopher
{
	int			id;
	int 		time_to_die;
	int 		time_to_eat;
	int 		time_to_sleep;
	int 		times_must_eat;
	long long	last_meal_time;
	// Add more fields as needed
}	t_philosopher;

# endif
