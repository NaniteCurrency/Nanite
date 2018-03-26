Sample init scripts and service configuration for nanited
==========================================================

Sample scripts and configuration files for systemd, Upstart and OpenRC
can be found in the contrib/init folder.

    contrib/init/nanited.service:    systemd service unit configuration
    contrib/init/nanited.openrc:     OpenRC compatible SysV style init script
    contrib/init/nanited.openrcconf: OpenRC conf.d file
    contrib/init/nanited.conf:       Upstart service configuration file
    contrib/init/nanited.init:       CentOS compatible SysV style init script

1. Service User
---------------------------------

All three startup configurations assume the existence of a "nanite" user
and group.  They must be created before attempting to use these scripts.

2. Configuration
---------------------------------

At a bare minimum, nanited requires that the rpcpassword setting be set
when running as a daemon.  If the configuration file does not exist or this
setting is not set, nanited will shutdown promptly after startup.

This password does not have to be remembered or typed as it is mostly used
as a fixed token that nanited and client programs read from the configuration
file, however it is recommended that a strong and secure password be used
as this password is security critical to securing the wallet should the
wallet be enabled.

If nanited is run with "-daemon" flag, and no rpcpassword is set, it will
print a randomly generated suitable password to stderr.  You can also
generate one from the shell yourself like this:

bash -c 'tr -dc a-zA-Z0-9 < /dev/urandom | head -c32 && echo'

Once you have a password in hand, set rpcpassword= in /etc/nanite/nanite.conf

For an example configuration file that describes the configuration settings,
see contrib/debian/examples/nanite.conf.

3. Paths
---------------------------------

All three configurations assume several paths that might need to be adjusted.

Binary:              /usr/bin/nanited
Configuration file:  /etc/nanite/nanite.conf
Data directory:      /var/lib/nanited
PID file:            /var/run/nanited/nanited.pid (OpenRC and Upstart)
                     /var/lib/nanited/nanited.pid (systemd)

The configuration file, PID directory (if applicable) and data directory
should all be owned by the nanite user and group.  It is advised for security
reasons to make the configuration file and data directory only readable by the
nanite user and group.  Access to nanite-cli and other nanited rpc clients
can then be controlled by group membership.

4. Installing Service Configuration
-----------------------------------

4a) systemd

Installing this .service file consists on just copying it to
/usr/lib/systemd/system directory, followed by the command
"systemctl daemon-reload" in order to update running systemd configuration.

To test, run "systemctl start nanited" and to enable for system startup run
"systemctl enable nanited"

4b) OpenRC

Rename nanited.openrc to nanited and drop it in /etc/init.d.  Double
check ownership and permissions and make it executable.  Test it with
"/etc/init.d/nanited start" and configure it to run on startup with
"rc-update add nanited"

4c) Upstart (for Debian/Ubuntu based distributions)

Drop nanited.conf in /etc/init.  Test by running "service nanited start"
it will automatically start on reboot.

NOTE: This script is incompatible with CentOS 5 and Amazon Linux 2014 as they
use old versions of Upstart and do not supply the start-stop-daemon uitility.

4d) CentOS

Copy nanited.init to /etc/init.d/nanited. Test by running "service nanited start".

Using this script, you can adjust the path and flags to the nanited program by
setting the NANITED and FLAGS environment variables in the file
/etc/sysconfig/nanited. You can also use the DAEMONOPTS environment variable here.

5. Auto-respawn
-----------------------------------

Auto respawning is currently only configured for Upstart and systemd.
Reasonable defaults have been chosen but YMMV.
