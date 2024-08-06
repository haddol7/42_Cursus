#ifndef MAP_H
# define MAP_H

# include "structures.h"
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

void	error_exit(void);
int		argument_validity(int argc, char *file_name);
void    map_validity(int fd);

#endif