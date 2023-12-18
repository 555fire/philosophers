/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_stats.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamiyaza <mamiyaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 22:55:04 by mamiyaza          #+#    #+#             */
/*   Updated: 2023/12/18 21:33:19 by mamiyaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	lock_printstat(t_data *d)
{
	d->printstat = LOCKED;
}

static void	unlock_printstat(t_data *d)
{
	d->printstat = UNLOCKED;
}

static void	set_errstat(t_data *d, t_errstat errstat)
{
	d->errstat = errstat;
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
	printf(ANSI_BOLD_RED"%s"ANSI_RESET"in %s, %d\n", s, func, line);
	unlock_printstat(d);
}

void	handle_error(t_data *d, t_errstat errstat, const char *func, int line)
{
	lock_printstat(d);
	set_errstat(d, errstat);
	print_errstat(d, errstat, func, line);
	unlock_printstat(d);
}

void	print_errstat(t_data *d, t_errstat errstat, const char *func, int line)
{
	char	*errmsg;

	if (errstat == ARGC_ERROR)
		errmsg = ERRMSG_ARGC;
	else if (errstat == ARGV_ERROR)
		errmsg = ERRMSG_ARGV;
	else if (errstat == MALLOC_ERROR)
		errmsg = ERRMSG_MALLOC;
	else if (errstat == CALLOC_ARGS_ERROR)
		errmsg = ERRMSG_CALLOC_ARGS;
	else if (errstat == THREAD_CREATE_ERROR)
		errmsg = ERRMSG_THREAD_CREATE;
	else if (errstat == THREAD_JOIN_ERROR)
		errmsg = ERRMSG_THREAD_JOIN;
	else if (errstat == MUTEX_INIT_ERROR)
		errmsg = ERRMSG_MUTEX_INIT;
	else if (errstat == MUTEX_DESTROY_ERROR)
		errmsg = ERRMSG_MUTEX_DESTROY;
	else if (errstat == MUTEX_LOCK_ERROR)
		errmsg = ERRMSG_MUTEX_LOCK;
	else if (errstat == MUTEX_UNLOCK_ERROR)
		errmsg = ERRMSG_MUTEX_UNLOCK;
	else if (errstat == GETTIMEOFDAY_ERROR)
		errmsg = ERRMSG_GETTIMEOFDAY;
	else if (errstat == USLEEP_ERROR)
		errmsg = ERRMSG_USLEEP;
	printf(ANSI_BOLD_RED"%s"ANSI_RESET"%s, %d\n", errmsg, func, line);
}
// void	print_errstat(t_data *d, t_errstat errstat)
// {
// 	if (errstat == ARGC_ERROR)
// 		printf(ANSI_BOLD_RED ERRMSG_ARGC ANSI_RESET);
// 	else if (errstat == ARGV_ERROR)
// 		printf(ANSI_BOLD_RED ERRMSG_ARGV ANSI_RESET);
// 	else if (errstat == MALLOC_ERROR)
// 		printf(ANSI_BOLD_RED ERRMSG_MALLOC ANSI_RESET);
// 	else if (errstat == CALLOC_ARGS_ERROR)
// 		printf(ANSI_BOLD_RED ERRMSG_CALLOC_ARGS ANSI_RESET);
// 	else if (errstat == THREAD_CREATE_ERROR)
// 		printf(ANSI_BOLD_RED ERRMSG_THREAD_CREATE ANSI_RESET);
// 	else if (errstat == THREAD_JOIN_ERROR)
// 		printf(ANSI_BOLD_RED ERRMSG_THREAD_JOIN ANSI_RESET);
// 	else if (errstat == MUTEX_INIT_ERROR)
// 		printf(ANSI_BOLD_RED ERRMSG_MUTEX_INIT ANSI_RESET);
// 	else if (errstat == MUTEX_DESTROY_ERROR)
// 		printf(ANSI_BOLD_RED ERRMSG_MUTEX_DESTROY ANSI_RESET);
// 	else if (errstat == MUTEX_LOCK_ERROR)
// 		printf(ANSI_BOLD_RED ERRMSG_MUTEX_LOCK ANSI_RESET);
// 	else if (errstat == MUTEX_UNLOCK_ERROR)
// 		printf(ANSI_BOLD_RED ERRMSG_MUTEX_UNLOCK ANSI_RESET);
// 	else if (errstat == GETTIMEOFDAY_ERROR)
// 		printf(ANSI_BOLD_RED ERRMSG_GETTIMEOFDAY ANSI_RESET);
// 	else if (errstat == USLEEP_ERROR)
// 		printf(ANSI_BOLD_RED ERRMSG_USLEEP ANSI_RESET);
// }

t_funcstat	print_philostat(t_personal *own_p, t_philostat philostat)
{
	time_t	usec_time;
	time_t	relative_usec;

	usec_time = get_usec_time(own_p->d);
	if (own_p->d->errstat)
		return (1);
	relative_usec = usec_time - own_p->d->start_time;
	lock_printstat(own_p->d);
	if (philostat == WAITING_FOR_TAKINGFORK)
		;
	else if (philostat == HASTOOKFORK)
		printf("%ld%s%zu%s%s", relative_usec, SPC, own_p->philo_i, SPC, MSG_TOOKFORK);
	else if (philostat == EATING)
		printf("%ld%s%zu%s%s", relative_usec, SPC, own_p->philo_i, SPC, MSG_EATING);
	else if (philostat == SLEEPING)
		printf("%ld%s%zu%s%s", relative_usec, SPC, own_p->philo_i, SPC, MSG_SLEEPING);
	else if (philostat == THINKING)
		printf("%ld%s%zu%s%s", relative_usec, SPC, own_p->philo_i, SPC, MSG_THINKING);
	else if (philostat == DEAD)
		printf("%ld%s%zu%s%s", relative_usec, SPC, own_p->philo_i, SPC, MSG_DIED);
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
		printf("%ld%s%zu%s%s", usec_time, SPC, own_p->philo_i, SPC, MSG_DIED);
	else if (simustat == REACHED_N_TIMES_MUST_EAT)
		;
	unlock_printstat(own_p->d);
	return (0);
}
