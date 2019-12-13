/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:44:38 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/12/13 01:42:36 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void get_cursor_position(t_readline *readline)
{
	char *buff;
	int col;
	int row;

	buff = (char[20]){0};
	ft_putstr_fd("\e[6n", 0);
	read(0, buff, 20);
	row = ft_atoi(buff + 2);
	buff = (char *)ft_skip_unitl_char(buff, ";");
	col = ft_atoi(buff + 1);
	readline->origin_cursor = (row - 1) * readline->col + col - 1;
	readline->cursor = readline->origin_cursor;
}

int output(int c)
{
	ft_putchar(c);
	return (0);
}

// void	configure_terminal(t_ft_select *ft_select)
// {
// 	if (tcgetattr(0, &ft_select->config) < 0)
// 		ft_die(ERR_TERM_GET_ARG, -2);
// 	ft_select->config.c_lflag &= ~(ECHO | ICANON);
// 	if (tcsetattr(0, 0, &ft_select->config) < 0)
// 		ft_die(ERR_TERM_SET_ARG, -3);
// 	if (tgetent(NULL, getenv("TERM")) <= 0)
// 		ft_die(ERR_TERM_INIT, -4);
// 	tputs(tgetstr("ti", 0), 0, output);
// 	tputs(tgetstr("vi", 0), 0, output);
// }
