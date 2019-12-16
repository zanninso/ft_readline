/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:44:12 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/12/16 03:22:36 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void init(t_readline *readline);

void history_next(t_readline *readline, int dir)
{
	if (readline->history_index + dir < 0)
	{
		if (readline->tmp_line)
		{
			if (readline->current_cmd_history)
				if (readline->current_cmd_history->line != readline->line)
					ft_strdel(&readline->line);
			readline->line = readline->tmp_line;
			readline->line_len = readline->tmp_len;
			readline->tmp_line = NULL;
			rewrite_line(readline);
			cur_goto(readline, readline->origin_cursor + readline->line_len);
		}
	}
	else
	{
	}
	if (readline->current_cmd_history)
	{
		if (readline->current_cmd_history->line != readline->line)
		{
			ft_strdel(&readline->tmp_line);
			readline->tmp_line = readline->line;
			readline->tmp_len = readline->line_len;
		}
		if (readline->current_cmd_history->next)
			readline->current_cmd_history = readline->current_cmd_history->next;
		readline->line = readline->current_cmd_history->line;
		readline->line_len = readline->current_cmd_history->len;
		rewrite_line(readline);
		cur_goto(readline, readline->origin_cursor + readline->line_len);
	}
}

void history_previous(t_readline *readline)
{
	if (readline->current_cmd_history && readline->current_cmd_history->prev)
	{
		if (readline->current_cmd_history->line != readline->line)
		{
			ft_strdel(&readline->tmp_line);
			readline->tmp_line = readline->line;
			readline->tmp_len = readline->line_len;
		}
		readline->current_cmd_history = readline->current_cmd_history->prev;
		readline->line = readline->current_cmd_history->line;
		readline->line_len = readline->current_cmd_history->len;
		rewrite_line(readline);
		cur_goto(readline, readline->origin_cursor + readline->line_len);
	}
	else if (readline->tmp_line)
	{
		if (readline->current_cmd_history)
			if (readline->current_cmd_history->line != readline->line)
				ft_strdel(&readline->line);
		readline->line = readline->tmp_line;
		readline->line_len = readline->tmp_len;
		readline->tmp_line = NULL;
		rewrite_line(readline);
		cur_goto(readline, readline->origin_cursor + readline->line_len);
	}
}

void end_readline(t_readline *readline)
{
	if (readline->line_len)
		add_to_history(readline->line, readline->line_len);
	ft_printf("\n➜  ft_readline git:(master) ");
	init(readline);
}
