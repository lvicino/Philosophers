/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:50:39 by lvicino           #+#    #+#             */
/*   Updated: 2024/07/25 14:38:25 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	wait_philo(t_rules *rules)
{
	size_t	i;

	while (rules->r)
	{
		rules->pid = waitpid(-1, &rules->r, 0);
		rules->r = WEXITSTATUS(rules->r);
	}
	i = rules->n_philo;
	while (i > 0)
	{
		i--;
		if (rules->pid != rules->pid_tab[i])
			kill(rules->pid_tab[i], SIGCHLD);
	}
}

void	get_philo(t_rules *rules, t_philo *philo)
{
	rules->pid_tab = malloc(sizeof(pid_t) * (rules->n_philo));
	if (!rules->pid_tab)
		return (destroy(rules, philo), exit(0));
	while (rules->pid && philo->id < rules->n_philo)
	{
		rules->pid_tab[philo->id] = fork();
		rules->pid = rules->pid_tab[philo->id];
		philo->id++;
	}
}

int	main(int ac, char **ar)
{
	t_rules	rules;
	t_philo	philo;

	if (ac < 5 || ac > 6 || !init_data(&rules, &philo, ac, ar))
		return (write(2, "Error\n", 6), 1);
	get_philo(&rules, &philo);
	if (!rules.pid)
	{
		sem_wait(rules.status);
		pthread_create(&philo.t, NULL, &routine, &philo);
		rules.run = 1;
		rules.start = get_time(0);
		sem_post(rules.status);
		check(&philo, &rules);
		pthread_join(philo.t, NULL);
		return (destroy(&rules, &philo), rules.r);
	}
	wait_philo(&rules);
	destroy(&rules, &philo);
	return (0);
}
