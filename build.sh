#!/bin/sh

#-------------------
# Foreground Colors
#-------------------

# Black - White
FB="$(tput setaf 0)"      # black
FW="$(tput setaf 7)"      # white

# RGB
FR="$(tput setaf 1)"      # red
FG="$(tput setaf 2)"      # green
FB="$(tput setaf 4)"      # blue

# CMY
FC="$(tput setaf 6)"      # cyan
FM="$(tput setaf 5)"      # magenta
FY="$(tput setaf 3)"      # yellow

#-------------------
# Background colors
#-------------------

# black - white
BB="$(tput setab 0)"      # black
BW="$(tput setab 7)"      # white

# RGB
BR="$(tput setab 1)"      # red
BG="$(tput setab 2)"      # green
BB="$(tput setab 4)"      # blue

# CMY
BC="$(tput setab 6)"      # cyan
BM="$(tput setab 5)"      # magenta
BY="$(tput setab 3)"      # yellow

#---------------
# Text commands
#---------------

TB="$(tput bold)"         # bold text
TD="$(tput dim)"          # dim text
TC="$(tput sgr0)"         # clear any coloring

NL="\n"                   # new line

#----------------------------------

clear

printf "${BM}${FY} Compiling from source ${TC}${NL}${NL}"

g++ -std=c++2b -Wall \
main.cpp src/glad/*.c src/ImGui/*.cpp -I ./include/ \
-lGL -lglfw \
-o main.out

if [ $? -eq 0 ]; then
    printf "${NL}${FG}${BM} Compiling was successful! ${TC}${NL}${NL}"

    ./main.out

    if [ $? -eq 0 ]; then
        printf "${NL}${FG}${BC} Program ended! ${TC}${NL}${NL}"
    else
        printf "${NL}${FR}${BC} Program crashed! ${TC}${NL}${NL}"
    fi
else
    printf "${NL}${FR}${BM} Compiling failed! ${TC}${NL}${NL}"
fi