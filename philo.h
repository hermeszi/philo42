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
#ifndef PHILO_H
# define PHILO_H

/************************************/
/*			System includes			*/
/************************************/
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_philosopher
{
	int				id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	long long		last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philosopher;

long		ft_strtol(const char *str, char **endptr, int base);
int			ft_isvalid_integer(const char *str, int base);
int			valid_input(char **args);
int			ft_set_sign(const char **str);
int			ft_char_to_digit(char c, int base);
const char	*ft_check_base(const char *str, int *base);
int			ft_isspace(int c);
void		init_philo(t_philosopher *diner, int count, \
			char **args, pthread_mutex_t *forks);
int			init_forks(pthread_mutex_t **forks, int count);
int			allocate_memory(t_philosopher **diner, pthread_t **tid, \
			pthread_mutex_t **forks, int count);
int			create_threads(pthread_t *tid, t_philosopher *diner, int count);
void		*do_philo(void *arg);
void		wait_for_threads(pthread_t *tid, int count);
void		clean_up(t_philosopher *diner, pthread_t *tid, \
			pthread_mutex_t *forks, int count);

#endif