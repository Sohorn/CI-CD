#!/bin/bash
if scp ./src/cat/s21_cat ./src/grep/s21_grep zekemath@192.168.100.10:~/ ; then
    ssh zekemath@192.168.100.10 "sudo mv s21_cat s21_grep /usr/local/bin"
    exit 0
fi
