/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 13:19:03 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/01/14 09:02:03 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

// static void	signal_stop(int sig)
// {
// 	(void)sig;
// 	g_select->config.c_lflag |= (ICANON | ECHO);
// 	tputs(tgetstr("te", NULL), 1, output);
// 	tputs(tgetstr("ve", NULL), 1, output);
// 	ioctl(0, TIOCSTI, (char[2]){g_select->config.c_cc[VSUSP], 0});
// 	tcsetattr(0, 0, &g_select->config);
// 	signal(SIGTSTP, SIG_DFL);
// }

// static void	signal_cont(int sig)
// {
// 	g_select->config.c_lflag &= ~(ECHO | ICANON);
// 	if (tcsetattr(0, 0, &g_select->config) < 0)
// 		puts("error");
// 	tputs(tgetstr("ti", 0), 0, output);
// 	tputs(tgetstr("vi", 0), 0, output);
// 	signal(SIGTSTP, signal_stop);
// 	signal_resize(sig);
// }

void		signal_resize(int sig)
{
	struct winsize	wn;

	(void)sig;
	ioctl(1, TIOCGWINSZ, &wn);
	g_readline->col = wn.ws_col;
	g_readline->row = wn.ws_row;
}

void		set_signal(void)
{
	int	sig;

	sig = 0;
	while (sig++ < 32)
		signal(sig, SIG_IGN);
	// signal(SIGCONT, signal_cont);
	// signal(SIGTSTP, signal_stop);
	signal(SIGWINCH, signal_resize);
}
