/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:44:12 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/12/15 02:29:33 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void history_next(t_readline *readline)
{
	if (readline->current_cmd_history && readline->current_cmd_history->next)
	{
		if (readline->current_cmd_history->line != readline->line)
		{
			ft_strdel(&readline->tmp_line);
			readline->tmp_line = readline->line;
			readline->tmp_len = readline->line_len;
		}
		readline->current_cmd_history = readline->current_cmd_history->next;
		readline->line = readline->current_cmd_history->line;
		readline->line_len = readline->current_cmd_history->len;
		rewrite_line(readline);
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
	}
	else if(readline->tmp_line)
	{
		if (readline->current_cmd_history)
			if (readline->current_cmd_history->line != readline->line)
				ft_strdel(&readline->line);
		readline->line = readline->tmp_line;
		readline->line_len = readline->tmp_len;
		rewrite_line(readline);
	}
}

void end_readline(t_readline *readline)
{
	if(readline->line_len)
	add_to_history(readline->line);
	ft_printf("➜  ft_readline git:(master) ");
	init(readline);
}
