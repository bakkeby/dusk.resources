#!/bin/bash

PLAYER=$(cat /tmp/.playerctl_status_player.txt 2>/dev/null)

case $BLOCK_BUTTON in
	1) playerctl $PLAYER play-pause ;;
	2) playerctl $PLAYER play-pause ;;
	3) "$HOME"/bin/context_menu/playerctlmenu.sh ;;
	4) "$HOME"/bin/pulse/pulseaudio_increase_output_volume.sh ;;
	5) "$HOME"/bin/pulse/pulseaudio_decrease_output_volume.sh ;;
	6) playerctl $PLAYER position 5- ;;
	7) playerctl $PLAYER position 5+ ;;
	8) playerctl $PLAYER previous ;;
	9) playerctl $PLAYER next ;;
	*) notify-send -t 2000 "playerctl $PLAYER $BLOCK_BUTTON" & ;;
esac
