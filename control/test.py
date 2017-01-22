import fcntl
import sys
import termios

with open(sys.argv[1], 'w') as fd:
    for c in "drive 2 2000\n":
        fcntl.ioctl(fd, termios.TIOCSTI, c)


screen -S 37411.ttys000.MBP-Valentin-2 -p 0 -X stuff "drive 0 000`echo -ne '\015'`"



screen -S 37411.ttys000.MBP-Valentin-2 -p0 -X hardcopy $(tty)

screen -S 37411.ttys000.MBP-Valentin-2 -p0 -X hardcopy $(echo test.txt)

`echo -ne '\015'`
