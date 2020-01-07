/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 06:44:03 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/01/07 03:27:08 by aait-ihi         ###   ########.fr       */
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
	if (button == BUTTON_ALT_RIGHT)
	{
		tmp = (char *)ft_skip_unitl_char(line + current_cur, " '\";");
		tmp = ft_skip_chars(tmp, " '\";");
	}
	else if (button == BUTTON_ALT_LEFT)
	{
		tmp = ft_rskip_chars(line, " '\";", current_cur - 1);
		tmp = ft_rskip_unitl_char(line, " '\";", tmp - line);
		if (ft_isinstr(*tmp, " '\";"))
			tmp++;
	}
	diff = tmp - &line[current_cur];
	cur_goto(readline, readline->cursor + diff);
}

t_point calc_cur_pos(t_point cursor, int col_count)
{
	t_point ret;

	ret.x = cursor.x % col_count;
	ret.y = cursor.y + (cursor.x / col_count);
}

void cur_up(t_readline *readline)
{
	char *tmp;
	char *tmp2;
	int diff;

	diff = 0;
	tmp = ft_rskip_chars(readline->cmd->tmp_line, "\n", readline->line_index);
	if (*tmp != '\n')
		return;
	tmp--;
	diff = readline->cmd->line - tmp;
	tmp = ft_rskip_chars(tmp, "\n", readline->line_index - diff);
	diff = readline->cmd->line - tmp;
	readline->cursor.y -= !!(diff % readline->col) + (diff / readline->col);
	tmp2 = ft_skip_chars(tmp, "\n");
	readline->cursor.x = ft_min(readline->cursor.x, tmp2 - tmp);
	diff += readline->cursor.x;
	readline->line_index -= diff;
	cur_goto(readline, readline->cursor);
}

void cur_down(t_readline *readline)
{
	char *tmp;
	char *tmp2;
	int diff;

	diff = 0;
	tmp = ft_skip_chars(readline->cmd->tmp_line + readline->line_index, "\n");
	if (*tmp == '\n')
	{
		tmp++;
		diff = tmp - readline->cmd->tmp_line;
		readline->cursor.y += diff % readline->col + diff / readline->col;
	}
	tmp2 = ft_skip_chars(tmp, "\n");
	readline->cursor.x = ft_min(readline->cursor.x, tmp2 - tmp);
	diff += readline->cursor.x;
	readline->line_index += diff;
	cur_goto(readline, readline->cursor);
}

void cur_left(t_readline *readline)
{
	if ()
		readline->cursor -= readline->cursor == readline->origin_cursor ? 0 : 1;
	cur_goto(readline, readline->cursor);
}

void cur_right(t_readline *readline)
{
	const int limit = readline->cmd->tmp_len + readline->origin_cursor;

	readline->cursor += readline->cursor == limit ? 0 : 1;
	cur_goto(readline, readline->cursor);
}
