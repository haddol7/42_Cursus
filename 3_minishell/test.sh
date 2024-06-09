#!/bin/sh

# 인자의 개수 출력
echo "Number of arguments: $#"

# 인자의 값 출력
echo "Arguments: $@"

# 개별 인자 출력
count=1
for arg in "$@"
do
    echo "Argument $count: $arg"
    count=$((count + 1))
done

