#include QMK_KEYBOARD_H

#if defined(__has_include) && __has_include("snippets.h")
    #include "snippets.h"
#endif


enum alt_keycodes {
    U_T_AUTO = SAFE_RANGE, //USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR,              //USB Toggle Automatic GCR control
    DBG_TOG,               //DEBUG Toggle On / Off
    DBG_MTRX,              //DEBUG Toggle Matrix Prints
    DBG_KBD,               //DEBUG Toggle Keyboard Prints
    DBG_MOU,               //DEBUG Toggle Mouse Prints
    MD_BOOT,               //Restart into bootloader after hold timeout
    // begin my additions
    NUM_TGL // Toggle whether NUM_ENT closes layer
};

keymap_config_t keymap_config;

enum alt_layers {
    _QWERTY,
    _FUNC,
    _NUM,
};
enum alt_keys {
    _KEY_ESC, _KEY_1, _KEY_2, _KEY_3, _KEY_4, _KEY_5, _KEY_6, _KEY_7, _KEY_8, _KEY_9, _KEY_0, _KEY_MINS, _KEY_EQL, _KEY_BSPC, _KEY_DEL, 
    _KEY_TAB, _KEY_Q, _KEY_W, _KEY_E, _KEY_R, _KEY_T, _KEY_Y, _KEY_U, _KEY_I, _KEY_O, _KEY_P, _KEY_LBRC, _KEY_RBRC, _KEY_BSLS, _KEY_HOME, 
    _KEY_CAPS, _KEY_A, _KEY_S, _KEY_D, _KEY_F, _KEY_G, _KEY_H, _KEY_J, _KEY_K, _KEY_L, _KEY_SCLN, _KEY_QUOT, _KEY_ENT, _KEY_PGUP, 
    _KEY_LSFT, _KEY_Z, _KEY_X, _KEY_C, _KEY_V, _KEY_B, _KEY_N, _KEY_M, _KEY_COMM, _KEY_DOT, _KEY_SLSH, _KEY_RSFT, _KEY_UP, _KEY_PGDN, 
    _KEY_LCTL, _KEY_LALT, _KEY_LGUI, _KEY_SPC, _KEY_RGUI, _KEY_FN, _KEY_LEFT, _KEY_DOWN, _KEY_RIGHT, 
};

int row_col_to_i(int row, int col){
    if(row == 0 || row == 1 || row == 2){
        return col + row * MATRIX_COLS;
    } else if (row == 3){
        return col + MATRIX_COLS * 3 - 1;
    } else if (row == 4){
        return col + MATRIX_COLS * 4 - 2;
    } 
    return -1;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_65_ansi_blocker(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,  \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME, \
        KC_ESC , KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP, \
        KC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC,          KC_UP,   KC_PGDN, \
        KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                             KC_RGUI, MO(_FUNC),KC_LEFT,KC_DOWN, KC_RGHT  \
    ),
    [_FUNC] = LAYOUT_65_ansi_blocker(
        _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, KC_F12,  _______, KC_MUTE, \
        _______, _______, _______, _______, RGB_TOG, RGB_VAI, _______, U_T_AUTO,U_T_AGCR,_______, _______, KC_SLCK, KC_PAUS, _______, KC_END,  \
        KC_CAPS, _______, _______, _______, _______, RGB_VAD, _______, _______, _______, _______, _______, _______,          _______, KC_VOLU, \
        _______, _______, _______, _______, _______, MD_BOOT, NK_TOGG, DBG_TOG,TG(_NUM), _______, _______, _______,          _______, KC_VOLD, \
        _______, _______, _______,                            _______,                            _______, _______, KC_MRWD, KC_MPLY, KC_MFFD  \
    ),
    [_NUM] = LAYOUT(
        TG(_NUM),_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, KC_7,    KC_8,    KC_9,    _______, _______, _______, _______, _______, _______, \
        TG(_NUM),_______, _______, _______, _______, _______, KC_4,    KC_5,    KC_6,    _______, _______, _______,          KC_ENT,  _______, \
        _______, _______, _______, _______, _______, _______, KC_1,    KC_2,    KC_3,    _______, _______, NUM_TGL,          _______, _______, \
        _______, _______, _______,                            KC_0,                               _______, _______, _______, _______, _______  \
    ),
    /*
    [X] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______  \
    ),
    */
};

typedef union {
    uint32_t raw;
    struct {
        bool rgb_layer_change : 1;
    };
} user_config_t;

user_config_t user_config;
typedef struct {
    bool ent_leaves_num;
} temp_user_config_t;
temp_user_config_t temp_user_config;
void keyboard_post_init_user(void) {
  // Call the keymap level matrix init.

  // Read the user config from EEPROM
    user_config.raw = eeconfig_read_user();
  
    rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER);
    rgb_matrix_sethsv(HSV_WHITE);

  //init temp user config
  temp_user_config.ent_leaves_num = true;
}


// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
};

#define MODS_SHIFT  (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))
#define MODS_CTRL  (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTRL))
#define MODS_ALT  (get_mods() & MOD_BIT(KC_LALT) || get_mods() & MOD_BIT(KC_RALT))

void cycle_colors(void) {
    if (user_config.rgb_layer_change) {
        rgb_matrix_sethsv(HSV_PURPLE);
    } else {
        rgb_matrix_sethsv(HSV_BLUE);
    }
    user_config.rgb_layer_change = !user_config.rgb_layer_change;
    eeconfig_update_user(user_config.raw);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {
        case U_T_AUTO:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_extra_manual, "USB extra port manual mode");
            }
            return false;
        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            }
            return false;
        case DBG_TOG:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
            }
            return false;
        case DBG_MTRX:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
            }
            return false;
        case DBG_KBD:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
            }
            return false;
        case DBG_MOU:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
            }
            return false;
        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;
        // begin my additions
        case KC_ENT:
            if (record->event.pressed && get_highest_layer(layer_state) == _NUM && temp_user_config.ent_leaves_num){ 
                layer_off(_NUM);
            }
            return true;
        case NUM_TGL: 
            if(record->event.pressed){
                temp_user_config.ent_leaves_num = !temp_user_config.ent_leaves_num ;
            }
        case RGB_TOG:
            if (record->event.pressed) {
                if(rgb_matrix_config.hsv.v == 0){
                    rgb_matrix_sethsv(rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, 0xFF);
                } else {
                    rgb_matrix_sethsv(rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, 0);
                }
            }
            return false;
        #ifdef SNIPPET_1
        case KC_F2:
            if (MODS_SHIFT){
                if(record->event.pressed){
                    uint8_t mods = get_mods();
                    clear_mods();
                    SEND_STRING(SNIPPET_1);
                    set_mods(mods);
                    return false;
                }
            }
        #endif
        #ifdef SNIPPET_2
        case KC_F3:
            if (MODS_SHIFT){
                if(record->event.pressed){
                    uint8_t mods = get_mods();
                    clear_mods();
                    SEND_STRING(SNIPPET_2);
                    set_mods(mods);
                    return false;
                }
            }
        #endif
        default:
            return true; //Process all other keycodes normally
    }
}
void rgb_matrix_set_color_array(int keys[], size_t len, uint8_t red, uint8_t green, uint8_t blue){
    for(int i = 0; i < len; i++){
        rgb_matrix_set_color(keys[i], red, green, blue);
    }
}
void rgb_matrix_indicators_user(void) {
    // uint8_t this_led = host_keyboard_leds();
    if (!g_suspend_state && rgb_matrix_config.enable) {
        switch (get_highest_layer(layer_state)) {
            case _QWERTY: 
                break;
            case _FUNC:
                rgb_matrix_set_color_all(0,0,0);
                for(int i = _KEY_1; i <= _KEY_EQL; i++){
                    rgb_matrix_set_color(i, RGB_BLUE);
                }
                rgb_matrix_set_color(_KEY_COMM, RGB_GREEN);
                rgb_matrix_set_color(_KEY_LBRC, RGB_WHITE);
                rgb_matrix_set_color(_KEY_RBRC, RGB_WHITE);
                rgb_matrix_set_color(_KEY_T, RGB_WHITE);
                rgb_matrix_set_color(_KEY_G, RGB_WHITE);
                int media[] = {_KEY_PGUP, _KEY_PGDN, _KEY_DEL, _KEY_LEFT, _KEY_DOWN, _KEY_RIGHT};
                rgb_matrix_set_color_array(media, sizeof(media)/sizeof(media[0]), RGB_RED);
                HSV tog_hsv = {.h = 0, .s = 0, .v = (0xFF/2 + rgb_matrix_config.hsv.v/2)};
                RGB tog_rgb = hsv_to_rgb(tog_hsv);
                rgb_matrix_set_color(_KEY_R, tog_rgb.r, tog_rgb.g, tog_rgb.b);
                rgb_matrix_set_color(_KEY_B, RGB_YELLOW);
                break;
            case _NUM: {
                rgb_matrix_set_color_all(0,0,0);
                int keys[] = {_KEY_Y, _KEY_U, _KEY_I, _KEY_H ,_KEY_J, _KEY_K, _KEY_N,_KEY_M,_KEY_COMM,_KEY_SPC,_KEY_CAPS, _KEY_ESC, _KEY_RSFT};
                rgb_matrix_set_color_array(keys, sizeof(keys)/sizeof(keys[0]), RGB_GREEN);
                if(temp_user_config.ent_leaves_num){
                    rgb_matrix_set_color(_KEY_ENT, RGB_GREEN);
                }
                break;
            }   
        }
    }
}