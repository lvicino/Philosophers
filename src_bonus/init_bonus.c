/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:56:15 by lvicino           #+#    #+#             */
/*   Updated: 2024/08/22 13:33:50 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	check_args(char **ar)
{
	int	i;
	int	j;

	i = 0;
	while (ar[++i])
	{
		if (check_nbr_len(ar[i]) > 9 || check_nbr_len(ar[i]) < 1)
			return (0);
		j = -1;
		while (ar[i][++j])
		{
			if ((!j && (ar[i][j] == '-' || (ar[i][j] != '+' && \
			!(ar[i][j] >= '0' && ar[i][j] <= '9')))) || \
			(j && !(ar[i][j] >= '0' && ar[i][j] <= '9')))
				return (0);
		}
	}
	return (1);
}

bool	init_locks(t_rules *rules)
{
	(sem_unlink("/print_sem"), sem_unlink("/status_sem"));
	(sem_unlink("/count_sem"), sem_unlink("/meal_sem"));
	rules->print = sem_open("/print_sem", O_CREAT, 0644, 1);
	if (!rules->print)
		return (0);
	rules->status = sem_open("/status_sem", O_CREAT, 0644, 1);
	if (!rules->status)
		return (sem_close(rules->print), 0);
	rules->count = sem_open("/count_sem", O_CREAT, 0644, 1);
	if (!rules->count)
		return (sem_close(rules->print), sem_close(rules->status), 0);
	rules->meal = sem_open("/meal_sem", O_CREAT, 0644, 1);
	if (!rules->meal)
		return (sem_close(rules->print), sem_close(rules->status), \
		sem_close(rules->meal), 0);
	return (1);
}

bool	init_rules(t_rules *rules, int ac, char **ar)
{
	rules->r = -1;
	rules->pid = -1;
	rules->n_philo = ft_atost(ar[1]);
	rules->tt_die = ft_atost(ar[2]);
	rules->tt_eat = ft_atost(ar[3]);
	rules->tt_sleep = ft_atost(ar[4]);
	if (ac == 6)
		rules->min_meal = ft_atost(ar[5]);
	else
			rules->min_meal = 0;
	rules->must_eat = 0 | (ac == 6);
	rules->run = 0;
	if (!rules->n_philo || rules->n_philo > 200)
		return (0);
	return (init_locks(rules));
}

int	init_philo(t_rules *rules, t_philo *philo)
{
	philo->id = 0;
	philo->n_meal = 0;
	philo->last_meal = 0;
	sem_unlink("/fork_sem");
	philo->fork = sem_open("/fork_sem", O_CREAT, 0644, rules->n_philo / 2);
	if (!philo->fork)
		return (sem_close(rules->print), sem_close(rules->status), \
		sem_close(rules->count), sem_close(rules->meal), 0);
	philo->rules = rules;
	return (1);
}

bool	init_data(t_rules *rules, t_philo *philo, int ac, char **ar)
{
	if (!check_args(ar) || !init_rules(rules, ac, ar) || \
	!init_philo(rules, philo))
		return (0);
	return (1);
}
