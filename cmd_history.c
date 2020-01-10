/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 08:55:45 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/01/09 17:16:32 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static t_cmd_history *history_list = NULL;

t_cmd_history *get_cmd_history_head(void)
{
	return (history_list);
}

void add_to_history(char *str, int len)
{
	t_cmd_history *tmp;

	if (!str)
		return;
	if ((tmp = ft_memalloc(sizeof(t_cmd_history))))
	{
		if (history_list)
			history_list->prev = tmp;
		tmp->next = history_list;
		tmp->line = str;
		tmp->tmp_line = ft_strdup(str);
		tmp->len = len;
		tmp->tmp_len = len;
		history_list = tmp;
	}
}

void free_history(void)
{
	t_cmd_history *next;

	while (history_list)
	{
		next = history_list->next;
		if (*history_list->line)
		{
			ft_bzero(history_list->line, history_list->len);
			free(history_list->line);
		}
		free(history_list);
		history_list = next;
	}
}

void clean_hsitory()
{
	t_cmd_history **next;
	t_cmd_history *to_free;

	next = &history_list;
	while (*next)
	{
		if (!(*next)->line || !*(*next)->line)
		{
			to_free = *next;
			*next = (*next)->next;
			free(to_free->line);
			if (to_free->tmp_line != to_free->line)
				free(to_free->tmp_line);
			free(to_free);
			continue;
		}
		else
			break;
		next = &(*next)->next;
	}
}

void move_in_history(t_readline *readline, int button)
{
	char *new_line;
	//const int cursor = readline->o_cursor;

	if (button == BUTTON_UP && readline->cmd->next)
		readline->cmd = readline->cmd->next;
	else if (button == BUTTON_DOWN && readline->cmd->prev)
		readline->cmd = readline->cmd->prev;
	if (!readline->cmd->tmp_line)
		if ((new_line = ft_strdup(readline->cmd->line)))
		{
			readline->cmd->tmp_line = new_line;
			readline->cmd->tmp_len = readline->cmd->len;
			readline->line_props.details = get_line_details(readline);
		}
	rewrite_line(readline);
	readline->cursor = readline->o_cursor;
	readline->line_index = 0;
	//cur_goto(readline, cursor + readline->cmd->tmp_len);
}
