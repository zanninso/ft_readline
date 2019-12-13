/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 00:57:15 by aait-ihi          #+#    #+#             */
/*   Updated: 2019/12/13 00:56:29 by aait-ihi         ###   ########.fr       */
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
	int button;

	ft_printf("➜  ft_readline git:(master) ");
	init(&readline);
	while (1)
	{
		button = 0;
		if (read(0, &button, sizeof(int)) > 0)
		{
			if (button == BUTTON_UP)
				cur_up(&readline);
			else if (button == BUTTON_DOWN)
				cur_down(&readline);
			else if (button == BUTTON_RIGHT)
				cur_right(&readline);
			else if (button == BUTTON_LEFT)
				cur_left(&readline);
			else if (button == BUTTON_HOME)
				cur_left(&readline);
			else if (button == BUTTON_END)
				cur_left(&readline);
			else if (button == BUTTON_DEL || button == BUTTON_DEL2)
				remove_from_line(&readline);
			else if (button == BUTTON_ENTER)
				exit(0);
			else
				insert_in_line(&readline, button);
		}
	}
}
