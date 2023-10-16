#!/bin/bash
#  Short script to toggle a GPIO pin at the highest frequency
#  possible using Bash - by Derek Molloy
echo 17 > /sys/class/gpio/export
sleep 0.5
echo "in" > /sys/class/gpio/gpio17/direction


echo 22 > /sys/class/gpio/export
sleep 0.5
echo "out" > /sys/class/gpio/gpio22/direction
echo 0 > /sys/class/gpio/gpio22/value

while true; do
    cat /sys/class/gpio/gpio17/value > /sys/class/gpio/gpio22/value
done


echo 17 > /sys/class/gpio/unexport
echo 22 > /sys/class/gpio/unexport