/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkopiika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 21:06:00 by mkopiika          #+#    #+#             */
/*   Updated: 2019/07/24 21:10:31 by mkopiika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	error_valid(int fail)
{
	if (fail == FAIL_MAZE)
	{
		ft_putendl("Error: No current maze or is empty");
		exit(FAIL_MAZE);
	}
	else if (fail == FAIL_INVAL)
	{
		ft_putendl("Error: Invalid maze");
		exit(FAIL_INVAL);
	}
}

void		get_error(int fail)
{
	if (fail == FAIL_ARGC)
	{
		ft_putendl("Usage: ./wolf3d <need to get maze>");
		exit(FAIL_ARGC);
	}
	else if (fail == FAIL_MALLOC)
	{
		ft_putendl("Error: Malloc failed");
		exit(FAIL_MALLOC);
	}
	else if (fail == FAIL_NAME)
	{
		ft_putendl("Error: Invalid maze name or run from another directory");
		exit(FAIL_NAME);
	}
	else if (fail == FAIL_SDL)
	{
		ft_putendl("Error: SDL failed:");
		ft_putendl(SDL_GetError());
		exit(FAIL_SDL);
	}
	error_valid(fail);
}
