#!/bin/bash

DIR=$(dirname "${BASH_SOURCE[0]}")

cleanup() {
    pkill -P $$  # Kill all child processes of this script
    exit 0
}

"$DIR"/playerctl_updater.sh &

trap 'cleanup' SIGINT SIGTERM EXIT  # Run cleanup when the script is killed

playerctl -F status | while read -r; do
    kill -USR1 $(pgrep -f playerctl_updater.sh)
done;
