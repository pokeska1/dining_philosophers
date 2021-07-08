/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarian <jmarian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 16:09:55 by jmarian           #+#    #+#             */
/*   Updated: 2021/07/08 13:30:17 by jmarian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean(t_all *all)
{
	int	i;

	i = 0;
	while (i != all->num_philo)
	{
		pthread_mutex_destroy(&all->philos[i].eat_m);
		pthread_mutex_destroy(&all->philos[i].mutex);
		pthread_mutex_destroy(&all->forks_m[i]);
		i++;
	}
	pthread_mutex_destroy(&all->write_m);
	pthread_mutex_destroy(&all->somebody_dead_m);
}

int	dead_inside(t_all *all)
{
	int			i;
	pthread_t	meh;

	all->start = ft_that_time();
	i = 0;
	(void)meh;
	while (i < all->num_philo)
	{
		pthread_create(&meh, NULL, live, (void *)&all->philos[i++]);
		pthread_detach(meh);
		usleep((useconds_t)50);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_all	all;
	int		error;

	error = 0;
	if (argc < 5 || argc > 6)
		error = ft_error("Wrong input!");
	if (error == 1)
		return (1);
	if (make_argv(&all, argc, argv) == 0)
		error = ft_error("Wrong input!");
	if (error == 1)
		return (1);
	dead_inside(&all);
	pthread_mutex_lock(&all.somebody_dead_m);
	pthread_mutex_unlock(&all.somebody_dead_m);
	if (all.error != -1)
	{
		pthread_mutex_lock(&all.write_m);
		printf("All allive\n");
	}
	clean(&all);
	usleep((useconds_t)300000);
	return (0);
}
