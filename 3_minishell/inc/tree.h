/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:34:27 by daeha             #+#    #+#             */
/*   Updated: 2024/05/29 22:04:21 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

# include <stdlib.h>

typedef enum e_node_type
{
	N_CMD,
	N_AND,
	N_OR,
	N_PIPE,
	N_SUBSHELL,
	N_INPUT,
	N_OUTPUT,
	N_HERE_DOC,
	N_APPEND
}	t_node_type;

typedef struct s_node
{
	t_node_type		type;
	char			**cmd;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

#endif
