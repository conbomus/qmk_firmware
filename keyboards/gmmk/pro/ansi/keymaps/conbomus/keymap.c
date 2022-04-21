/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H


enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
    USR_CPY,
    USR_CUT,
    USR_PST,
    #ifdef ENCODER_ENABLE
    USR_SLCK,
    USR_SINT,
    #endif //ENCODER_ENABLE
};


// RGB led number layout, function of the key

//  67, led 01   0, ESC    6, F1      12, F2      18, F3   23, F4   28, F5      34, F6   39, F7   44, F8      50, F9   56, F10   61, F11    66, F12    69, Prt       Rotary(Mute)   68, led 11
//  70, led 02   1, ~      7, 1       13, 2       19, 3    24, 4    29, 5       35, 6    40, 7    45, 8       51, 9    57, 0     62, -_     78, (=+)   85, BackSpc   72, Home       71, led 12
//  73, led 03   2, Tab    8, Q       14, W       20. E    25, R    30, T       36, Y    41, U    46, I       52, O    58, P     63, [{     89, ]}     93, \|        75, PgUp       74, led 13
//  76, led 04   3, Caps   9, A       15, S       21, D    26, F    31, G       37, H    42, J    47, K       53, L    59, ;:    64, '"                96, Enter     86, PgDn       77, led 14
//  80, led 05   4, Sh_L   10, Z      16, X       22, C    27, V    32, B       38, N    43, M    48, ,<      54, .<   60, /?               90, Sh_R   94, Up        82, End        81, led 15
//  83, led 06   5, Ct_L   11,Win_L   17, Alt_L                     33, SPACE                     49, Alt_R   55, FN             65, Ct_R   95, Left   97, Down      79, Right      84, led 16
//  87, led 07                                                                                                                                                                      88, led 17
//  91, led 08                                                                                                                                                                      92, led 18

#define CAPS_LOCK_LED_COUNT 8
uint8_t CAPS_LOCK_LEDS[CAPS_LOCK_LED_COUNT] = {67, 70, 73, 76, 80, 83, 87, 91};



#ifdef ENCODER_ENABLE

bool ENCODER_SCROLL_ON = false;
bool ENCODER_INTENSITY_MODIFY_ON = false;
uint8_t ENCODER_SCROLL_INTENSITY = 1; //Defaults value to 1.

#define SCROLL_INTENSITY_COUNT 8
uint8_t SCROLL_STATUS_LEDS[SCROLL_INTENSITY_COUNT] = {92, 88, 84, 81, 77, 74, 71, 68};

static void scroll_with_intensity(uint8_t keycode);

#endif //ENCODER_ENABLE

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt           ScrollToggle
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 Copy
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             Home
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right


    // The FN key by default maps to a momentary toggle to layer 1 to provide access to the RESET key (to put the board into bootloader mode). Without
    // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
    // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
    // if that's your preference.
    //
    // To put the keyboard in bootloader mode, use FN+backslash. If you accidentally put it into bootloader, you can just unplug the USB cable and
    // it'll be back to normal when you plug it back in.
    //
    // This keyboard defaults to 6KRO instead of NKRO for compatibility reasons (some KVMs and BIOSes are incompatible with NKRO).
    // Since this is, among other things, a "gaming" keyboard, a key combination to enable NKRO on the fly is provided for convenience.
    // Press Fn+N to toggle between 6KRO and NKRO. This setting is persisted to the EEPROM and thus persists between restarts.
    [0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,          USR_SLCK,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          USR_CPY,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_HOME,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [1] = LAYOUT(
        DEBUG,   KC_MYCM, KC_WHOM, KC_CALC, KC_MSEL, KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______,          USR_SINT,
        _______, RGB_TOG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, RGB_VAI, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET,            USR_CUT,
        _______, _______, RGB_VAD, _______, _______, _______, _______, _______, _______, _______, _______, _______,          QMKBEST,          USR_PST,
        _______,          _______, RGB_HUI, _______, _______, _______, NK_TOGG, _______, _______, _______, _______,          _______, RGB_MOD, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, RGB_SPD, RGB_RMOD, RGB_SPI
    ),


};
// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case QMKBEST:
            if (record->event.pressed){
                SEND_STRING("QMK is pretty darn cool!");
            }
        break;
        
        case USR_CPY:
            if (record->event.pressed){
                SEND_STRING(SS_LCTL("c"));
            }
        break;

        case USR_PST:
            if (record->event.pressed){
                SEND_STRING(SS_LCTL("v"));
            }
        break;

        case USR_CUT:
            if (record->event.pressed){
                SEND_STRING(SS_LCTL("x"));
            }
        break;

        #ifdef ENCODER_ENABLE
        case USR_SLCK:
            if (record->event.pressed){
                ENCODER_SCROLL_ON = !ENCODER_SCROLL_ON;
            }
        break;
        
        case USR_SINT:
            if (record->event.pressed) {
                ENCODER_INTENSITY_MODIFY_ON = !ENCODER_INTENSITY_MODIFY_ON;
            }
        break;

        #endif //ENCODER_ENABLE
    }

    return true;
};


