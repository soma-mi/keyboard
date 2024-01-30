# via 有効化
VIA_ENABLE = no
# リンク時最適化
LTO_ENABLE = yes
# OS判定 有効化
OS_DETECTION_ENABLE = yes
# マウスキー 有効化
MOUSEKEY_ENABLE = yes
# COMBO 有効化
COMBO_ENABLE = yes
# TAP DANCE 有効化
TAP_DANCE_ENABLE = yes
# DEBUG
CONSOLE_ENABLE = no
# 動的マクロ 有効化
DYNAMIC_MACRO_ENABLE = yes
# 遅延実行 有効化
DEFERRED_EXEC_ENABLE = yes

SRC += features/jtu_custom_keycodes/default/jtu_custom_keycodes.c
SRC += features/casemodes.c
SRC += features/qmk-vim/src/mac_mode.c
SRC += features/qmk-vim/src/process_func.c
SRC += features/qmk-vim/src/numbered_actions.c
SRC += features/qmk-vim/src/motions.c
SRC += features/qmk-vim/src/actions.c
SRC += features/qmk-vim/src/modes.c
SRC += features/qmk-vim/src/vim.c
SRC += functions.c
