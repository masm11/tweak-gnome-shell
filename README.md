# Tweak gnome-shell lockscreen fadein/out

## Prerequisites

GNOME3 on archlinux.

## Installation

```sh
make
```

This builds `tweak-gnome-shell`.

Place tweak-gnome-shell in `/etc/pacman.d/bin/`, and tweak-gnome-shell.hook
in `/etc/pacman.d/hooks/`. If one or both of the directories doesn't exist,
create them.

## Testing

```sh
sudo pacman -S gnome-shell
```

This reinstalls gnome-shell, and tweak-gnome-shell is invoked while the reinstallation. You see a line like this:
```
(3/4) Tweaking libgnome-shell.so...
```

After you logout and login, fadein/out of lockscreen will be smooth.

## Author

Yuuki Harano &lt;masm@masm11.ddo.jp&gt;
