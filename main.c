/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chly-huc <chly-huc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 17:06:09 by shyrno            #+#    #+#             */
/*   Updated: 2021/09/16 15:51:44 by chly-huc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct/struct.h"

int verif_syntax(t_sh *sh)
{
	sh->ptr_cmd = sh->lst_cmd;
	if (!ft_strcmp(sh->ptr_cmd->cmd, "|") || !ft_strcmp(sh->ptr_cmd->cmd, "<") || !ft_strcmp(sh->ptr_cmd->cmd, "<<") || !ft_strcmp(sh->ptr_cmd->cmd, ">")
	|| !ft_strcmp(sh->ptr_cmd->cmd, ">>"))
		return (2);
	return (0);
}

int main(int argc, char **argv, char **env)
{
	int ret;
	t_sh *sh;

	sh = ft_malloc_sh();
	env_setup(sh, env);
	ret = 1;
	(void)argc;
	(void)argv;
	while(ret)
	{
		get_all_path(sh);
		// if(!(sh->input_str = readline("My Minishell ~> ")))
		// 	add_history(sh->input_str);
		ft_putstr_fd("My Minishell ~> ", 2);
		ret = get_next_line(0, &sh->input_str);
		if (!ft_strcmp(sh->input_str, ""))
			continue;
		if (!ver_quote(sh->input_str))
		{
			sh_free(sh);
			continue;
		}
		sh->input_str = dollarz(sh, sh->input_str);
		str_tolst(sh->input_str, sh);
		//ft_print_lst(sh->lst_cmd);
		quoting(sh);
		if (!verif_syntax(sh))
		{
			sh->ptr_cmd = sh->lst_cmd;
			exec(sh, sh->lst_cmd);
			sh_free(sh); 
			waitpid(-1, &sh->child_pid, 0);
			if (WIFEXITED(sh->child_pid))
				sh->child_pid = WEXITSTATUS(sh->child_pid);
			if (sh->stat == 1)
				exit(sh->exit_code);
			else if (sh->stat == 2)
				exit_code(sh, sh->child_pid);
			else
				exit_code(sh, sh->exit_code);	
			sh->stat = 0;
			sh->ret = 0;
			sh->child_pid = 0;
		}
		else
			exit_code(sh, 2);
		//printf("%d\n", ft_atoi(env_lstcontent(sh, "?")));
		return (ft_atoi(env_lstcontent(sh, "?")));
	}
}
