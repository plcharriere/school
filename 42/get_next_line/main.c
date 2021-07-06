/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcharrie <pcharrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 16:18:23 by pcharrie          #+#    #+#             */
/*   Updated: 2020/03/10 11:34:15 by pcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int		main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		ret;

	fd = 0;
	if (argc > 2)
		printf("Usage: %s or %s path/to/file\n", argv[0], argv[0]);
	else if (argc == 2 && (fd = open(argv[1], O_RDONLY)) < 0)
		printf("Failed to open file '%s'\n", argv[1]);
	else
	{
		while ((ret = get_next_line(fd, &line)) > 0)
		{
			printf("[%d] : %s\n", ret, line);
			free(line);
		}
		printf("[%d]\n", ret);
		close(fd);
		return (0);
	}
	return (1);
}
