#!/bin/bash

DIR=$(dirname ${BASH_SOURCE[0]})

case $BLOCK_STATUS in
	0) $DIR/clock_click ;;
	1) $DIR/volume_click ;;
	2) $DIR/mem_click ;;
	3) $DIR/cpu_click ;;
	4) $DIR/sysupdates_click ;;
	5) $DIR/mouse_battery_click ;;
	7) $DIR/statusbutton_click ;;
	9) $DIR/kblayout_click ;;
	*) notify-send -t 2000 "Unknown status $BLOCK_STATUS clicked $BLOCK_BUTTON" & ;;
esac
