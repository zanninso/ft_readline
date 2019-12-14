/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 00:57:15 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/12/14 10:59:58 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void init(t_readline *readline)
{
	g_readline = readline;
	ft_bzero(readline, sizeof(t_readline));
	readline->line = ft_strdup("");
	if (tcgetattr(0, &readline->config) < 0)
		puts("error");
	readline->config.c_lflag &= ~(ECHO | ICANON);
	if (tcsetattr(0, 0, &readline->config) < 0)
		puts("error");
	tgetent(NULL, getenv("TERM"));
	signal_resize(0);
	get_cursor_position(readline);
}

int main()
{
	t_readline readline;
	char  buff[4001];
	int r;
	int button;

	ft_printf("➜  ft_readline git:(master) ");
	init(&readline);
	while (1)
	{
		ft_bzero(buff, 4001);
		if ((r = read(0, buff, 4000)) > 0)
		{
			button = *((int *)buff);
			if(r > 4)
				insert_in_line(&readline, buff);
			else if (button == BUTTON_UP)
				cur_up(&readline);
			else if (button == BUTTON_DOWN)
				cur_down(&readline);
			else if (button == BUTTON_RIGHT)
				cur_right(&readline);
			else if (button == BUTTON_LEFT)
				cur_left(&readline);
			else if (button == BUTTON_HOME)
				cur_goto(&readline, readline.origin_cursor);
			else if (button == BUTTON_END)
				cur_goto(&readline, readline.origin_cursor + readline.line_len);
			else if (button == BUTTON_ALT_RIGHT || button == BUTTON_ALT_LEFT)
				cur_move_by_word(&readline, button);
			else if (button == BUTTON_DEL || button == BUTTON_DEL2)
				remove_from_line(&readline);
			else if (button == BUTTON_ENTER)
				exit(0);
			else 
				insert_in_line(&readline, buff);
		}
	}
}
