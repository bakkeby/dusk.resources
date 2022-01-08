#!/bin/sh
# Toggles audio output, e.g. headphones <--> speakers
#
# Note that changing the output sink through the  command line
# interface can only take effect if stream target device reading
# is disabled which can be achieved by editing the corresponing
# line in /etc/pulse/default.pa to:
#    load-module module-stream-restore restore_device=false
#

SINK=$(pactl info | awk '/Default Sink/ { print $NF }')
NEXT=$(pactl list short sinks | awk -vSINK="$SINK" '
	NR == 1 || PREVIOUS_SINK == SINK {
		NEXT=$1
	}
	{
		PREVIOUS_SINK=$2
	}
	END {
		print NEXT
	}
')

pacmd set-default-sink $NEXT
for INPUT in $(pactl list short sink-inputs | cut -f 1); do
	pactl move-sink-input $INPUT $NEXT
done

duskc --ignore-reply run_command setstatus 1 "$(~/bin/statusbar/volume)"

# On some systems one may have to change the profile of the same card, e.g.
#   pactl set-card-profile 0 output:hdmi-stereo
#
# Check available profiles by running:
#   pactl list cards
#
# Then look at the "Profiles:" section and the "Active Profile:" section
#
