/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:50:39 by lvicino           #+#    #+#             */
/*   Updated: 2024/07/08 18:25:11 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_run(t_rules *rules)
{
	bool	r;

	pthread_mutex_lock(&rules->status);
	r = rules->run;
	pthread_mutex_unlock(&rules->status);
	return (r);
}

void	ft_usleep(size_t time, t_rules *rules)
{
	size_t	start;

	start = get_time(0);
	while (get_time(0) - start < time)
	{
		if (!ft_run(rules))
			break ;
		usleep(1000);
	}
}

void	ft_eat(t_philo *philo, t_rules *rules, \
pthread_mutex_t	*fork1, pthread_mutex_t	*fork2)
{
	pthread_mutex_lock(fork1);
	ft_print(get_time(rules->start), philo->id, FORK, rules);
	pthread_mutex_lock(fork2);
	ft_print(get_time(rules->start), philo->id, FORK, rules);
	pthread_mutex_lock(&rules->meal);
	philo->last_meal = get_time(0) - rules->start;
	pthread_mutex_unlock(&rules->meal);
	ft_print(get_time(rules->start), philo->id, EAT, rules);
	pthread_mutex_lock(&rules->count);
	philo->n_meal++;
	pthread_mutex_unlock(&rules->count);
	ft_usleep(rules->tt_eat, rules);
	pthread_mutex_unlock(fork2);
	pthread_mutex_unlock(fork1);
	ft_print(get_time(rules->start), philo->id, SLEEP, rules);
	ft_usleep(rules->tt_sleep, rules);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_rules	*rules;

	philo = arg;
	rules = philo->rules;
	pthread_mutex_lock(&rules->status);
	pthread_mutex_unlock(&rules->status);
	if (philo->id % 2)
		ft_usleep(rules->tt_eat / 2, rules);
	while (ft_run(rules))
	{
		if (philo->id % 2)
			ft_eat(philo, rules, &philo->fork, philo->righ_fork);
		else
			ft_eat(philo, rules, philo->righ_fork, &philo->fork);
		ft_print(get_time(rules->start), philo->id, THINK, rules);
		if (rules->n_philo % 2 && rules->tt_eat >= rules->tt_sleep)
			ft_usleep(rules->tt_eat - rules->tt_sleep + 2, rules);
		else
			usleep(1000);
	}
	return (NULL);
}

int	main(int ac, char **ar)
{
	t_rules	rules;
	t_philo	*philo;
	int		i;

	if (ac < 5 || ac > 6 || !init_data(&rules, &philo, ac, ar))
		return (write(2, "Error\n", 6), 1);
	i = -1;
	pthread_mutex_lock(&philo->rules->status);
	while (++i < (int)rules.n_philo && rules.n_philo > 1)
		pthread_create(&philo[i].t, NULL, &routine, &philo[i]);
	rules.run = 1;
	rules.start = get_time(0);
	pthread_mutex_unlock(&philo->rules->status);
	if (rules.n_philo == 1 && (!rules.must_eat || rules.min_meal))
		(pthread_mutex_lock(&philo[0].fork), ft_print(get_time(rules.start), \
		0, FORK, &rules), pthread_mutex_unlock(&philo[0].fork));
	check(philo, &rules);
	while (--i >= 0)
		pthread_join(philo[i].t, NULL);
	destroy(&rules, &philo);
	return (0);
}
