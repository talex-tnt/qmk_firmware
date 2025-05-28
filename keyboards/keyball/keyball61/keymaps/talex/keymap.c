/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

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

#include "quantum.h"

#define PERMISSIVE_HOLD
#define TAPPING_FORCE_HOLD

// actual keycode values are here: quantum/keycodes.h
// actual modifier values are here: quantum/modifiers.h

#define SAFE_RANGE_CODE 0b1000000000000000
#define IS_CUSTOM_MOD(keycode) ( \
	((keycode) & 0xF000) == (SAFE_RANGE_CODE & 0xF000) && \
	((((keycode) >> 8) & 0x0F) == (MOD_LGUI & 0x0F) || ((keycode >> 8) & 0x0F) == (MOD_LCTL & 0x0F)) \
)
#define MOD_GUI(kc)  ((SAFE_RANGE_CODE & 0xF000) | ((MOD_LGUI & 0x000F) << 8) | (kc & 0x00FF))
#define MOD_CTRL(kc) ((SAFE_RANGE_CODE & 0xF000) | ((MOD_LCTL & 0x000F) << 8) | (kc & 0x00FF))

// enum custom_keycodes {
//     // Custom modifier keycodes
// 	// other custom keycodes...
// };

enum {
    // os specific layouts
    L_MAC_BASE = 0,
    L_MAC_MOD = 1,

    // general layouts
    L_FUNC = 2,
    L_KEYBALL = 3
};

