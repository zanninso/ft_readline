/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 06:44:03 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/12/18 00:16:48 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void cur_move_by_word(t_readline *readline, int button)
{
	const int current_cur = readline->cursor - readline->origin_cursor;
	int diff;
	char *tmp;
	const char *line = readline->cmd->tmp_line;

	tmp = NULL;
	if(button == BUTTON_ALT_RIGHT)
	{
		tmp = (char *)ft_skip_unitl_char(line + current_cur, " '\";");
		tmp = ft_skip_chars(tmp, " '\";");
	}
	else if(button == BUTTON_ALT_LEFT)
	{
		tmp = ft_rskip_chars(line, " '\";", current_cur - 1);
		tmp = ft_rskip_unitl_char(line, " '\";", tmp - line);
		if(ft_isinstr(*tmp, " '\";"))
			tmp++;
	}
	diff = tmp - &line[current_cur];
	cur_goto(readline, readline->cursor + diff);
}

// void cur_up(t_readline *readline)
// {
// 	const int limit = readline->origin_cursor + readline->col;
	
// 	readline->cursor -= readline->cursor >= limit ? readline->col : 0;
// 	cur_goto(readline, readline->cursor);
// }

// void cur_down(t_readline *readline)
// {
// 	const int col = readline->col;
// 	const int limit = readline->origin_cursor + readline->line_len - col;

// 	readline->cursor += readline->cursor <= limit ? readline->col : 0;
// 	cur_goto(readline, readline->cursor);
// }

void cur_left(t_readline *readline)
{
	readline->cursor -= readline->cursor == readline->origin_cursor ? 0 : 1;
	cur_goto(readline, readline->cursor);
}

void cur_right(t_readline *readline)
{
	const int limit = readline->cmd->tmp_len + readline->origin_cursor;
	
	readline->cursor += readline->cursor == limit ? 0 : 1;
	cur_goto(readline, readline->cursor);
}
