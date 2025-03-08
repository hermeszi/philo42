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
# include <sys/time.h>
# include <string.h>

# define WAIT 1000

typedef struct s_philosopher
{
	int				id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	long long		last_meal_time;
	int				meals_eaten;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	meal_time_lock;
	int				*simulation_running;
}	t_philosopher;

typedef struct s_table
{
	t_philosopher	*diner;
	pthread_t		*tid;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print_lock;
	int				count;
	int				simulation_running;
}	t_table;

long		ft_strtol(const char *str, char **endptr, int base);
int			ft_isvalid_integer(const char *str, int base);
int			valid_input(char **args);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_set_sign(const char **str);
int			ft_char_to_digit(char c, int base);
const char	*ft_check_base(const char *str, int *base);
int			ft_isspace(int c);
int			init_philo(t_table *p, char **args);
int			init_fork(pthread_mutex_t **fork, int count);
int			allocate_memory(t_table *p, char **argv);
int			create_threads(pthread_t *tid, t_philosopher *diner, int count);
void		*do_philo(void *arg);
void		wait_for_threads(pthread_t *tid, int count);
void		clean_up(t_table *p);
long long	get_current_time(void);
void		print_state(t_philosopher *p, char *state);
void		think(t_philosopher *p);
int			pickup_forks(t_philosopher *p);
void		eat(t_philosopher *p);
void		putdown_forks(t_philosopher *p);
void		sleep_philo(t_philosopher *p);
int			monitor_philo(t_table *p);

#endif