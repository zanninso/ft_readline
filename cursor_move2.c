/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_move2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 22:42:16 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/01/15 03:17:33 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void to_start_or_end(t_readline *readline, int button)
{
	const int len = readline->line_props.details[readline->line_props.index];
	const int count = readline->line_props.linecount;
	int cursor;

	cursor = 0;
	if (button == BUTTON_HOME)
	{
		if (readline->cursor == 0 && readline->line_props.index > 0)
		{
			readline->line_props.index--;
			set_virtual_origin(readline);
		}
	}
	else
	{
		if (readline->cursor == len - 1 && readline->line_props.index < count - 1)
		{
			readline->line_props.index++;
			set_virtual_origin(readline);
		}
		cursor = readline->line_props.details[readline->line_props.index];
		cursor -= readline->line_props.index != count - 1;
	}
	cur_goto(readline, cursor);
}

void cur_goto(t_readline *readline, int cursor)
{
	t_point origin;

	origin = readline->ov_cursor;
	origin.y += (origin.x + cursor) / readline->col;
	origin.x = (origin.x + cursor) % readline->col;
	readline->cursor = cursor;
	set_idnex_from_cursor(readline);
	// char *cm = tgetstr("cm", 0);
	// char *tmp = tgoto(cm, origin.x, origin.y);
	ft_printf("\e[%d;%dH", origin.y + 1, origin.x + 1);
	// ft_putstr(tmp);
	//tputs(tgoto(tgetstr("cm", 0), origin.x, origin.y), 0, output);
}