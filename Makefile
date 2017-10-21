all: tweak-gnome-shell

tweak-gnome-shell: tweak-gnome-shell.c
	cc -Wall -O2 -o $@ tweak-gnome-shell.c
