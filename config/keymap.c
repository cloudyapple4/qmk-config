#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif

enum layer_names {
    DEFAULT,
    LOWER,
    RAISE,
    ADJUST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEFAULT] = LAYOUT_split_3x5_2(
	KC_QUOTE,          KC_COMMA,         KC_DOT,         KC_P,               KC_Y,            KC_F,            KC_G,              KC_C,             KC_R,             KC_L, 
	KC_A,              KC_O,             KC_E,           KC_U,               KC_I,            KC_D,            KC_H,              KC_T,             KC_N,             KC_S,
	LSFT_T(KC_SCLN),   LCTL_T(KC_Q),     LALT_T(KC_J),   KC_K,               KC_X,            KC_B,            KC_M,              RALT_T(KC_W),     RCTL_T(KC_V),     RSFT_T(KC_Z),
	                                                     LT(LOWER, KC_ENT),  KC_SPC,          KC_BSPC,         LT(RAISE, KC_TAB)
    ),

    [LOWER] = LAYOUT_split_3x5_2(
	KC_F1,             KC_F2,            KC_F3,          KC_F4,              KC_F5,           KC_PSCR,         XXXXXXX,           XXXXXXX,          KC_ESC,           KC_DEL, 
	KC_F6,             KC_F7,            KC_F8,          KC_F9,              KC_F10,          KC_LEFT,         KC_DOWN,           KC_UP,            KC_RIGHT,         CW_TOGG,
	LSFT_T(KC_F11),    LCTL_T(KC_F12),   KC_LALT,        XXXXXXX,            XXXXXXX,         KC_HOME,         KC_PGDN,           RALT_T(KC_PGUP),  RCTL_T(KC_END),   KC_RSFT,
	                                                     _______,            _______,         KC_LGUI,         _______
    ),

    [RAISE] = LAYOUT_split_3x5_2(
	KC_0,              KC_1,             KC_2,           KC_3,               KC_AMPR,         KC_BSLS,         KC_AT,             KC_ASTR,          KC_CIRC,          KC_DLR, 
	KC_PERC,           KC_4,             KC_5,           KC_6,               KC_PIPE,         KC_TILD,         KC_EQL,            KC_MINS,          KC_PLUS,          KC_GRV,
	KC_HASH,           LCTL_T(KC_7),     LALT_T(KC_8),   KC_9,               KC_EXLM,         XXXXXXX,         KC_UNDS,           KC_RALT,          KC_RCTL,          KC_RSFT,
	                                                     _______,            _______,         _______,         _______
    ),

    [ADJUST] = LAYOUT_split_3x5_2(
	XXXXXXX,           XXXXXXX,          KC_BRIU,        KC_BRID,            XXXXXXX,         QK_BOOT,         XXXXXXX,           XXXXXXX,          XXXXXXX,          XXXXXXX, 
	XXXXXXX,           KC_MUTE,          KC_VOLU,        KC_VOLD,            XXXXXXX,         QK_RBT,          XXXXXXX,           XXXXXXX,          XXXXXXX,          XXXXXXX,
	XXXXXXX,           XXXXXXX,          XXXXXXX,        XXXXXXX,            XXXXXXX,         XXXXXXX,         XXXXXXX,           XXXXXXX,          XXXXXXX,          XXXXXXX,
	                                                     _______,            _______,         _______,         _______
    )
};

// Tri Layer
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, LOWER, RAISE, ADJUST);
};

// Custom Tap Hold Config
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
	case RSFT_T(KC_Z):
	case LSFT_T(KC_SEMICOLON):
	case LT(LOWER, KC_ENT):
	case LT(RAISE, KC_TAB):
	    return true;
	default:
	    return false;
    }
};

// Combos
enum combos {
    GC_LBRC,
    CR_RBRC,
    HT_LPRN,
    TN_RPRN,
    MW_SLSH
};

const uint16_t PROGMEM gc_combo[] = {KC_G, KC_C, COMBO_END};
const uint16_t PROGMEM cr_combo[] = {KC_C, KC_R, COMBO_END};
const uint16_t PROGMEM ht_combo[] = {KC_H, KC_T, COMBO_END};
const uint16_t PROGMEM tn_combo[] = {KC_T, KC_N, COMBO_END};
const uint16_t PROGMEM mw_combo[] = {KC_M, RALT_T(KC_W), COMBO_END};

combo_t key_combos[] = {
    [GC_LBRC] = COMBO(gc_combo, KC_LBRC),
    [CR_RBRC] = COMBO(cr_combo, KC_RBRC),
    [HT_LPRN] = COMBO(ht_combo, KC_LPRN),
    [TN_RPRN] = COMBO(tn_combo, KC_RPRN),
    [MW_SLSH] = COMBO(mw_combo, KC_SLSH)
};

// Custom Combo Term
uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    switch (index) {
	case MW_SLSH:
	    return 20;
    }
    return COMBO_TERM;
};