#define HI_PRECISION_LAYER_KEY MO(L_FUNC)
#define _EMPTY_ XXXXXXX

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [L_MAC_BASE] = LAYOUT_universal(
    KC_ESC   , KC_1     , KC_2              , KC_3           , KC_4        , KC_5                                                              , KC_6     , KC_7           , KC_8     , KC_9           , KC_0     , KC_BSPC ,
    KC_TAB   , KC_Q     , KC_W              , KC_E           , KC_R        , KC_T                                                              , KC_Y     , KC_U           , KC_I     , KC_O           , KC_P     , KC_BSLS ,
    KC_DEL   , KC_A     , KC_S              , KC_D           , KC_F        , KC_G                                                              , KC_H     , KC_J           , KC_K     , KC_L           , KC_SCLN  , KC_ENT  ,
    KC_LSFT  , KC_Z     , KC_X              , KC_C           , KC_V        , KC_B           , KC_BTN1                  , MO(L_KEYBALL)         , KC_N     , KC_M           , KC_COMM  , KC_DOT         , KC_SLSH  , KC_RSFT ,
    KC_LGUI  , KC_LCTL  , KC_LALT           , _EMPTY_        , MO(L_FUNC)  , MO(L_MAC_MOD)  , KC_SPC                   , KC_RCTL              , KC_SPC   , _EMPTY_        , _EMPTY_  , _EMPTY_        , KC_RALT  , KC_RGUI
  ),

  [L_MAC_MOD] = LAYOUT_universal(
    KC_GRAVE , _EMPTY_  , _EMPTY_           , _EMPTY_       , _EMPTY_     , _EMPTY_                                                             , _EMPTY_  , _EMPTY_        , _EMPTY_  , KC_MINUS       , KC_EQUAL , KC_DEL  ,
    _______  , MOD_GUI(KC_Q)  , _EMPTY_     , MOD_CTRL(KC_TAB)      , _EMPTY_     , _EMPTY_                                                             , KC_PGUP  , KC_HOME        , KC_UP    , KC_END         , KC_LBRC  , KC_RBRC ,
    _______  , KC_CAPS  , G(S(KC_QUOT))     , MOD_GUI(KC_TAB)       , G(KC_QUOT)  , _EMPTY_                                                             , KC_PGDN  , KC_LEFT        , KC_DOWN  , KC_RGHT        , KC_QUOT  , KC_ENT  ,
    _______  , _EMPTY_  , KC_BTN2           , KC_BTN3       , KC_BTN1     , _EMPTY_                  , _EMPTY_          , _EMPTY_               , _EMPTY_  , S(C(KC_LEFT))  , _EMPTY_  , S(C(KC_RGHT))  , KC_BSPC  , KC_DEL  ,
    _______  , _______  , _______           , _EMPTY_       , _EMPTY_     , _______                  , _EMPTY_          , _EMPTY_               , _EMPTY_  , _EMPTY_        , _EMPTY_  , _EMPTY_        , _______  , _______
  ),

  [L_FUNC] = LAYOUT_universal(
    _______  , KC_F1    , KC_F2             , KC_F3         , KC_F4       , KC_F5                                                               , KC_F6    , KC_F7          , KC_F8    , KC_F9          , KC_F10   , _______ ,
    _______  , KC_F11   , KC_F12            , _EMPTY_       , _EMPTY_     , _EMPTY_                                                             , _EMPTY_  , _EMPTY_        , _EMPTY_  , _EMPTY_        , _EMPTY_  , _EMPTY_ ,
    _______  , _EMPTY_  , _EMPTY_           , _EMPTY_       , _EMPTY_     , _EMPTY_                                                             , _EMPTY_  , _EMPTY_        , _EMPTY_  , _EMPTY_        , _EMPTY_  , _______ ,
    _______  , _EMPTY_  , KC_BTN2           , KC_BTN3       , KC_BTN1     , _EMPTY_                  , _EMPTY_           , _EMPTY_              , _EMPTY_  , _EMPTY_        , _EMPTY_  , _EMPTY_        , _EMPTY_  , _______ ,
    _______  , _______  , _______           , _EMPTY_       , _______     , _EMPTY_                  , _EMPTY_           , _EMPTY_              , _EMPTY_  , _EMPTY_        , _EMPTY_  , _EMPTY_        , _______  , _______
  ),

  [L_KEYBALL] = LAYOUT_universal(
    RGB_TOG  , RGB_MOD  , _EMPTY_           , RGB_HUI        , RGB_SAI     , RGB_VAI                                                            , SCRL_DVD , SCRL_DVI        , _EMPTY_ , _EMPTY_        , RGB_MOD  , RGB_TOG ,
    _EMPTY_  , RGB_RMOD , _EMPTY_           , RGB_HUD        , RGB_SAD     , RGB_VAD                                                            , SCRL_MO , SCRL_TO          , AML_TO  , _EMPTY_        , RGB_RMOD , _EMPTY_ ,
    _EMPTY_  , _EMPTY_  , _EMPTY_           , _EMPTY_        , _EMPTY_     , _EMPTY_                                                            , CPI_I100  , CPI_I1K        , AML_I50 , _EMPTY_        , _EMPTY_  , _EMPTY_ ,
    _EMPTY_  , _EMPTY_  , _EMPTY_           , _EMPTY_        , _EMPTY_     , _EMPTY_                 , _EMPTY_           , _EMPTY_              , CPI_D1K  , CPI_D100        , AML_D50 , _EMPTY_        , KBC_SAVE , KBC_RST ,
    _EMPTY_  , _EMPTY_  , _EMPTY_           , _EMPTY_        , _EMPTY_     , _EMPTY_                 , _EMPTY_           , _EMPTY_              , _EMPTY_  , _EMPTY_         , _EMPTY_ , _EMPTY_        , EE_CLR   , QK_BOOT
  )

};
// clang-format on

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif


// https://docs.qmk.fm/feature_advanced_keycodes
bool swap_alt_gui(uint16_t keycode, keyrecord_t *record) {
    uint8_t mod_state = get_mods();
	switch (keycode) {
        case KC_DEL:
        case KC_BSPC:
		case KC_LEFT:
		case KC_RIGHT:
		case KC_UP:
		case KC_DOWN: {
			if (record->event.pressed) {
				if (mod_state & MOD_MASK_ALT) {
                    del_mods(MOD_MASK_ALT);
                    add_mods(MOD_MASK_GUI);
					register_code(keycode);
                    set_mods(mod_state);
				} else if (mod_state & MOD_MASK_GUI) {
                    del_mods(MOD_MASK_GUI);
                    add_mods(MOD_MASK_ALT);
					register_code(keycode);
                    set_mods(mod_state);
				} else {
					register_code(keycode);
				}
			} else {
				unregister_code(keycode);
			}
			return false;
		}
	}
	return true;
}

