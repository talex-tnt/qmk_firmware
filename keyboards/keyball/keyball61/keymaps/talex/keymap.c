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

enum custom_keycodes {
	GUI_TAB = SAFE_RANGE,
    CTRL_TAB,
	// other custom keycodes...
};

enum {
    MAC_BASE_LAYER = 0,
    MAC_MOD_LAYER = 1,
    MAC_FN_LAYER = 2
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [MAC_BASE_LAYER] = LAYOUT_universal(
    KC_ESC   , KC_1     , KC_2     , KC_3               , KC_4     , KC_5                                            , KC_6     , KC_7     , KC_8     , KC_9     , KC_0     , KC_BSPC ,
    KC_TAB   , KC_Q     , KC_W     , KC_E               , KC_R     , KC_T                                            , KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_BSLS ,
    KC_DEL   , KC_A     , KC_S     , KC_D               , KC_F     , KC_G                                            , KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , KC_ENT  ,
    KC_LSFT  , KC_Z     , KC_X     , KC_C               , KC_V     , KC_B              , KC_BTN1           , _______ , KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , KC_RSFT ,
    KC_LGUI  , KC_LCTL  , KC_LALT  , MO(MAC_FN_LAYER)   , _______  , MO(MAC_MOD_LAYER) , _______           , _______ , KC_SPC   , _______  , _______  , _______  , KC_RALT  , KC_RGUI
  ),

  [MAC_MOD_LAYER] = LAYOUT_universal(
    KC_GRAVE , KC_F1    , KC_F2     , KC_F3             , KC_F4    , KC_F5                                            , KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , KC_DEL  ,
    _______  , KC_F11   , KC_F12    , CTRL_TAB          , _______  , _______                                          , KC_PGUP  , KC_HOME  , KC_UP    , KC_END   , KC_LBRC  , KC_RBRC ,
    _______  , KC_CAPS  , _______   , GUI_TAB           , _______  , _______                                          , KC_PGDN  , KC_LEFT  , KC_DOWN  , KC_RGHT  , KC_BSPC  , KC_COMM ,
    _______  , _______  , _______   , _______           , _______  , _______           , KC_BTN2           , _______  , _______  , _______  , _______  , _______  , _______  , _______ ,
    _______  , _______  , _______   , _______           , _______  , _______           , _______           , _______  , _______  , _______  , _______  , _______  , _______  , _______
  ),

  [MAC_FN_LAYER] = LAYOUT_universal(
    RGB_TOG  , AML_TO   , AML_I50  , AML_D50  , _______  , _______  ,                                  RGB_M_P  , RGB_M_B  , RGB_M_R  , RGB_M_SW , RGB_M_SN , RGB_M_K  ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , _______  , _______  ,                                  RGB_M_X  , RGB_M_G  , RGB_M_T  , RGB_M_TW , _______  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , _______  , _______  ,                                  CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , KBC_SAVE , KBC_RST  ,
    _______  , _______  , SCRL_DVD , SCRL_DVI , SCRL_MO  , SCRL_TO  , EE_CLR   ,            EE_CLR   , KC_HOME  , KC_PGDN  , KC_PGUP  , KC_END   , _______  , _______  ,
    QK_BOOT  , _______  , _______  , _______  , _______  , _______  , _______  ,            _______  , KC_BSPC  , _______  , _______  , _______  , _______  , QK_BOOT
  )

};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is MAC_MOD_LAYER
    keyball_set_scroll_mode(get_highest_layer(state) == MAC_MOD_LAYER);
    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif



bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case GUI_TAB:
			if (record->event.pressed) {
				register_mods(MOD_BIT(KC_LGUI));
				register_code(KC_TAB);
			} else {
				unregister_code(KC_TAB);
				unregister_mods(MOD_BIT(KC_LGUI));
			}
			return false; // skip default processing
        case CTRL_TAB:
			if (record->event.pressed) {
				register_mods(MOD_BIT(KC_LCTL));
				register_code(KC_TAB);
			} else {
				unregister_code(KC_TAB);
				unregister_mods(MOD_BIT(KC_LCTL));
			}
			return false; // Skip further processing
	}
	return true;
}
