#!/bin/bash

## CHECK LIST ##

# OCF를 다 지켰나요?
# PDF를 꼼꼼히 읽었나요?
# 평가 로그를 참고했나요?
# fsanitize=address, leaks 체크 다 하셨나요?
# codespace에서 성공적으로 컴파일 하나요?
# remote repo에 다 잘 올라갔나요?
# 과제 외의 파일들은 다 삭제했나요?
# 파일명들의 철자가 다 올바른가요?

GREEN="\033[0;32m"
YELLOW="\033[0;33m"  
RESET="\033[0m"      

dirs=("ex00" "ex01" "ex02" "ex03" "ex04" "ex05" "ex06" "ex07" "ex08" "ex09")

if [ "$1" == "m" ] || [ "$1" == "make" ]; then
    command="make"
elif [ "$1" == "c" ] || [ "$1" == "clean" ]; then
    command="make fclean"
elif [ "$1" == "e" ] || [ "$1" == "exec" ]; then
    command="${dirs[@]}"
else
    echo -e "${YELLOW}Invalid argument. m, make | c, clean | e, exec${RESET}"
    exit 1
fi

for dir in "${dirs[@]}"; do
    if [ -d "$dir" ]; then
        echo -e "${GREEN}================== Entering directory: $dir ==================\n${RESET}"
        cd "$dir" || exit
        if [ "$1" == "e" ] || [ "$1" == "exec" ]; then
			./$dir
        else
            $command
        fi
        cd ..
		echo -e ""
	fi
done

echo -e "${GREEN}==================👻 DONE! 👻==================${RESET}"
