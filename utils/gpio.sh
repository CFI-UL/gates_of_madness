#!/bin/sh

if [ -z "$1" -o -z "$2" ]
then
    echo "Usage: $0 PIN [1|0]"
    exit 1
fi

echo $2 > /sys/class/gpio/gpio$1/value
