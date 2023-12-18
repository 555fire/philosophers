/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_stats.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamiyaza <mamiyaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 22:55:04 by mamiyaza          #+#    #+#             */
/*   Updated: 2023/12/18 11:52:42 by mamiyaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	lock_printstat(t_data *d)
{
	while (1)
	{
		if (d->printstat == UNLOCKED)
		{
			d->printstat = LOCKED;
			printf("\tLOCKED!\n");
			break ;
		}
	}
}

void	unlock_printstat(t_data *d)
{
	if (d->printstat == UNLOCKED)
	{
		d->errstat = PRINTSTAT_ERROR;
		printf(ERRMSG_PRINTSTAT);
	}
	else
	{
		d->printstat = UNLOCKED;
		printf("\tUNLOCKED!\n");
	}
}

void	print_atomically(t_data *d, char *s)
{
	lock_printstat(d);
	printf("%s", s);
	unlock_printstat(d);
}

void	perror_atomically(t_data *d, char *s, const char *func, int line)
{
	lock_printstat(d);
	printf("%s [%s, %d]", s, func, line);
	unlock_printstat(d);
}

// void	print_errstat_without_d(t_errstat errstat)
// {
// 	if (errstat == ARGC_ERROR)
// 		printf("%s", ERRMSG_ARGC);
// 	else if (errstat == ARGV_ERROR)
// 		printf("%s", ERRMSG_ARGV);
// 	else if (errstat == CALLOC_ARGS_ERROR)
// 		printf("%s", ERRMSG_CALLOC_ARGS);
// 	else if (errstat == MALLOC_ERROR)
// 		printf("%s", ERRMSG_MALLOC);
// 	return ;
// }
//
// void	print_errstat(t_data *d, t_errstat errstat)
// {
// 	lock_printstat(d);
// 	if (errstat == NO_ERROR)
// 		;
// 	else if (errstat == ARGC_ERROR)
// 		printf("%s", ERRMSG_ARGC);
// 	else if (errstat == ARGV_ERROR)
// 		printf("%s", ERRMSG_ARGV);
// 	else if (errstat == MALLOC_ERROR)
// 		printf("%s", ERRMSG_MALLOC);
// 	else if (errstat == CALLOC_ARGS_ERROR)
// 		printf("%s", ERRMSG_CALLOC_ARGS);
// 	else if (errstat == THREAD_CREATE_ERROR)
// 		printf("%s", ERRMSG_THREAD_CREATE);
// 	else if (errstat == THREAD_JOIN_ERROR)
// 		printf("%s", ERRMSG_THREAD_JOIN);
// 	else if (errstat == MUTEX_INIT_ERROR)
// 		printf("%s", ERRMSG_MUTEX_INIT);
// 	else if (errstat == MUTEX_DESTROY_ERROR)
// 		printf("%s", ERRMSG_MUTEX_DESTROY);
// 	else if (errstat == MUTEX_LOCK_ERROR)
// 		printf("%s", ERRMSG_MUTEX_LOCK);
// 	else if (errstat == MUTEX_UNLOCK_ERROR)
// 		printf("%s", ERRMSG_MUTEX_UNLOCK);
// 	else if (errstat == GETTIMEOFDAY_ERROR)
// 		printf("%s", ERRMSG_GETTIMEOFDAY);
// 	else if (errstat == USLEEP_ERROR)
// 		printf("%s", ERRMSG_USLEEP);
// 	unlock_printstat(d);
// 	return ;
// }

t_funcstat	print_philostat(t_personal *own_p, t_philostat philostat)
{
	time_t	usec_time;
	time_t	relative_usec_time;

	usec_time = get_usec_time(own_p->d);
	if (own_p->d->errstat)
		return (1);
	relative_usec_time = usec_time - own_p->d->start_time;
	lock_printstat(own_p->d);
	if (philostat == WAITING_FOR_TAKINGFORK)
		;
	else if (philostat == HASTOOKFORK)
		printf("%ld%s%zu%s%s", relative_usec_time, SPC, own_p->philo_i, SPC, MSG_TOOKFORK);
	else if (philostat == EATING)
		printf("%ld%s%zu%s%s", relative_usec_time, SPC, own_p->philo_i, SPC, MSG_EATING);
	else if (philostat == SLEEPING)
		printf("%ld%s%zu%s%s", relative_usec_time, SPC, own_p->philo_i, SPC, MSG_SLEEPING);
	else if (philostat == THINKING)
		printf("%ld%s%zu%s%s", relative_usec_time, SPC, own_p->philo_i, SPC, MSG_THINKING);
	else if (philostat == DEAD)
		printf("%ld%s%zu%s%s", relative_usec_time, SPC, own_p->philo_i, SPC, MSG_DIED);
	unlock_printstat(own_p->d);
	return (0);
}

t_funcstat	print_simustat(t_personal *own_p, t_simustat simustat)
{
	time_t	usec_time;

	usec_time = get_usec_time(own_p->d);
	if (own_p->d->errstat)
		return (1);
	lock_printstat(own_p->d);
	if (simustat == SIMU_LASTS)
		;
	else if (simustat == ANY_ERROR_HAS_OCCURRED)
		;
	else if (simustat == ANYONE_DIED)
		printf("%ld%s%zu%s%s",usec_time, SPC, own_p->philo_i, SPC, MSG_DIED);
	else if (simustat == REACHED_N_TIMES_MUST_EAT)
		;
	unlock_printstat(own_p->d);
	return (0);
}
