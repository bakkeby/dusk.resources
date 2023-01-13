#!/bin/sh

THEME=$1
if [ "$THEME" != "" ] && [ -e "$THEME" ]; then
	sed --follow-symlinks -i "0,/^#include \".*\/themes\/.*[.]res\"$/{s|^#include \".*\"|#include \"$THEME\"|}" ~/.Xresources
	echo "Loading theme: $THEME"
fi

xrdb ~/.Xresources
if [ $? -eq 0 ]; then
	duskc --ignore-reply run_command xrdb
	#killall -q -USR1 st
	#killall -q -HUP dunst
	xrdb_generate_sequences.sh
	for TTY in /dev/pts/[0-9]*; do
		cat ${XDG_CACHE_HOME:-~/.cache}/wal/sequences > $TTY
	done
fi