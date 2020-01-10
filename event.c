/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:44:12 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/01/08 18:00:51 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void init(t_readline *readline);

void end_readline(t_readline *readline, int suit)
{
	t_cmd_history *head;
	char *tmp;

	head = get_cmd_history_head();
	if (suit && head->next)
	{
		tmp = ft_strnjoin((char *[]){head->next->line, "\n", readline->cmd->tmp_line}, 3);
		ft_strdel(&head->line);
		free(readline->cmd->tmp_line);
		readline->cmd->tmp_line = tmp;
		readline->cmd->tmp_len = head->next->len + readline->cmd->tmp_len + 1;
		head = head->next;
	}
	head->line = readline->cmd->tmp_line;
	head->len = readline->cmd->tmp_len;
	readline->cmd->tmp_line = NULL;
	ft_strdel(&head->tmp_line);
	clean_hsitory();
	ft_printf("\n➜  ft_readline git:(master) ");
	init(readline);
}
