#!/usr/bin/env bash
run() {
	if [ ! $(pgrep -f $1) ]
  then
    $@&
  fi
}

# if [ $(pgrep -f "dwm_autorun") ] ; then
# 	echo "Already Started"
# 	exit
# fi

sleep 5
numlockx &
xmodmap -e "clear lock" &
xmodmap -e "keycode 66 = Escape NoSymbol Escape" &
setxkbmap -option caps:escape &
setxkbmap -layout pt &
xsetroot -cursor_name left_ptr &
if [ -f "$(which i3lock-fancy)" ]; then 
  xss-lock -- i3lock-fancy &
else
  xss-lock -- i3lock &
fi
# xscreensaver -no-splash &
wmname compiz

# run lxsession
run lxpolkit
run picom
run nm-applet
# run nitrogen --restore
run ~/scripts/set_wallpaper
# run parcellite
# run clipmenud
run xfce4-clipman
if [ -f "$(which xfce4-notifyd)" ]; then
  run xfce4-notifyd
else
  run dunst
fi
run xsettingsd
run sxhkd
run nextcloud
xmodmap ~/.Xmodmap

#dwmblocks
if test -x "$(which dwmblocks)"; then
  run dwmblocks
else
  run ~/app/dwm-6.2/dwm_statusbar
fi


