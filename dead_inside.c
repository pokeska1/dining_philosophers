/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_inside.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarian <jmarian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 02:11:42 by jmarian           #+#    #+#             */
/*   Updated: 2021/07/08 13:22:18 by jmarian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(unsigned long time)
{
	unsigned long	start;
	unsigned long	limit;

	start = ft_that_time();
	limit = start + time;
	while (1)
	{
		if (ft_that_time() >= (int)limit)
			break ;
		usleep(500);
	}
}

void	ft_think(t_philo *phil)
{
	int	j;

	pthread_mutex_lock(&phil->all->write_m);
	j = ft_that_time();
	printf("%d	№%d is thinking\n",
		(j - (int)phil->all->start), phil->position + 1);
	pthread_mutex_unlock(&phil->all->write_m);
}

void	*ft_is_he_dead(void *meh)
{
	t_philo	*phil;
	int		i;

	phil = (t_philo *)meh;
	while (1)
	{
		pthread_mutex_lock(&phil->mutex);
		i = ((int)phil->limit - ft_that_time());
		if (i < 0)
		{
			phil->all->error = -1;
			pthread_mutex_lock(&phil->all->write_m);
			printf("%d	%d died\n",
				(ft_that_time() - (int)phil->all->start), phil->position + 1);
			pthread_mutex_unlock(&phil->all->somebody_dead_m);
			return ((void *)0);
		}
		pthread_mutex_unlock(&phil->mutex);
		usleep((useconds_t)100);
	}
	return (phil);
}

void	*live(void *str)
{
	t_philo		*phil;
	pthread_t	meh;
	int			i;

	phil = (void *)str;
	i = -1;
	if (phil->all->number_of_dinner != 0)
		i = phil->all->number_of_dinner + 1;
	phil->limit = ft_that_time() + phil->all->time_to_die;
	pthread_create(&meh, NULL, ft_is_he_dead, phil);
	while (i != 0)
	{
		ft_eat(phil);
		ft_think(phil);
		i--;
		if (i == 1)
			phil->all->philos->eat_count++;
		if (phil->all->philos->eat_count + 1 == phil->all->num_philo)
		{
			pthread_mutex_unlock(&phil->all->somebody_dead_m);
		}
	}
	return ((void *)0);
}
