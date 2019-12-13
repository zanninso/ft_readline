/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 06:44:03 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/12/13 14:20:30 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void cur_goto(t_readline *readline, int cursor)
{
	int co;
	int li;

	li = cursor / readline->col;
	co = cursor % readline->col;
	readline->cursor = cursor;
	tputs(tgoto(tgetstr("cm", 0), co, li), 0, output);
}

void cur_up(t_readline *readline)
{
	const int limit = readline->origin_cursor + readline->col;
	
	readline->cursor -= readline->cursor >= limit ? readline->col : 0;
	cur_goto(readline, readline->cursor);
}

void cur_down(t_readline *readline)
{
	const int col = readline->col;
	const int limit = readline->origin_cursor + readline->line_len - col;

	readline->cursor += readline->cursor <= limit ? readline->col : 0;
	cur_goto(readline, readline->cursor);
}

void cur_left(t_readline *readline)
{
	readline->cursor -= readline->cursor == readline->origin_cursor ? 0 : 1;
	cur_goto(readline, readline->cursor);
}

void cur_right(t_readline *readline)
{
	const int limit = readline->line_len + readline->origin_cursor;
	
	readline->cursor += readline->cursor == limit ? 0 : 1;
	cur_goto(readline, readline->cursor);
}
