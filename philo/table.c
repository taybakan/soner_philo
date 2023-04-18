/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkorucu <mkorucu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 15:19:21 by mkorucu           #+#    #+#             */
/*   Updated: 2022/12/10 18:32:41 by mkorucu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_philo_check(t_philo *philo)
{
	if (philo->eaten == philo->goal)
		return (1);
	pthread_mutex_lock(philo->lock);
	if (*philo->check_dead)
	{
		pthread_mutex_unlock(philo->lock);
		return (1);
	}
	pthread_mutex_unlock(philo->lock);
	if (ft_get_time() - philo->last_meal > philo->die_time)
	{
		ft_philo_print(philo, "died", 1);
		return (1);
	}
	return (0);
}

int	ft_philo_wait(t_philo *philo, t_time wait_time)
{
	t_time	time;

	time = ft_get_time();
	while (ft_get_time() - time < wait_time)
	{
		if (ft_philo_check(philo))
			return (1);
		usleep(100);
	}
	return (0);
}

void	ft_philo_print(t_philo *philo, char *status, int kill)
{
	pthread_mutex_lock(philo->lock);
	if (!*philo->check_dead)
	{
		printf("%llu %d %s\n", (ft_get_time() - philo->start_time), \
		philo->id + 1, status);
		if (kill)
			*philo->check_dead = 1;
	}
	pthread_mutex_unlock(philo->lock);
}

void	ft_philo_eat_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	ft_philo_print(philo, "has taken a fork", 0);
	pthread_mutex_lock(philo->right_fork);
	ft_philo_print(philo, "has taken a fork ", 0);
	ft_philo_print(philo, "is eating", 0);
	ft_philo_wait(philo, philo->eat_time);
	philo->eaten++;
	philo->last_meal = ft_get_time();
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (ft_philo_check(philo))
		return ;
	ft_philo_print(philo, "is sleeping", 0);
	ft_philo_wait(philo, philo->sleep_time);
}

void	*ft_table(void *argument)
{
	t_philo	*philo;

	philo = (t_philo *)argument;
	if (philo->total_philo == 1 && !ft_philo_check(philo))
	{
		if (pthread_mutex_lock(philo->left_fork))
			return (NULL);
		ft_philo_print(philo, " has taken a fork", 0);
		while (!ft_philo_check(philo))
		{
		}
		pthread_mutex_unlock(philo->left_fork);
	}
	while (1)
	{
		if (ft_philo_check(philo))
			break ;
		ft_philo_eat_sleep(philo);
		if (ft_philo_check(philo))
			continue ;
		ft_philo_print(philo, "is thinking", 0);
	}
	return (NULL);
}
