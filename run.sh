#!/bin/bash

#	Save users settings that are to be changed
#	Sets user terminal to desired settings
#	Loads settings back after closing
profileID=$(gsettings get org.gnome.Terminal.ProfilesList default)
profileID=${profileID:1:-1} # remove leading and trailing single quotes

original_config=".resources/original_config.conf"
game_config=".resources/game_config.conf"

# $1: Profile ID
# $2: Save destination
# Saves profile to destin[[2~]
function save_profile()
{
	#echo $1 > $2 
	truncate -s 0 $2
	dconf read /org/gnome/terminal/legacy/profiles:/:$1/font >> $2
	dconf read /org/gnome/terminal/legacy/profiles:/:$1/use-system-font >> $2 
	dconf read /org/gnome/terminal/legacy/profiles:/:$1/use-theme-colors >> $2
	dconf read /org/gnome/terminal/legacy/profiles:/:$1/use-theme-transparency >> $2
	
	#dconf read /org/gnome/terminal/legacy/profiles:/:$1/pallete >> $2 
}

# Load from save.
function load_profile()
{
	IFS=$'\n' read -d '' -r -a lines < $2
	dconf write /org/gnome/terminal/legacy/profiles:/:$1/font "${lines[0]}"
	dconf write /org/gnome/terminal/legacy/profiles:/:$1/use-system-font "${lines[1]}"
	dconf write /org/gnome/terminal/legacy/profiles:/:$1/use-theme-colors "${lines[2]}"
	dconf write /org/gnome/terminal/legacy/profiles:/:$1/use-theme-transparency "${lines[3]}"
	#echo "${lines[@]}"
}

save_profile $profileID $original_config
load_profile $profileID $game_config
exec gnome-terminal.real --maximize --full-screen -x "`dirname \"$0\"`"/Application
load_profile $profileID $original_config

