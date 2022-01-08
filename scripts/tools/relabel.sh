#!/bin/sh
# Sets the class of a window, depends on dmenu and xdotool

LABEL=$(echo | dmenu)
if [ ! -z "$LABEL" ]; then
	xdotool getactivewindow set_window --class "$LABEL"
fi