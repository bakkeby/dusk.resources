#!/bin/sh
# Mutes/unmutes the all audio output

pactl list sinks | grep -q "Mute: yes"
MUTE=$?

for SINK_ID in $(pacmd list-sinks | awk '/index:/ { print $NF }'); do
	pactl set-sink-mute $SINK_ID $MUTE
done

duskc --ignore-reply run_command setstatus 1 "$(~/bin/statusbar/volume)"