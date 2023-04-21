#!/bin/sh

OUTPUT=$(awk -vFILE=/tmp/.$USER.statusbar.cpu.${DISPLAY}.txt\~ -vFGCOLOR=${FGCOLOR}  -vCOL1="14" -vCOL2="6" '
BEGIN {
	while ((getline < FILE) > 0) {
		total = 0
		for (i = 2; i<=NF; i++)
			total += $i

		PREVIDLE[$1] = $5
		PREVTOTAL[$1] = total
	}
}

/^cpu/ {
	gsub("cpu", "", $1)
	if ($1 == "") {
		$1 = "A"
	}
	idle = $5
	total = 0
	for (i=2; i<=NF; i++)
		total += $i

	IDLE[$1] = $5
	TOTAL[$1] = total
	print $0 > FILE
}

END {
	OUTPUT=""
	print ""
	lrpad=6
	X=lrpad
	W=2

	for (i = 0; i < length(TOTAL) - 1; i++) {
		if (i % 2)
			COLOR=COL1
		else
			COLOR=COL2

		if (TOTAL[i]-PREVTOTAL[i] == 0)
			continue

		H=int(14*(1-(IDLE[i]-PREVIDLE[i])/(TOTAL[i]-PREVTOTAL[i])))
		Y=16-H
		OUTPUT=OUTPUT "^C" COLOR "^^r" X "," Y "," W "," H "^"
		X += 3
	}
	OUTPUT=OUTPUT "^d^^f" X+lrpad "^"
	if (TOTAL["A"]-PREVTOTAL["A"] != 0) {
		PCT=int((1-(IDLE["A"]-PREVIDLE["A"])/(TOTAL["A"]-PREVTOTAL["A"]))*100)
		printf("%s" FGCOLOR "%s%% CPU^d^\n",OUTPUT,PCT)
	}
}
' < /proc/stat)
echo $OUTPUT