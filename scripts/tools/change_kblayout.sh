#!/bin/bash

if [ -z $IPCCMD ]; then
	IPCCMD=duskc
fi

LANG=$(echo -e "gb\nno\nfr" | xmenu)
if [ "$LANG" != "" ]; then
	setxkbmap $LANG
	if [ $? -eq 0 ]; then
		$IPCCMD run_command setstatus 9 $LANG
	fi
fi
