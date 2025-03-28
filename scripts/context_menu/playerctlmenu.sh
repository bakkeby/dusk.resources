#!/bin/bash

TMP_TYPE_FILE=/tmp/.playerctl_status_player.txt

CHOICE=$(playerctl --list-all | awk '
	BEGIN {
		print "Player	auto\n"
	}

	{
		print $0 "	--player=" $0
	}

	END {
		print "auto	auto"
		print "all	--all-players"
	}

' | xmenu)

test -z "$CHOICE" && exit  # user cancelled

if [ "$CHOICE" == "auto" ]; then
	CHOICE=""
fi

echo "$CHOICE" > "$TMP_TYPE_FILE"
kill -USR1 $(pgrep -f playerctl_updater.sh)