bool swap_ctrl_gui(uint16_t keycode, keyrecord_t *record) {
    uint8_t mod_state = get_mods();
	switch (keycode) {
		case KC_MINUS: {
			if (record->event.pressed) {
				if (mod_state & MOD_MASK_CTRL) {
                    del_mods(MOD_MASK_CTRL);
                    add_mods(MOD_MASK_GUI);
					register_code(keycode);
                    set_mods(mod_state);
				} else if (mod_state & MOD_MASK_GUI) {
                    del_mods(MOD_MASK_GUI);
                    add_mods(MOD_MASK_CTRL);
					register_code(keycode);
                    set_mods(mod_state);
				} else {
					register_code(keycode);
				}
			} else {
				unregister_code(keycode);
			}
			return false;
		}
	}
	return true;
}



// Track active state for cleanup
bool mod_key_active = false;
uint8_t mod_key_mod = 0;

bool handle_alt_gui_tab(uint16_t keycode, keyrecord_t *record) {
	if (IS_CUSTOM_MOD(keycode)) {
		uint8_t mod = (keycode >> 8) & 0x000F;
		uint8_t base_key = keycode & 0x00FF;

        uprintf("keycode = 0x%04X\n", keycode);
        // uprintf("Pressed mod = 0x%02X base = 0x%02X\n", mod, base_key);

        // uprintf("MOD_GUI(KC_TAB) = 0x%04X\n", MOD_GUI(KC_TAB));
        // uprintf("MOD_GUI mod = 0x%02X base = 0x%02X\n", (MOD_GUI(KC_TAB) >> 8) & 0x000F, MOD_GUI(KC_TAB) & 0x00FF);

        // uprintf("MOD_LGUI = 0x%08X\n", MOD_LGUI);
        // uprintf("MOD_BIT(KC_LGUI) = 0x%08X\n", MOD_BIT(KC_LGUI));
        // uprintf("mod = 0x%08X\n", mod);
        // uprintf("MOD_BIT(mod) = 0x%08X\n", MOD_BIT(mod));

		if (record->event.pressed) {
			register_mods(mod);
			register_code(base_key);
			mod_key_active = true;
			mod_key_mod = mod;
		} else {
			unregister_code(base_key); // modifier will be unregistered on layer change
		}
		return false;
	}

	return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
	static layer_state_t previous_layer_state;

	keyball_set_scroll_mode(get_highest_layer(state) == L_MAC_MOD); // Auto enable scroll mode when the highest layer is MAC_MOD_LAYER

	if (mod_key_active) { // Cleanup if we changed layer
		for (uint8_t i = 0; i < 32; i++) {
			bool was_active = (previous_layer_state & (1UL << i)) != 0;
			bool is_active = (state & (1UL << i)) != 0;

			if (was_active && !is_active) {
				unregister_mods(mod_key_mod);
				mod_key_active = false;
				break;
			}
		}
	}
	previous_layer_state = state;
	return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    static uint16_t prev_cpi_value = KEYBALL_CPI_DEFAULT;

    if(!swap_alt_gui(keycode, record)) {
        return false;
    }
    if(!swap_ctrl_gui(keycode, record)) {
        return false;
    }
    if(!handle_alt_gui_tab(keycode, record)) {
        return false;
    }
    switch (keycode) {
        case HI_PRECISION_LAYER_KEY:
        if (record->event.pressed) {
            prev_cpi_value = keyball_get_cpi();
            keyball_set_cpi(500);
        } else {
            keyball_set_cpi(prev_cpi_value);
        }
        break;
    }
    return true;
}
