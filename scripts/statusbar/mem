#!/bin/bash
COLOR_SYMBOL=^C4^
# COLOR_HL=^c#FFF7D4^
# COLOR_NORM=^c#C6BDBD^
COLOR_HL=
COLOR_NORM=
symb=''
mem=($(free | awk '/Mem/ {printf "%d %d", $3 / 1024.0, $2 / 1024.0 }'))
NOM=${mem[0]}
DEN=${mem[1]}
echo "${COLOR_SYMBOL}${symb:(((${#symb}-1)*${mem[0]}/${mem[1]})):1}^d^ ${COLOR_HL}${NOM}${COLOR_NORM}/${DEN} ${COLOR_HL}MB^d^"
