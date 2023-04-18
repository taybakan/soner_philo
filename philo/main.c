/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkorucu <mkorucu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 14:19:03 by mkorucu           #+#    #+#             */
/*   Updated: 2022/12/10 18:34:51 by mkorucu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_philos(t_philo *philo, char **av, int ac)
{
	int	*check_dead;
	int	i;

	i = 0;
	check_dead = malloc(sizeof(int));
	*check_dead = 0;
	while (i < ft_atoi(av[1]))
	{
		philo[i].id = i;
		philo[i].die_time = ft_atoi(av[2]);
		philo[i].eat_time = ft_atoi(av[3]);
		philo[i].sleep_time = ft_atoi(av[4]);
		if (ac == 6)
			philo[i].goal = ft_atoi(av[5]);
		else
			philo[i].goal = -1;
		philo[i].last_meal = ft_get_time();
		philo[i].start_time = ft_get_time();
		philo[i].eaten = 0;
		philo[i].total_philo = ft_atoi(av[1]);
		philo[i].check_dead = check_dead;
		i++;
	}
	i = 0;
}

void	ft_init_mutexes(t_philo *philo, pthread_mutex_t *fork, \
		pthread_mutex_t *lock)
{
	int	i;

	i = 0;
	while (i < philo->total_philo)
	{
		philo[i].left_fork = &fork[i];
		philo[i].right_fork = &fork[(i + 1) % philo->total_philo];
		pthread_mutex_init(philo[i].left_fork, NULL);
		philo[i].lock = lock;
		i++;
	}
	pthread_mutex_init(philo->lock, NULL);
}

void	ft_start_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->total_philo)
	{
		pthread_create(&philo[i].thread, NULL, &ft_table, &philo[i]);
		i++;
		usleep(100);
	}
	i = 0;
	while (i < philo->total_philo)
		pthread_join(philo[i++].thread, NULL);
	while ((*philo).check_dead == 0)
	{
		ft_philo_check(philo);
	}
}

int	main(int ac, char **av)
{
	t_philo			*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*lock;

	if (ft_arg_check(ac, av))
	{
		printf("Error Occured!\n");
		return (1);
	}
	philo = malloc(sizeof(*philo) * ft_atoi(av[1]));
	fork = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	lock = malloc(sizeof(pthread_mutex_t));
	if (!philo || !fork || !lock)
		return (2);
	ft_init_philos(philo, av, ac);
	ft_init_mutexes(philo, fork, lock);
	ft_start_threads(philo);
	ft_free(philo, fork, lock);
	return (0);
}
