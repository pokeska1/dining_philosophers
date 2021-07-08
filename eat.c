/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarian <jmarian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 03:31:36 by jmarian           #+#    #+#             */
/*   Updated: 2021/07/08 17:29:13 by jmarian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_more_eat(t_philo *phil)
{
	int	i;

	pthread_mutex_lock(&phil->all->forks_m[phil->rfork]);
	pthread_mutex_lock(&phil->all->write_m);
	printf("%d	№%d has taken a fork\n",
		(int)(ft_that_time() - phil->all->start), phil->position + 1);
	pthread_mutex_unlock(&phil->all->write_m);
	pthread_mutex_lock(&phil->all->forks_m[phil->lfork]);
	pthread_mutex_lock(&phil->mutex);
	phil->last_eat = ft_that_time();
	phil->limit = phil->last_eat + phil->all->time_to_die;
	pthread_mutex_lock(&phil->all->write_m);
	printf("%d	№%d has taken a fork\n",
		(int)(ft_that_time() - phil->all->start), phil->position + 1);
	printf("%d	№%d is eating\n",
		(int)(ft_that_time() - phil->all->start),
		phil->position + 1);
	pthread_mutex_unlock(&phil->all->write_m);
	i = (int)phil->all->time_to_eat;
	ft_usleep(i);
	pthread_mutex_unlock(&phil->mutex);
	pthread_mutex_unlock(&phil->all->forks_m[phil->rfork]);
	pthread_mutex_unlock(&phil->all->forks_m[phil->lfork]);
}

static void	ft_more_two_eat(t_philo *phil)
{
	int	i;

	pthread_mutex_lock(&phil->all->forks_m[phil->lfork]);
	pthread_mutex_lock(&phil->all->write_m);
	printf("%d	№%d has taken a fork\n",
		(int)(ft_that_time() - phil->all->start), phil->position + 1);
	pthread_mutex_unlock(&phil->all->write_m);
	pthread_mutex_lock(&phil->all->forks_m[phil->rfork]);
	pthread_mutex_lock(&phil->mutex);
	phil->last_eat = ft_that_time();
	phil->limit = phil->last_eat + phil->all->time_to_die;
	pthread_mutex_lock(&phil->all->write_m);
	printf("%d	№%d has taken a fork\n",
		(int)(ft_that_time() - phil->all->start), phil->position + 1);
	printf("%d	№%d is eating\n",
		(int)(ft_that_time() - phil->all->start),
		phil->position + 1);
	pthread_mutex_unlock(&phil->all->write_m);
	i = (int)phil->all->time_to_eat;
	ft_usleep(i);
	pthread_mutex_unlock(&phil->mutex);
	pthread_mutex_unlock(&phil->all->forks_m[phil->lfork]);
	pthread_mutex_unlock(&phil->all->forks_m[phil->rfork]);
}

void	ft_eat(t_philo *phil)
{
	int	i;

	if (((phil->position + 1) % 2) == 0)
		ft_more_two_eat(phil);
	else if (((phil->position + 1) % 2) != 0)
		ft_more_eat(phil);
	phil->is_eating++;
	pthread_mutex_lock(&phil->all->write_m);
	i = ft_that_time();
	printf("%d	№%d is sleeping\n",
		(i - (int)phil->all->start), phil->position + 1);
	pthread_mutex_unlock(&phil->all->write_m);
	i = (int)phil->all->time_to_sleep;
	ft_usleep(i);
}

int	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57 || str[i] == '-')
			return (0);
		i++;
	}
	return (1);
}
