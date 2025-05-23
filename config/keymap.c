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
	SFT_T(KC_SCLN),    CTL_T(KC_Q),      ALT_T(KC_J),    GUI_T(KC_K),        KC_X,            KC_B,            GUI_T(KC_M),       ALT_T(KC_W),      CTL_T(KC_V),      SFT_T(KC_Z),
	                                                     LT(LOWER, KC_ENT),  KC_SPC,          KC_BSPC,         LT(RAISE, KC_TAB)
    ),

    [LOWER] = LAYOUT_split_3x5_2(
	KC_F1,             KC_F2,            KC_F3,          KC_F4,              KC_F5,           KC_PSCR,         XXXXXXX,           XXXXXXX,          KC_ESC,           KC_DEL, 
	KC_F6,             KC_F7,            KC_F8,          KC_F9,              KC_F10,          KC_LEFT,         KC_DOWN,           KC_UP,            KC_RIGHT,         XXXXXXX,
	KC_F11,            KC_F12,           XXXXXXX,        XXXXXXX,            XXXXXXX,         KC_HOME,         KC_PGDN,           KC_PGUP,          KC_END,           XXXXXXX,
	                                                     _______,            _______,         KC_LGUI,         _______
    ),

    [RAISE] = LAYOUT_split_3x5_2(
	KC_0,              KC_1,             KC_2,           KC_3,               KC_AMPR,         KC_BSLS,         KC_AT,             KC_ASTR,          KC_CIRC,          KC_DLR, 
	KC_PERC,           KC_4,             KC_5,           KC_6,               KC_PIPE,         KC_TILD,         KC_EQL,            KC_MINS,          KC_PLUS,          KC_GRV,
	KC_HASH,           KC_7,             KC_8,           KC_9,               KC_EXLM,         XXXXXXX,         KC_UNDS,           CW_TOGG,          XXXXXXX,          XXXXXXX,
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
	case SFT_T(KC_Z):
	case SFT_T(KC_SEMICOLON):
	case LT(LOWER, KC_ENT):
	case LT(RAISE, KC_TAB):
	    return true;
	default:
	    return false;
    }
};

// Disable quick tap term for layer keys
uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(LOWER, KC_ENT):
        case LT(RAISE, KC_TAB):
            return 0;
        default:
            return QUICK_TAP_TERM;
    }
}

// Send dummy key before release of ALT and GUI
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ALT_T(KC_J):
        case ALT_T(KC_W):
        case GUI_T(KC_K):
        case GUI_T(KC_M):
            if (!record->event.pressed) {
                if (!record->tap.count) {
                    tap_code(KC_F18);
                }
            }
            return true;
        default:
            return true;
    }
}

// Combos
enum combos {
    EU_LPRN,
    HT_RPRN,
    OE_LBRC,
    TN_RBRC,
    DOTCOM_LCBR,
    CR_RCBR,
    MW_SLSH
};

const uint16_t PROGMEM eu_combo[] = {KC_E, KC_U, COMBO_END};
const uint16_t PROGMEM ht_combo[] = {KC_H, KC_T, COMBO_END};
const uint16_t PROGMEM oe_combo[] = {KC_O, KC_E, COMBO_END};
const uint16_t PROGMEM tn_combo[] = {KC_T, KC_N, COMBO_END};
const uint16_t PROGMEM dotcom_combo[] = {KC_DOT, KC_COMM, COMBO_END};
const uint16_t PROGMEM cr_combo[] = {KC_C, KC_R, COMBO_END};
const uint16_t PROGMEM mw_combo[] = {GUI_T(KC_M), ALT_T(KC_W), COMBO_END};

combo_t key_combos[] = {
    [EU_LPRN] = COMBO(eu_combo, KC_LPRN),
    [HT_RPRN] = COMBO(ht_combo, KC_RPRN),
    [OE_LBRC] = COMBO(oe_combo, KC_LBRC),
    [TN_RBRC] = COMBO(tn_combo, KC_RBRC),
    [DOTCOM_LCBR] = COMBO(dotcom_combo, KC_LCBR),
    [CR_RCBR] = COMBO(cr_combo, KC_RCBR),
    [MW_SLSH] = COMBO(mw_combo, KC_SLSH)
};
