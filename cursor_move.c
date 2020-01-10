/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 06:44:03 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/01/10 00:05:35 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

// void cur_move_by_word(t_readline *readline, int button)
// {
// 	const int current_cur = readline->cursor - readline->o_cursor;
// 	int diff;
// 	char *tmp;
// 	const char *line = readline->cmd->tmp_line;

// 	tmp = NULL;
// 	if (button == BUTTON_ALT_RIGHT)
// 	{
// 		tmp = (char *)ft_skip_unitl_char(line + current_cur, " '\";");
// 		tmp = ft_skip_chars(tmp, " '\";");
// 	}
// 	else if (button == BUTTON_ALT_LEFT)
// 	{
// 		tmp = ft_rskip_chars(line, " '\";", current_cur - 1);
// 		tmp = ft_rskip_unitl_char(line, " '\";", tmp - line);
// 		if (ft_isinstr(*tmp, " '\";"))
// 			tmp++;
// 	}
// 	diff = tmp - &line[current_cur];
// 	cur_goto(readline, readline->cursor + diff);
// }

void cur_up(t_readline *readline)
{
	if (readline->line_props.index <= 0)
	{
		readline->line_props.index--;
		cur_goto(readline, readline->cursor);
	}
}

void cur_down(t_readline *readline)
{
	if (readline->line_props.index < readline->line_props.linecount)
	{
		readline->line_props.index++;
		cur_goto(readline, readline->cursor);
	}
}

void cur_left(t_readline *readline)
{
	if (readline->line_index - 1 < 0)
		return;
	readline->cursor.x--;
	cur_goto(readline, readline->cursor);
}

void cur_right(t_readline *readline)
{
	if (readline->line_index + 1 > readline->cmd->tmp_len)
		return;
	if (readline->cmd->tmp_line[readline->line_index] == '\n')
	{
		readline->cursor.x = 0;
		readline->cursor.y++;
	}
	else
		readline->cursor.x++;
	cur_goto(readline, readline->cursor);
}
