
Debian
====================
This directory contains files used to package nanited/nanite-qt
for Debian-based Linux systems. If you compile nanited/nanite-qt yourself, there are some useful files here.

## nanite: URI support ##


nanite-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install nanite-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your naniteqt binary to `/usr/bin`
and the `../../share/pixmaps/nanite128.png` to `/usr/share/pixmaps`

nanite-qt.protocol (KDE)

