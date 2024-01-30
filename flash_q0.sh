#!/bin/bash

KEYBOARD_HOME="$(pwd)"
QMK_MODULE="modules/qmk_firmware"
export QMK_HOME="$KEYBOARD_HOME/$QMK_MODULE"
export KEYBOARD="keychron/q0/base"
export KEYMAP="custom"

cd $QMK_HOME
qmk flash -kb $KEYBOARD -km $KEYMAP

