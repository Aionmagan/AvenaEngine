#! /bash/sh
a_flag=""

PROJECT_DIR=~/Desktop/spaceGame

. /opt/toolchains/dc/kos/environ.sh

#cd PROJECT_DIR

make dcclean

make dc

while getopts ':c' flags; do
	case "${flags}" in
		c) a_flag="true"
		   echo "it's working" ;;
		*) exit 1 ;;
	esac 
done

if [ "$a_flag" = "" ]
then 
	make  dcrunemu
else 
	make  dcrun
fi
