#!/bin/sh

#echo "Your repo:"
#read repo
#git clone $repo
#TODO: Добавить парсинг ссылки для команды cd

while :
do
	git clone https://github.com/BabkaOrk/test_auto_maker.git

	if cmp -s old_history.txt ./test_auto_maker/history.txt ; then
		echo
		echo "Изменения отсутствуют"
		echo
		rm -rf test_auto_maker
	else
		cd test_auto_maker
		out=$(make 2>&1)
		if "$out" == ""; then
			echo
			echo OK
			echo
		else
			echo
			echo ERROR
			echo
		fi
		mv history.txt ../old_history.txt
		cd ..
		rm -rf test_auto_maker
	fi

	sleep 3
done