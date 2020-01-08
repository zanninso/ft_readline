/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 06:44:03 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/01/08 03:03:25 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

// void cur_move_by_word(t_readline *readline, int button)
// {
// 	const int current_cur = readline->cursor - readline->origin_cursor;
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
	if (readline->line_index - 1 < 0)
		return ;
	readline->line_index--;
	readline->cursor.x += readline->col - 1; 
	readline->cursor.y -= !(readline->cursor.x / readline->col);
	readline->cursor.x = readline->cursor.x % readline->col;
	cur_goto(readline, readline->cursor);
}

void cur_right(t_readline *readline)
{
	if (readline->line_index + 1 > readline->cmd->tmp_len)
		return ;
	readline->line_index++;
	readline->cursor.y += (readline->cursor.x + 1) / readline->col;
	readline->cursor.x = (readline->cursor.x + 1) % readline->col;
	cur_goto(readline, readline->cursor);
}
