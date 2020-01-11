/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:44:38 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/01/10 20:50:08 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void set_virtual_origin(t_readline *readline)
{
	int i;
	t_point origin;

	origin = readline->o_cursor;
	i = readline->line_props.index;
	while (i > 0)
	{
		i--;
		origin.y += readline->line_props.details[i] / readline->col;
		origin.y += (readline->line_props.details[i] % readline->col) > 0;
		origin.x = 0;
	}
	readline->ov_cursor = origin;
}

int cursor_to_index(t_readline *readline, int cursor)
{
	int index;
	int i;

	i = readline->line_props.index;
	index = cursor;
	while (i)
	{
		i--;
		index += readline->line_props.details[i];	
	}
	return (index);
}

t_point index_to_cursor(t_readline *readline)
{
	int index;
	t_point cursor;

	cursor = readline->o_cursor;
	index = cursor.x;
	while (cursor.y)
	{
		cursor.y--;
		index += readline->line_props.details[cursor.y];
	}
	return (cursor);
}

void cur_goto(t_readline *readline, int cursor)
{
	t_point origin = readline->ov_cursor;

	origin = readline->ov_cursor;
	origin.y += (origin.x + cursor) / readline->col;
	origin.x = (origin.x + cursor) % readline->col;
	readline->cursor = cursor;
	readline->line_index = cursor_to_index(readline, cursor);
	tputs(tgoto(tgetstr("cm", 0), origin.x, origin.y), 0, output);
}

void get_cursor_position(t_readline *readline)
{
	char *buff;
	int col;
	int row;

	buff = (char[21]){0};
	while(1)
	{
		ft_putstr_fd("\e[6n", 0);
		read(0, buff, 20);
		if(ft_strchr(buff,'['))
			break;
	}
	// ft_putstr_fd("\e[6n", 0);
	// read(0, buff, 20);
	buff = (char *)ft_skip_unitl_char(buff, "[");
	row = ft_atoi(buff + 1);
	buff = (char *)ft_skip_unitl_char(buff, ";");
	col = ft_atoi(buff + 1);
	readline->o_cursor = (t_point){col - 1, row - 1};
	readline->ov_cursor = readline->o_cursor;
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
