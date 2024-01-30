#!/bin/bash

KEYBOARD_HOME="$(pwd)"
QMK_MODULE="modules/qmk_firmware"
export QMK_HOME="$KEYBOARD_HOME/$QMK_MODULE"

if [[ ! -d "$QMK_HOME" ]]
then
    echo "Add git sub-modules..."
    git submodule add -f https://github.com/qmk/qmk_firmware "$QMK_MODULE"
fi
echo "Update git sub-modules..."
git submodule sync --recursive
git submodule update --init --recursive --progress

echo "Creating symbolic link..."
ln -s "$KEYBOARD_HOME/src/keyboards/alpaca/wfeclipse/keymaps/custom" "$QMK_HOME/keyboards/alpaca/wfeclipse/keymaps"
ln -s "$KEYBOARD_HOME/src/keyboards/keychron/q0/base/keymaps/custom" "$QMK_HOME/keyboards/keychron/q0/base/keymaps"

