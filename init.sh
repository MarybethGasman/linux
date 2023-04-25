
#!/bin/sh

echo -e "\nhello, busybox!\n"

mount -t proc none /proc
mount -t sysfs none /sys
# mount -t debugfs none /sys/kernel/debug

mkdir /share
mount -t 9p -o trans=virtio,version=9p2000.L hostshare /share


ln -sf /dev/null /dev/tty2
ln -sf /dev/null /dev/tty3
ln -sf /dev/null /dev/tty4
 
echo -e "\nBoot took $(cut -d' ' -f1 /proc/uptime) seconds\n"
 
sh