#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    uint8_t mod_state = get_mods();


    if (ENCODER_INTENSITY_MODIFY_ON) {
        if (clockwise) {
            if (ENCODER_SCROLL_INTENSITY <= 2) {
                ENCODER_SCROLL_INTENSITY = 1;
            }
            else {
                ENCODER_SCROLL_INTENSITY = ENCODER_SCROLL_INTENSITY - 1;
            }
        }
        else {
            if (ENCODER_SCROLL_INTENSITY >= (SCROLL_INTENSITY_COUNT - 1)) {
                ENCODER_SCROLL_INTENSITY = SCROLL_INTENSITY_COUNT;
            }
            else {
                ENCODER_SCROLL_INTENSITY = ENCODER_SCROLL_INTENSITY + 1;
            }
        }
    }
    // If we are doing encoder scrolling, then we'll do all the mouse wheel codes.
    else if (ENCODER_SCROLL_ON) {
        if (get_mods() & MOD_MASK_CTRL) {
            unregister_mods(MOD_MASK_CTRL);
            if (clockwise) {
                scroll_with_intensity(KC_MS_WH_RIGHT);
            } else {
                scroll_with_intensity(KC_MS_WH_LEFT);
            }
            set_mods(mod_state);
        }
        else if (clockwise) {
            scroll_with_intensity(KC_MS_WH_DOWN);
        }
        else {
            scroll_with_intensity(KC_MS_WH_UP);
        }
    }
    // If we are not encoder scrolling, then use the arrow key codes.
    else {
        if (get_mods() & MOD_MASK_CTRL) {
            unregister_mods(MOD_MASK_CTRL);
            if (clockwise) {
                tap_code(KC_RGHT);
            }
            else {
                tap_code(KC_LEFT);
            }
            set_mods(mod_state);
        }
        else if (clockwise) {
            tap_code(KC_DOWN);
        }
        else {
            tap_code(KC_UP);
        }
    }

    return true;
}

static void scroll_with_intensity(uint8_t keycode) {
    for (int i = 0; i < ENCODER_SCROLL_INTENSITY; i++) {
        tap_code(keycode);
    }
};

#endif // ENCODER_ENABLE


#ifdef RGB_MATRIX_ENABLE

static void set_rgb_caps_leds_on(void);
static void set_rgb_caps_leds_off(void);

static void set_status_led_on(uint8_t keycode);
static void set_status_led_off(uint8_t keycode);


void rgb_matrix_indicators_user(void) {
    if (host_keyboard_led_state().caps_lock) {
        set_rgb_caps_leds_on();
    }
    else {
        set_rgb_caps_leds_off();
    }

    if (ENCODER_INTENSITY_MODIFY_ON) {
        for (int i = 0; i < ENCODER_SCROLL_INTENSITY && i < SCROLL_INTENSITY_COUNT; i++) {
            set_status_led_on(SCROLL_STATUS_LEDS[i]);
        }
    }
    else if (ENCODER_SCROLL_ON) {
        for (int i = 0; i < SCROLL_INTENSITY_COUNT; i++) {
            set_status_led_on(SCROLL_STATUS_LEDS[i]);
        }
    }
    else {
        for (int i = 0; i < SCROLL_INTENSITY_COUNT; i++) {
            set_status_led_off(SCROLL_STATUS_LEDS[i]);
        }
    }
}



static void set_rgb_caps_leds_on() { 
    for (int i = 0; i < CAPS_LOCK_LED_COUNT; i++) {
        set_status_led_on(CAPS_LOCK_LEDS[i]);
    }
}

static void set_rgb_caps_leds_off() {
    for (int i = 0; i < CAPS_LOCK_LED_COUNT; i++) {
        set_status_led_off(CAPS_LOCK_LEDS[i]);
    }
}

static void set_status_led_on(uint8_t keycode) {
    uint8_t brightness = rgb_matrix_get_val();
    
    // If the brightness is all the way down, turn it up to a nice subtle value.
    if (brightness < 1) {
        brightness = 100;
    }
    rgb_matrix_set_color(keycode, brightness, brightness, brightness);
}
static void set_status_led_off(uint8_t keycode) {
    rgb_matrix_set_color(keycode, 0, 0, 0); 
}

#endif