#!/bin/bash

COMMAND="uvcdynctrl"
DEVICE=" -d video"
PARAM=" --set='Saturation' 100\n --set='Brightness' 20\n --set='Contrast' 100\n --set='Hue' 0\n --set='Focus, Auto' 0"
SAVEIFS="$IFS"
IFS=$(echo -en "\n")

if [ "$1" = "1" ] && [ -e "/dev/video$1" ]; then

        for i in $(echo -e "$PARAM") ;do 
                $COMMAND"$DEVICE""$1 $i"
        done

elif [ -e "/dev/video0" ]; then

        for i in $(echo -e "$PARAM") ;do 
                $COMMAND "$DEVICE""0 $i"
        done
else 
        echo -e "\n\t Camera not found. \n\t Camera nao encontrada. \n"

fi


IFS="$SAVEIFS"
unset COMMAND PARAM SAVEIFS
