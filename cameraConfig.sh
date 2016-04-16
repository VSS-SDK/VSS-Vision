#!/bin/bash
if test "$1" = "1"; then
	uvcdynctrl -d video$1 --set='Saturation' 100
	uvcdynctrl -d video$1 --set='Brightness' 20
	uvcdynctrl -d video$1 --set='Contrast' 100
	uvcdynctrl -d video$1 --set='Hue' 0
	uvcdynctrl -d video$1 --set='Focus, Auto' 0
else
	uvcdynctrl -d video0 --set='Saturation' 100
	uvcdynctrl -d video0 --set='Brightness' 20
	uvcdynctrl -d video0 --set='Contrast' 100
	uvcdynctrl -d video0 --set='Hue' 0
	uvcdynctrl -d video0 --set='Focus, Auto' 0
fi