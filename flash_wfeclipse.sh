#!/bin/bash

KEYBOARD_HOME="$(pwd)"
QMK_MODULE="modules/qmk_firmware"
export QMK_HOME="$KEYBOARD_HOME/$QMK_MODULE"
export KEYBOARD="alpaca/wfeclipse"
export KEYMAP="custom"

cd $QMK_HOME
qmk flash -kb $KEYBOARD -km $KEYMAP

