#!/bin/sh

CFG_DIR=$1
if [ "$CFG_DIR" == "" ]; then
	CFG_DIR=${XDG_CONFIG_HOME:-${HOME}/.config}/dusk/themes
fi

if [ ! -e "$CFG_DIR" ]; then
	echo "Add theme files to $CFG_DIR"
	exit
fi

THEME=$(
	find "$CFG_DIR" -type f -name '*.res' \
	| sed -r 's#^(.*)/([^/]+)[.][^.]+$#\2|\0#' \
	| sort \
	| dmenu -p "dusk theme:" -RestrictReturn -RejectNoMatch -ShowNumbers -c -w 70% -l 50 -g 10 -d "|"
)

if [ "$THEME" != "" ]; then
	xrdb_reload.sh "$THEME"
fi
