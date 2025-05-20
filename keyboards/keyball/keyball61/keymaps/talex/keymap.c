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



enum custom_keycodes {
	GUI_TAB = QK_KB_16,
    CTRL_TAB = QK_KB_17,
	// other custom keycodes...
};

enum {
    // os specific layouts
    L_MAC_BASE = 0,
    L_MAC_MOD = 1,

    // general layouts
    L_FUNC = 2,
    L_KEYBALL = 3
};

#define HI_PRECISION_LAYER_KEY MO(L_FUNC)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [L_MAC_BASE] = LAYOUT_universal(
    KC_ESC   , KC_1     , KC_2              , KC_3           , KC_4        , KC_5                                                              , KC_6     , KC_7           , KC_8     , KC_9           , KC_0     , KC_BSPC ,
    KC_TAB   , KC_Q     , KC_W              , KC_E           , KC_R        , KC_T                                                              , KC_Y     , KC_U           , KC_I     , KC_O           , KC_P     , KC_BSLS ,
    KC_DEL   , KC_A     , KC_S              , KC_D           , KC_F        , KC_G                                                              , KC_H     , KC_J           , KC_K     , KC_L           , KC_SCLN  , KC_ENT  ,
    KC_LSFT  , KC_Z     , KC_X              , KC_C           , KC_V        , KC_B           , _______                  , MO(L_KEYBALL)         , KC_N     , KC_M           , KC_COMM  , KC_DOT         , KC_SLSH  , KC_RSFT ,
    KC_LGUI  , KC_LCTL  , KC_LALT           , KC_BTN1        , MO(L_FUNC)  , MO(L_MAC_MOD)  , KC_SPC                   , KC_RCTL              , KC_SPC   , _______        , _______  , _______        , KC_RALT  , KC_RGUI
  ),

  [L_MAC_MOD] = LAYOUT_universal(
    KC_GRAVE , _______  , _______           , _______       , _______     , _______                                                             , _______  , _______        , _______  , KC_MINUS       , KC_EQUAL , KC_DEL  ,
    _______  , _______  , _______           , CTRL_TAB      , _______     , _______                                                             , KC_PGUP  , KC_HOME        , KC_UP    , KC_END         , KC_LBRC  , KC_RBRC ,
    _______  , KC_CAPS  , G(S(KC_QUOT))     , GUI_TAB       , G(KC_QUOT)  , _______                                                             , KC_PGDN  , KC_LEFT        , KC_DOWN  , KC_RGHT        , KC_QUOT  , KC_ENT  ,
    _______  , _______  , KC_BTN2           , KC_BTN3       , KC_BTN1     , _______                  , _______          , _______               , _______  , S(C(KC_LEFT))  , _______  , S(C(KC_RGHT))  , KC_BSPC  , KC_DEL  ,
    _______  , _______  , _______           , _______       , _______     , _______                  , _______          , _______               , _______  , _______        , _______  , _______        , _______  , _______
  ),

  [L_FUNC] = LAYOUT_universal(
    _______  , KC_F1    , KC_F2             , KC_F3         , KC_F4       , KC_F5                                                               , KC_F6    , KC_F7          , KC_F8    , KC_F9          , KC_F10   , _______ ,
    _______  , KC_F11   , KC_F12            , _______       , _______     , _______                                                             , _______  , _______        , _______  , _______        , _______  , _______ ,
    _______  , _______  , _______           , _______       , _______     , _______                                                             , _______  , _______        , _______  , _______        , _______  , _______ ,
    _______  , _______  , KC_BTN2           , KC_BTN3       , KC_BTN1     , _______                  , _______           , _______              , _______  , _______        , _______  , _______        , _______  , _______ ,
    _______  , _______  , _______           , _______       , _______     , _______                  , _______           , _______              , _______  , _______        , _______  , _______        , _______  , _______
  ),

  [L_KEYBALL] = LAYOUT_universal(
    RGB_TOG  , AML_TO   , AML_I50           , AML_D50        , _______     , _______                                                            , RGB_M_P  , RGB_M_B        , RGB_M_R  , RGB_M_SW       , RGB_M_SN , RGB_M_K ,
    RGB_MOD  , RGB_HUI  , RGB_SAI           , RGB_VAI        , _______     , _______                                                            , RGB_M_X  , RGB_M_G        , RGB_M_T  , RGB_M_TW       , _______  , _______ ,
    RGB_RMOD , RGB_HUD  , RGB_SAD           , RGB_VAD        , _______     , _______                                                            , CPI_D1K  , CPI_D100       , CPI_I100 , CPI_I1K        , _______  , _______ ,
    _______  , _______  , SCRL_DVD          , SCRL_DVI       , SCRL_MO     , SCRL_TO                 , _______           , _______              , _______  , _______        , _______  , _______        , KBC_SAVE , KBC_RST ,
    _______  , _______  , _______           , _______        , _______     , _______                 , _______           , _______              , _______  , _______        , _______  , _______        , EE_CLR   , QK_BOOT
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


bool gui_tab_active = false;
bool ctrl_tab_active = false;
bool handle_alt_gui_tab(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case GUI_TAB:
			if (record->event.pressed) {
				register_mods(MOD_BIT(KC_LGUI));
				register_code(KC_TAB);
                gui_tab_active = true;
			} else {
				unregister_code(KC_TAB);
			}
			return false; // skip default processing
        case CTRL_TAB:
			if (record->event.pressed) {
				register_mods(MOD_BIT(KC_LCTL));
				register_code(KC_TAB);
                ctrl_tab_active = true;
			} else {
				unregister_code(KC_TAB);
			}
			return false;
	}
	return true;
}


uint16_t prev_cpi_value = KEYBALL_CPI_DEFAULT;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if(!swap_alt_gui(keycode, record)) {
        return false;
    }
    if(layer_state_is(L_MAC_MOD) && !swap_ctrl_gui(keycode, record)) {
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

layer_state_t previous_layer_state;


layer_state_t layer_state_set_user(layer_state_t state) {

    keyball_set_scroll_mode(get_highest_layer(state) == L_MAC_MOD);  // Auto enable scroll mode when the highest layer is MAC_MOD_LAYER

	if (gui_tab_active || ctrl_tab_active) {
		for (uint8_t i = 0; i < 32; i++) {
			bool was_active = (previous_layer_state & (1UL << i)) != 0;
			bool is_active = (state & (1UL << i)) != 0;

			if (was_active && !is_active) {
				if (gui_tab_active) {
					unregister_mods(MOD_BIT(KC_LGUI));
					gui_tab_active = false;
				}
				if (ctrl_tab_active) {
					unregister_mods(MOD_BIT(KC_LCTL));
					ctrl_tab_active = false;
				}
				break;
			}
		}
	}

	previous_layer_state = state;
	return state;
}
