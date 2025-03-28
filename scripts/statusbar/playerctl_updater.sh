#!/bin/bash

IDX=0

function get_cached_player() {
	TMP_PLAYER_FILE=/tmp/.playerctl_status_player.txt
	PLAYER=""

	# If the file exists then check if the player still exists
	if [[ -f "$TMP_PLAYER_FILE" ]]; then
		PLAYER=$(<"$TMP_PLAYER_FILE")
		# Clear player if it no longer exists
		if [[ -n "$PLAYER" ]] && [[ "$(playerctl $PLAYER status 2>&1)" == "No players found" ]]; then
			echo "" > "$TMP_PLAYER_FILE"
			PLAYER=""
		fi
	fi

	echo "$PLAYER"
}

function get_title() {
	PLAYER=$(get_cached_player)
	IFS='¦' read -r ARTIST TITLE <<< "$(playerctl $PLAYER metadata --format "{{artist}}¦{{title}}")"

	if [[ "$TITLE" != "$ARTIST"* ]]; then
		TITLE="$ARTIST $TITLE"
	fi

	case "$(playerctl $PLAYER status)" in
		"Playing")
			SYMBOL=""
			;;
		"Paused")
			SYMBOL=""
			;;
		"Stopped")
			SYMBOL=""
			IDX=0
			;;
	esac

	echo "$TITLE¦$SYMBOL¦$IDX"
}

trap 'IFS='¦' read -r TITLE SYMBOL IDX <<< "$(get_title)";' SIGUSR1  # Update title on USR1 signal

while $RUNNING; do
	duskc --ignore-reply setstatus 8 "^c#e5e8ec^$SYMBOL ^c#FF9977^$(marquee -t "$TITLE" -i $IDX -n 20)^d^"
	if [[ "$SYMBOL" == "" ]]; then
		((IDX++));
	fi
	sleep 1
done
