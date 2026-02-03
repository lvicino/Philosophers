/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:24:41 by lvicino           #+#    #+#             */
/*   Updated: 2024/08/22 13:34:27 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	ft_eat(t_philo *philo, t_rules *rules, sem_t	*fork)
{
	sem_wait(fork);
	ft_print(get_time(rules->start), philo->id, FORK, rules);
	ft_print(get_time(rules->start), philo->id, FORK, rules);
	sem_wait(rules->meal);
	philo->last_meal = get_time(0) - rules->start;
	sem_post(rules->meal);
	ft_print(get_time(rules->start), philo->id, EAT, rules);
	sem_wait(rules->count);
	philo->n_meal++;
	sem_post(rules->count);
	ft_usleep(rules->tt_eat, rules);
	sem_post(fork);
	ft_print(get_time(rules->start), philo->id, SLEEP, rules);
	ft_usleep(rules->tt_sleep, rules);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_rules	*rules;

	philo = arg;
	rules = philo->rules;
	sem_wait(rules->status);
	sem_post(rules->status);
	while (ft_run(rules))
	{
		ft_eat(philo, rules, philo->fork);
		ft_print(get_time(rules->start), philo->id, THINK, rules);
		if (rules->n_philo % 2 && rules->tt_eat >= rules->tt_sleep)
			ft_usleep(rules->tt_eat - rules->tt_sleep + 2, rules);
		else
			usleep(1000);
	}
	return (NULL);
}
