/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarian <jmarian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 01:32:35 by jmarian           #+#    #+#             */
/*   Updated: 2021/07/08 17:30:09 by jmarian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	make_mutex(t_all *all)
{
	int	i;

	i = 0;
	pthread_mutex_init(&all->write_m, NULL);
	pthread_mutex_init(&all->somebody_dead_m, NULL);
	pthread_mutex_lock(&all->somebody_dead_m);
	all->forks_m = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * all->num_philo - 1);
	if (!all->forks_m)
		ft_error("Error: Malloc break->all->forks_m->make_argv.c");
	while (i < all->num_philo)
		pthread_mutex_init(&all->forks_m[i++], NULL);
}

void	make_philosophers(t_all *all)
{
	int	i;

	i = 0;
	all->philos = (t_philo *)malloc(sizeof(t_philo) * all->num_philo - 1);
	if (!all->philos)
		ft_error("Error: Malloc break->all->philos->make_argv.c");
	while (i < all->num_philo)
	{
		all->philos[i].position = i;
		all->philos[i].lfork = i;
		all->philos[i].rfork = ((i + 1) % all->num_philo);
		all->philos[i].eat_count = 0;
		all->philos[i].is_eating = 0;
		all->philos[i].all = all;
		pthread_mutex_init(&all->philos[i].eat_m, NULL);
		pthread_mutex_init(&all->philos[i].mutex, NULL);
		pthread_mutex_lock(&all->philos[i++].eat_m);
	}
	make_mutex(all);
}

int	make_argv(t_all *all, int argc, char **argv)
{
	(void) argc;
	all->num_philo = ft_atoi(argv[1]);
	all->time_to_die = ft_atoi(argv[2]);
	all->time_to_eat = ft_atoi(argv[3]);
	all->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		all->number_of_dinner = ft_atoi(argv[5]);
		if (all->number_of_dinner <= 0)
			return (0);
	}
	else
		all->number_of_dinner = 0;
	if (all->num_philo < 1 || (int)all->time_to_die < 60
		|| (int)all->time_to_eat < 60 || (int)all->time_to_sleep < 60)
		return (0);
	make_philosophers(all);
	return (1);
}
