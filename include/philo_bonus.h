/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:50:26 by lvicino           #+#    #+#             */
/*   Updated: 2024/08/22 13:35:37 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <signal.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>

# define FORK "\x1b[1;38;5;102mhas taken a fork\x1b[0m"
# define EAT "\x1b[1;38;5;208mis eating\x1b[0m"
# define SLEEP "\x1b[1;38;5;63mis sleeping\x1b[0m"
# define THINK "\x1b[38;5;98mis thinking\x1b[0m"
# define DEATH "\x1b[1;5;31m%zu %zu died\x1b[0m\n"

typedef struct s_rules
{
	size_t	n_philo;
	size_t	tt_die;
	size_t	tt_eat;
	size_t	tt_sleep;
	bool	must_eat;
	size_t	min_meal;
	bool	run;
	size_t	start;
	sem_t	*print;
	sem_t	*status;
	sem_t	*count;
	sem_t	*meal;
	pid_t	*pid_tab;
	pid_t	pid;
	int		r;
}			t_rules;

typedef struct s_philo
{
	size_t		id;
	size_t		n_meal;
	size_t		last_meal;
	sem_t		*fork;
	t_rules		*rules;
	pthread_t	t;
}				t_philo;

/*utils*/
size_t	ft_atost(const char *nptr);
int		check_nbr_len(char *s);
void	ft_print(size_t time, size_t id, char *state, t_rules *rules);
size_t	get_time(size_t start);
void	destroy(t_rules *rules, t_philo *philo);

/*init*/
bool	init_data(t_rules *rules, t_philo *philo, int ac, char **ar);

/*routine*/
void	*routine(void *arg);

/*check*/
bool	ft_run(t_rules *rules);
void	check(t_philo *philo, t_rules *rules);

#endif
