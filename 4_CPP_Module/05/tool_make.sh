#!/bin/bash

## CHECK LIST ##

# OCF를 다 지켰나요?
# PDF를 꼼꼼히 읽었나요?
# 평가 로그를 참고하셨나요?
# fsanitize=address, leaks 체크 다 하셨나요?
# codespace에서 성공적으로 컴파일 하나요?
# remote repo에 다 잘 올라갔나요?
# 과제 외의 파일들은 다 삭제했나요?

# 인자가 없거나 잘못된 경우 메시지 출력
if [ "$#" -ne 1 ] || { [ "$1" != "make" ] && [ "$1" != "clean" ]; }; then
    echo "Usage: $0 make | clean"
    exit 1
fi

dirs=("ex00" "ex01" "ex02" "ex03" "ex04" "ex05" "ex06" "ex07" "ex08" "ex09")

if [ "$1" == "make" ]; then
    command="make"
else
    command="make fclean"
fi

for dir in "${dirs[@]}"; do
    if [ -d "$dir" ]; then
        echo "Entering directory: $dir"
        cd "$dir" || exit
        $command
        cd .. 
    fi
done
