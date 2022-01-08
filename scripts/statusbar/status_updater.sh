#!/bin/bash

DIR=$(dirname ${BASH_SOURCE[0]})

for pid in $(pidof -x "status_updater.sh"); do
	if [ $pid != $$ ]; then
		if [ "$(cat /proc/$pid/environ | tr '\0' '\n' | awk '/^DISPLAY/')" == "DISPLAY=$DISPLAY" ]; then
			echo "$(date +"%F %T"): status_updater.sh is already running with PID $pid, killing"
			kill $pid
		fi
	fi
done

# Add an artificial sleep to wait for the IPC handler to be ready to process requests
sleep 0.5

SETSTATUS="duskc --ignore-reply run_command setstatus"

$SETSTATUS 7 "$($DIR/statusbutton)" &

secs=0

while true; do

	$SETSTATUS 0 "$($DIR/clock)" &
	$SETSTATUS 2 "$($DIR/mem)" &
	$SETSTATUS 3 "$($DIR/cpu)" &

	if [ $((secs % 60)) = 0 ]; then
		$SETSTATUS 5 "$($DIR/mouse_battery)" &
		$SETSTATUS 1 "$($DIR/volume)" &
	fi

	if [ $((secs % 3600)) = 0 ]; then
		$SETSTATUS 4 "$($DIR/sysupdates)" &
	fi

	((secs+=1))
	sleep 1
done
