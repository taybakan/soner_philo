/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkorucu <mkorucu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 17:53:03 by mkorucu           #+#    #+#             */
/*   Updated: 2022/12/10 17:55:43 by mkorucu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_arg_check(int ac, char **av)
{
	int	i;
	int	j;

	if (ac != 5 && ac != 6)
		return (1);
	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j] != '\0')
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
			if (ft_atoi(av[i]) > 2147483647)
				return (1);
			if (ft_atoi(av[i]) == 0)
				return (1);
			j++;
		}
		i++;
	}
	if (ft_atoi(av[1]) < 1)
		return (1);
	return (0);
}

long	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long long	number;

	sign = 1;
	number = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		number = (number * 10) + (str[i] - 48) * sign;
		i++;
	}
	return (number);
}

void	ft_free(t_philo *philo, pthread_mutex_t *fork, pthread_mutex_t *lock)
{
	int	i;

	i = 0;
	while (i < philo->total_philo)
	{
		pthread_mutex_destroy(philo[i].left_fork);
		pthread_mutex_destroy(philo[i].right_fork);
		i++;
	}
	pthread_mutex_destroy(philo->lock);
	pthread_mutex_destroy(fork);
	free(lock);
	free(philo->check_dead);
	free(philo);
}

t_time	ft_get_time(void)
{
	struct timeval		tv;
	unsigned long long	time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}
