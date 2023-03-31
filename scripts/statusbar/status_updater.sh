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

wait_for_ipc_handler () {
	seconds=$1

	for (( d=1; d<=2*${seconds}; d++ ))
	do
		sleep 0.5
		duskc --ignore-reply get_monitors 2>/dev/null 1>&2
		if [ $? = 0 ]; then
			return
		fi
	done

	echo "Failed to reach IPC handler, bailing"
	exit
}

SETSTATUS="duskc --ignore-reply run_command setstatus"
secs=0

while true; do

	$SETSTATUS 0 "$($DIR/clock)"

	if [ $? != 0 ]; then
		wait_for_ipc_handler 30
	fi

	$SETSTATUS 2 "$($DIR/mem)" &
	$SETSTATUS 3 "$($DIR/cpu)" &

	if [ $((secs % 60)) = 0 ]; then
		$SETSTATUS 5 "$($DIR/mouse_battery)" &
		$SETSTATUS 1 "$($DIR/volume)" &
		$SETSTATUS 9 "$($DIR/kblayout)" &
	fi

	# Update these once after 1 minute, i.e. hourly
	if [ $secs = 60 ]; then
		$SETSTATUS 4 "$($DIR/sysupdates)" &
		$SETSTATUS 7 "$($DIR/statusbutton)" &
	fi

	# Restart script every hour
	if [ $secs = 3600 ]; then
		exec ${BASH_SOURCE[0]}
	fi

	((secs+=1))
	sleep 1
done
