#!/bin/sh
# Decreases the current audio output volume

pactl set-sink-volume @DEFAULT_SINK@ '50%'
duskc --ignore-reply run_command setstatus 1 "$(~/bin/statusbar/volume)"