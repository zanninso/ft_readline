/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 08:55:45 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/12/15 02:09:15 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static t_cmd_history *history_list = NULL;

t_cmd_history *get_cmd_history_head(void)
{
	return (history_list);
}

void add_to_history(char *str)
{
	t_cmd_history *tmp;
	if (!str)
		return;
	if (tmp = ft_memalloc(sizeof(t_cmd_history)))
	{
		history_list->prev = tmp;
		tmp->next = history_list;
		history_list = tmp;
	}
}

void free_history(void)
{
	t_cmd_history *next;
	while(history_list)
	{
		next = history_list->next;
		if(*history_list->line)
		{
			ft_bzero(history_list->line, history_list->len);
			free(history_list->line);
		}
		free(history_list);
		history_list = next;
	}
}
