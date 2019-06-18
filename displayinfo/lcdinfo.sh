#!/bin/bash --posix

cpu_temp=`cat /sys/class/thermal/thermal_zone0/temp`

cpu_load=`uptime | awk '{print $9,$10,$11,$12}'`

./displayinfo4lcd ${cpu_temp} ${cpu_load}
