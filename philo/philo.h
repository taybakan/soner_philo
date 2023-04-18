/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkorucu <mkorucu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 16:50:45 by mkorucu           #+#    #+#             */
/*   Updated: 2022/12/10 17:56:49 by mkorucu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef unsigned long long	t_time;

typedef struct s_philo
{
	int				id;
	int				goal;
	int				total_philo;
	int				eaten;
	int				*check_dead;
	t_time			die_time;
	t_time			eat_time;
	t_time			sleep_time;
	t_time			start_time;
	t_time			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*lock;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

void	ft_init_philos(t_philo *philo, char **av, int ac);
void	ft_init_mutexes(t_philo *philo, pthread_mutex_t *fork, \
		pthread_mutex_t *lock);
void	ft_start_threads(t_philo *philo);
void	*ft_table(void *argument);
void	ft_philo_print(t_philo *philo, char *status, int kill);
void	ft_philo_eat_sleep(t_philo *philo);
int		ft_philo_wait(t_philo *philo, unsigned long long wait_time);
int		ft_philo_check(t_philo *philo);
int		ft_arg_check(int ac, char **av);
long	ft_atoi(const char *str);
void	ft_free(t_philo *philo, pthread_mutex_t *fork, pthread_mutex_t *lock);
t_time	ft_get_time(void);
int		ft_isdigit(int c);
#endif
