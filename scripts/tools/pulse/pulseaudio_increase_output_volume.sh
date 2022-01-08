#!/bin/sh
# Increases the current audio output volume

pactl set-sink-volume @DEFAULT_SINK@ '+5%'
duskc --ignore-reply run_command setstatus 1 "$(~/bin/statusbar/volume)"