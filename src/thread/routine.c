/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:21:44 by glaguyon          #+#    #+#             */
/*   Updated: 2024/03/17 18:52:37 by glag             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread/philo.h"

//lock une variable commune dans le thread principal puis l,unlock a la fin de la creation des threads
//check erreur puis start routine
//apres check erreur apres les mutex :(
void	*routine(void *philo_)
{
	t_philo	*philo = philo_;

	printp(23000, philo->num, FORK);
	printp(23000, philo->num, EAT);
	printp(23000, philo->num, SLEEP);
	printp(23000, philo->num, THINK);
	printp(23000, philo->num, DIE);
	return (philo);
}
