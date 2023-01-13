#!/bin/sh

xrdb -query | awk '
	$1 ~ /^\*\.color([0-9]+):$/ {
		split($1,F,"r")
		printf "\033]4;%d;%s\033\\", F[2], $2
	}
	$1 ~ /^\*\.cursor:$/ {
		printf "\033]12;%s\033\\", $2
	}
	$1 ~ /^\*\.foreground:$/ {
		printf "\033]10;%s\033\\", $2
		printf "\033]13;%s\033\\", $2
		printf "\033]17;%s\033\\", $2
		printf "\033]4;256;%s\033\\", $2
	}
	$1 ~ /^\*\.background:$/ {
		printf "\033]11;%s\033\\", $2
		printf "\033]19;%s\033\\", $2
		printf "\033]4;232;%s\033\\", $2
		printf "\033]708;%s\033\\", $2
	}
' > ${XDG_CACHE_HOME:-~/.cache}/wal/sequences
