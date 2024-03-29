/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:15:55 by glaguyon          #+#    #+#             */
/*   Updated: 2024/03/21 17:25:33 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_mutex(t_fork *forks, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&forks[i].mutex);
		i++;
	}
}

static void	give_forks(t_pdata *pdata, t_philo *philo, uint16_t len)
{
	int	i;

	i = 0;
	while (i + 1 < len)
	{
		philo[i].fork = &pdata->forks[i];
		philo[i].nfork = &pdata->forks[i + 1];
		philo[i].meal = &pdata->meals[i];
		i++;
	}
	philo[i].fork = &pdata->forks[i];
	philo[i].nfork = &pdata->forks[0];
	philo[i].meal = &pdata->meals[i];
}

static void	start_threads(t_pdata *pdata, t_philo *philo, uint16_t len)
{
	int	i;
	int	j;
	int	err;

	pdata->eating = pdata->data.nphilo;
	give_forks(pdata, philo, len);
	i = 0;
	pthread_mutex_lock(&pdata->run);
	while (i < len)
	{
		err = pthread_create(pdata->threads + i, NULL, &routine, philo + i);
		if (err)
		{
			ft_perror("Error : cannot create threads\n");
			pdata->data.end = ERR_THREAD;
			break ;
		}
		i++;
	}
	gettimeofday(&pdata->start, NULL);
	pthread_mutex_unlock(&pdata->run);
	j = -1;
	while (++j < i)
		pthread_join(pdata->threads[j], NULL);
	free_mutex(philo->pdata->forks, i);
}

static int	init_struct(t_pdata *pdata, t_philo *philo, uint16_t len)
{
	int	i;

	memset(pdata->meals, 0, pdata->data.nphilo * sizeof(*pdata->meals));
	memset(pdata->threads, 0, pdata->data.nphilo * sizeof(*pdata->threads));
	if (pthread_mutex_init(&pdata->run, NULL))
		return (1);
	i = -1;
	while (++i < len)
	{
		philo[i].pdata = pdata;
		pdata->forks[i].clean = 1;
		if (pthread_mutex_init(&(pdata->forks[i].mutex), NULL))
		{
			pdata->data.end = 2;
			break ;
		}
		philo[i].num = i;
	}
	if (i < len)
	{
		ft_perror("Error: cannot create mutex\n");
		pthread_mutex_destroy(&pdata->run);
		free_mutex(pdata->forks, i);
	}
	return (i < len);
}

int	start_philo(t_data *data)
{
	t_pdata	pdata;
	t_philo	*philo;

	pdata.data = *data;
	pdata.forks = malloc(pdata.data.nphilo * sizeof(*pdata.forks));
	pdata.meals = malloc(pdata.data.nphilo * sizeof(*pdata.meals));
	pdata.threads = malloc(pdata.data.nphilo * sizeof(*pdata.threads));
	philo = malloc(pdata.data.nphilo * sizeof(*philo));
	if (!pdata.forks || !pdata.meals || !pdata.threads || !philo)
		ft_perror("Error: epic malloc fail\n");
	else if (init_struct(&pdata, philo, pdata.data.nphilo) == 0)
		start_threads(&pdata, philo, pdata.data.nphilo);
	free(pdata.forks);
	free(pdata.meals);
	free(pdata.threads);
	free(philo);
	if (!pdata.forks || !pdata.meals || !pdata.threads || !philo)
		return (ERR_AINTNOWAY);
	if (pdata.data.end == ERR_THREAD)
		return (ERR_THREAD);
	return (0);
}
