/*
 * Corne (Aurora rev1) keymap — optimized for PHP development
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include QMK_KEYBOARD_H

// --- Layer names ---
enum layers {
    _BASE,
    _LOWER,
    _RAISE,
    _FUNC
};

// --- Key aliases (readability) ---
#define OSM_ALT  OSM(MOD_LALT)
#define OSM_SFT  OSM(MOD_LSFT)
#define OSM_CTL  OSM(MOD_LCTL)
#define GUI_ENT  GUI_T(KC_ENT)
#define LOW_TAB  LT(_LOWER, KC_TAB)
#define RSE_BSP  LT(_RAISE, KC_BSPC)
#define CTL_ESC  LCTL_T(KC_ESC)
#define OSL_FUN  OSL(_FUNC)

// --- Combos ---
const uint16_t PROGMEM jk_combo[]  = {KC_J, KC_K, COMBO_END};    // Escape (Vim-style)
const uint16_t PROGMEM df_combo[]  = {KC_D, KC_F, COMBO_END};    // Minus (for -> in PHP)
const uint16_t PROGMEM sd_combo[]  = {KC_S, KC_D, COMBO_END};    // Equals (quick assignment)

combo_t key_combos[] = {
    COMBO(jk_combo, KC_ESC),
    COMBO(df_combo, KC_MINS),
    COMBO(sd_combo, KC_EQL),
};

// --- Tapping term per key ---
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Thumb keys: shorter tapping term for snappy layer/mod switching
        case GUI_ENT:
        case LOW_TAB:
        case RSE_BSP:
        case CTL_ESC:
            return 125;
        default:
            return TAPPING_TERM;  // 200ms from config.h
    }
}

// --- Keymap ---
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /*
     * BASE (QWERTY)
     * ┌──────┬──────┬──────┬──────┬──────┬──────┐   ┌──────┬──────┬──────┬──────┬──────┬──────┐
     * │ TAB  │  Q   │  W   │  E   │  R   │  T   │   │  Y   │  U   │  I   │  O   │  P   │ BSPC │
     * ├──────┼──────┼──────┼──────┼──────┼──────┤   ├──────┼──────┼──────┼──────┼──────┼──────┤
     * │ ALT  │  A   │  S   │  D   │  F   │  G   │   │  H   │  J   │  K   │  L   │  ;   │  '   │
     * ├──────┼──────┼──────┼──────┼──────┼──────┤   ├──────┼──────┼──────┼──────┼──────┼──────┤
     * │ SHFT │  Z   │  X   │  C   │  V   │  B   │   │  N   │  M   │  ,   │  .   │  /   │ FUNC │
     * └──────┴──────┴──┬───┴──┬───┴──┬───┴──┬───┘   └──┬───┴──┬───┴──┬───┴──┬───┴──────┴──────┘
     *                  │ CTRL │GUIENT│LOWTAB│           │RSEBSP│ SPC  │ SHFT │
     *                  └──────┴──────┴──────┘           └──────┴──────┴──────┘
     */
    [_BASE] = LAYOUT_split_3x6_3(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        OSM_ALT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        OSM_SFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, OSL_FUN,
                                   OSM_CTL, GUI_ENT, LOW_TAB,      RSE_BSP, KC_SPC,  OSM_SFT
    ),

    /*
     * LOWER — Symbols & Numbers (hold left thumb)
     * ┌──────┬──────┬──────┬──────┬──────┬──────┐   ┌──────┬──────┬──────┬──────┬──────┬──────┐
     * │  `   │  !   │  @   │  #   │  $   │  %   │   │  ^   │  &   │  *   │  (   │  )   │ DEL  │
     * ├──────┼──────┼──────┼──────┼──────┼──────┤   ├──────┼──────┼──────┼──────┼──────┼──────┤
     * │  ~   │  1   │  2   │  3   │  4   │  5   │   │  6   │  7   │  8   │  9   │  0   │  :   │
     * ├──────┼──────┼──────┼──────┼──────┼──────┤   ├──────┼──────┼──────┼──────┼──────┼──────┤
     * │      │      │  <   │  >   │  [   │  {   │   │  }   │  ]   │  ,   │  .   │  /   │      │
     * └──────┴──────┴──┬───┴──┬───┴──┬───┴──┬───┘   └──┬───┴──┬───┴──┬───┴──┬───┴──────┴──────┘
     *                  │      │      │██████│           │      │      │      │
     *                  └──────┴──────┴──────┘           └──────┴──────┴──────┘
     */
    [_LOWER] = LAYOUT_split_3x6_3(
        KC_GRV,  KC_EXLM, KC_AT,      KC_HASH,    KC_DLR,  KC_PERC,      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
        KC_TILD, KC_1,    KC_2,       KC_3,       KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    S(KC_SCLN),
        KC_TRNS, KC_NO,   S(KC_COMM), S(KC_DOT),  KC_LBRC, KC_LCBR,      KC_RCBR, KC_RBRC, KC_COMM, KC_DOT,  KC_SLSH, KC_TRNS,
                                      KC_TRNS,    KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS
    ),

    /*
     * RAISE — Navigation & Operators (hold right thumb)
     * ┌──────┬──────┬──────┬──────┬──────┬──────┐   ┌──────┬──────┬──────┬──────┬──────┬──────┐
     * │      │ DEL  │ INS  │  _   │  +   │ PGUP │   │      │      │      │  \   │  |   │      │
     * ├──────┼──────┼──────┼──────┼──────┼──────┤   ├──────┼──────┼──────┼──────┼──────┼──────┤
     * │      │ HOME │ END  │  -   │  =   │ PGDN │   │  ←   │  ↓   │  ↑   │  →   │ APP  │      │
     * ├──────┼──────┼──────┼──────┼──────┼──────┤   ├──────┼──────┼──────┼──────┼──────┼──────┤
     * │      │      │      │ COPY │PASTE │  ;   │   │ PLAY │ PREV │ NEXT │ VOL- │ VOL+ │      │
     * └──────┴──────┴──┬───┴──┬───┴──┬───┴──┬───┘   └──┬───┴──┬───┴──┬───┴──┬───┴──────┴──────┘
     *                  │CTLESC│      │      │           │██████│      │      │
     *                  └──────┴──────┴──────┘           └──────┴──────┴──────┘
     */
    [_RAISE] = LAYOUT_split_3x6_3(
        KC_NO,   KC_DEL,  KC_INS,  KC_UNDS, KC_PLUS, KC_PGUP,      KC_NO,   KC_NO,   KC_NO,   KC_BSLS, KC_PIPE, KC_NO,
        KC_NO,   KC_HOME, KC_END,  KC_MINS, KC_EQL,  KC_PGDN,      KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_APP,  KC_NO,
        KC_TRNS, KC_NO,   KC_NO,   C(KC_C), C(KC_V), KC_SCLN,      KC_MPLY, KC_MPRV, KC_MNXT, KC_VOLD, KC_VOLU, KC_TRNS,
                                   CTL_ESC, KC_TRNS, KC_NO,        KC_TRNS, KC_TRNS, KC_TRNS
    ),

    /*
     * FUNC — Function keys & System (one-shot from base)
     * ┌──────┬──────┬──────┬──────┬──────┬──────┐   ┌──────┬──────┬──────┬──────┬──────┬──────┐
     * │      │  F1  │  F2  │  F3  │  F4  │  F5  │   │  F6  │  F7  │  F8  │  F9  │ F10  │      │
     * ├──────┼──────┼──────┼──────┼──────┼──────┤   ├──────┼──────┼──────┼──────┼──────┼──────┤
     * │      │ F11  │ F12  │      │      │      │   │      │      │      │      │      │      │
     * ├──────┼──────┼──────┼──────┼──────┼──────┤   ├──────┼──────┼──────┼──────┼──────┼──────┤
     * │      │ CAPS │S+DEL │C+INS │S+INS │      │   │      │      │      │      │ BOOT │      │
     * └──────┴──────┴──┬───┴──┬───┴──┬───┴──┬───┘   └──┬───┴──┬───┴──┬───┴──┬───┴──────┴──────┘
     *                  │      │      │      │           │      │      │      │
     *                  └──────┴──────┴──────┘           └──────┴──────┴──────┘
     */
    [_FUNC] = LAYOUT_split_3x6_3(
        KC_NO,   KC_F1,   KC_F2,      KC_F3,      KC_F4,      KC_F5,        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_NO,
        KC_NO,   KC_F11,  KC_F12,     KC_NO,      KC_NO,      KC_NO,        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_CAPS, S(KC_DEL),  C(KC_INS),  S(KC_INS),  KC_NO,        KC_NO,   KC_NO,   KC_NO,   KC_NO,   QK_BOOT, KC_NO,
                                      KC_NO,      KC_NO,      KC_NO,        KC_NO,   KC_NO,   KC_NO
    )
};
