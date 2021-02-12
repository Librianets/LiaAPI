#!/bin/bash
set -e

CPU=4
hostw32=win32
hostw64=win64
hostnx32=unix32
hostnx64=unix64
hostdef=$hostw32
NONE='\033[00m'
BOLD='\033[1m'
dirmake=./makefile
makefileglobal=makeglobal
traceval=

ME=`basename $0`

function print_help() 
{
echo -e "${BOLD}NAME ${NONE}"
echo "	$ME - обработчик makefile"	
echo ""
echo -e "${BOLD}SYNOPSIS ${NONE}"
echo "	$ME [OPTION]..."
echo ""
echo -e "${BOLD}DESCRIPTION ${NONE}"
echo "	Управляет сборкой проекта"
echo ""
echo "	-p"
echo "		make project"
echo "		"
echo "	-h"
echo "		print help"
echo ""
echo "	-t"
echo "		enable trace make"
echo ""
echo -e "${BOLD}AUTHOR ${NONE}"
echo "	Librianets. Team Liasteria."
echo ""
echo -e "${BOLD}DATA AND VERSION ${NONE}"
echo "	2020, 0.2a"
echo ""
}

function trace()
{
	traceval='--trace'
}

function project()
{
if [[ $2 = "dbg" ]]
then
	debugmode=1
else
	debugmode=0
fi

if [[ $1 = "full" ]]
then
	make $traceval -f $dirmake/$makefileglobal all_make_api --eval=host_win32=1, debugmode=$debugmode
elif [[ $1 = "make" ]]
then
	make $traceval -f $dirmake/$makefileglobal all_remake_api --eval=host_win32=1, debugmode=$debugmode
elif [[ $1 = "clean" ]]
then
	make $traceval -f $dirmake/$makefileglobal del_all --eval=host_win32=1, debugmode=$debugmode
elif [[ $1 = "test" ]]
then
	make $traceval -f $dirmake/$makefileglobal test_test --eval=host_win32=1, debugmode=$debugmode
else
	echo "not correct option project"
	return 255
fi

return 0
}

if [ $# = 0 ]; then
	print_help
fi

while getopts ":tp:h" opt
do
    case $opt in
        t) trace;;
        p) project $OPTARG;;
        h) print_help;;
        *) echo "Выбран не существующий параметр"; exit 1;;
    esac
done
#Сдвиг параметров сценария
#shift $(($OPTIND -1))


#        m) project $OPTARG;;
exit 0

# $OPTIND — хранит «внутренний индекс», по которому getopts определяет очередность выполнения опций;
# $OPTARG — содержит аргумент, передаваемый опции;
# $OPTERR — содержит код ошибки, обычно 1.