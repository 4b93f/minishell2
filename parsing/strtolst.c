/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtolst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 17:31:11 by chly-huc          #+#    #+#             */
/*   Updated: 2021/07/21 20:05:45 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../struct/struct.h"


char *str_to_lst(char *str, t_sh *sh)
{
	int squote = 0;
	int dquote = 0;
	
	int i;
	int j;

	j = 0;
	i = 0;
	// while(str[j] && (str[j] == ' '))

	i = j;
	if (str[i] == '|')
		while(str[i] == '|')
			i++;
	else
	{
		while(str[i] && str[i] != ' ')
		{
			i++;
			if (str[i] == '|')
				break;
		}
	}
	cmd_lstaddback(&sh->lst_cmd, cmd_lstnew(ft_substr(str, j, i - j)));
	return (str + i);
}