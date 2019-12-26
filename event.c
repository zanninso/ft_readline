/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:44:12 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/12/26 02:06:21 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void init(t_readline *readline);

void end_readline(t_readline *readline, int suit)
{
	t_cmd_history *head;

	head = get_cmd_history_head();
	if (suit)
	{
		head->next->line = ft_strjoin(head->next->line, readline->cmd->tmp_line);
		head->next->len = head->next->len + readline->cmd->tmp_len;
		if (head->tmp_line != head->line)
			ft_strdel(&head->tmp_line);
		ft_strdel(&head->line);
	}
	else
	{
		head->line = readline->cmd->tmp_line;
		ft_strdel(&head->tmp_line);
		head->len = readline->cmd->tmp_len;
	}
	readline->cmd->tmp_line = NULL;
	clean_hsitory();
	ft_printf("\n➜  ft_readline git:(master) ");
	init(readline);
}
