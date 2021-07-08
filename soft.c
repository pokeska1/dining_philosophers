/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soft.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarian <jmarian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 17:11:32 by jmarian           #+#    #+#             */
/*   Updated: 2021/07/08 13:24:01 by jmarian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	long	sum;
	long	i;
	long	minus;

	if (is_digit(str) == 0)
		return (-1);
	sum = 0;
	minus = 0;
	i = 0;
	if (str[0] == '-')
	{
		i = 1;
		minus = -1;
	}
	while (str[i])
		sum = sum * 10 + ((int)str[i++] - 48);
	if (minus == -1)
		sum = sum * -1;
	return ((int)sum);
}

char	*ft_copy(char *str)
{
	int		i;
	char	*str2;

	i = 0;
	str2 = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		str2[i] = str[i];
		i++;
	}
	return (str2);
}

int	ft_that_time(void)
{
	struct timeval	time;
	long int		i;

	gettimeofday(&time, DST_NONE);
	i = (time.tv_sec * (uint64_t)1000) + (time.tv_usec / 1000);
	return ((int)i);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_error(char *str)
{
	printf("%s\n", str);
	return (1);
}
