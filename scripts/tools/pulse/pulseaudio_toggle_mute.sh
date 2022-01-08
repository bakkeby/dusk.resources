#!/bin/sh
# Mutes/unmutes the current audio output

pactl set-sink-mute @DEFAULT_SINK@ toggle
duskc --ignore-reply run_command setstatus 1 "$(~/bin/statusbar/volume)"