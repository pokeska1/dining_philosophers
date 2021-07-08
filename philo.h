#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>

struct		s_all;

typedef struct s_philo{
	int				position;
	int				is_eating;
	uint64_t		limit;
	uint64_t		last_eat;
	int				lfork;
	int				rfork;
	int				eat_count;
	struct s_all	*all;
	pthread_mutex_t	mutex;
	pthread_mutex_t	eat_m;
}					t_philo;

typedef struct s_all
{
	int				num_philo;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				number_of_dinner;
	int				error;
	uint64_t		start;
	t_philo			*philos;
	pthread_mutex_t	*forks_m;
	pthread_mutex_t	write_m;
	pthread_mutex_t	somebody_dead_m;
}					t_all;

int		dead_inside(t_all *all);
void	*live(void *str);
void	ft_eat(t_philo *phil);
int		ft_atoi(char *str);
int		make_argv(t_all *all, int argc, char **argv);
int		ft_error(char *str);
int		ft_strlen(char *str);
char	*ft_copy(char *str);
int		ft_that_time(void);
void	usleep_v2(int i);
int		is_digit(char *str);
void	ft_usleep(unsigned long time);

#endif