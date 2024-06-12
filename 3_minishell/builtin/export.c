/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeha <daeha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 20:41:57 by daeha             #+#    #+#             */
/*   Updated: 2024/06/12 22:31:59 by daeha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void ms_export(char **arg, t_env *stat)
{
	if (arg != NULL || stat != NULL)
		printf("ms_export func detected\n");
}
// //if node->cmd[0] == export일 때 이 함수를 들어왔다고 가정.
// void	export(t_node *node)
// {
// 	int	i;

// 	i = 0;
// 	if (node->cmd[1] == NULL)
// 		//env전체 출력 -> 앞에 접두사로 declare -x 붙이고, ascii 문자 정렬 순서대로 출력..
// 	while (node->cmd[i] != NULL)
// 	{
// 		// = 혹은 += 으로 앞뒤 스플릿.
// 		//에러인지
// 		//name만 들어왓는지
// 		//word 도 들어왔는지
// 		//띄어쓰기 까지 .. -> 어차피 스필리팅이 될 것임.
// 	}
// 		//= 전까지 스플릿해서 env 에 저장해야겠다!
// 	//올바르지 않은형식은 에러처리...
// 	// 1. 변수 컨벤션에 맞지 않거나,.(영어 _ 이외의 글자가 있는경우, 숫자가 가장 앞에 오는 경우)
// 	// 2. 띄어쓰기 있는 경우

// }

// export a                            #key값만 생성
// export b=                           #value에 아무 값 없음
// export c=hello          
// export c+=world                     #환경변수 뒤에 덧붙이기
// export d="oh      my          god"  #echo출력과 export출력 다름
// export e=elephant f=flower
