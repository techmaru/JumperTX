/*
 * Authors (alphabetical order)
 * - Andre Bernet <bernet.andre@gmail.com>
 * - Andreas Weitl
 * - Bertrand Songis <bsongis@gmail.com>
 * - Bryan J. Rentoul (Gruvin) <gruvin@gmail.com>
 * - Cameron Weeks <th9xer@gmail.com>
 * - Erez Raviv
 * - Gabriel Birkus
 * - Jean-Pierre Parisy
 * - Karl Szmutny
 * - Michael Blandford
 * - Michal Hlavinka
 * - Pat Mackenzie
 * - Philip Moss
 * - Rob Thomson
 * - Thomas Husterer
 *
 * opentx is based on code named
 * gruvin9x by Bryan J. Rentoul: http://code.google.com/p/gruvin9x/,
 * er9x by Erez Raviv: http://code.google.com/p/er9x/,
 * and the original (and ongoing) project by
 * Thomas Husterer, th9x: http://code.google.com/p/th9x/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include "../../opentx.h"

enum menuModelHeliItems {
  ITEM_HELI_SWASHTYPE,
  ITEM_HELI_ELESOURCE,
  ITEM_HELI_AILSOURCE,
  ITEM_HELI_COLSOURCE,
  ITEM_HELI_SWASHRING,
  ITEM_HELI_ELEDIRECTION,
  ITEM_HELI_AILDIRECTION,
  ITEM_HELI_COLDIRECTION,
  ITEM_HELI_MAX
};

#define HELI_PARAM_OFS (23*FW)

void menuModelHeli(uint8_t event)
{
  SIMPLE_MENU(STR_MENUHELISETUP, menuTabModel, e_Heli, ITEM_HELI_MAX);

  int sub = m_posVert;

  for (unsigned int i=0; i<NUM_BODY_LINES; i++) {
    coord_t y = MENU_TITLE_HEIGHT + 1 + i*FH;
    int k = i+s_pgOfs;
    LcdFlags blink = ((s_editMode>0) ? BLINK|INVERS : INVERS);
    LcdFlags attr = (sub == k ? blink : 0);

    switch(k) {
      case ITEM_HELI_SWASHTYPE:
        g_model.swashR.type = selectMenuItem(HELI_PARAM_OFS, y, STR_SWASHTYPE, STR_VSWASHTYPE, g_model.swashR.type, 0, SWASH_TYPE_MAX, attr, event);
        break;

      case ITEM_HELI_ELESOURCE:
        lcd_putsLeft(y, STR_ELEVATOR_SOURCE);
        if (attr) CHECK_INCDEC_MODELSOURCE(event, g_model.swashR.elevatorSource, 0, MIXSRC_LAST_CH);
        putsMixerSource(HELI_PARAM_OFS, y, g_model.swashR.elevatorSource, attr);
        break;

      case ITEM_HELI_AILSOURCE:
        lcd_putsLeft(y, STR_AILERON_SOURCE);
        if (attr) CHECK_INCDEC_MODELSOURCE(event, g_model.swashR.aileronSource, 0, MIXSRC_LAST_CH);
        putsMixerSource(HELI_PARAM_OFS, y, g_model.swashR.aileronSource, attr);
        break;

      case ITEM_HELI_COLSOURCE:
        lcd_putsLeft(y, STR_COLLECTIVE_SOURCE);
        if (attr) CHECK_INCDEC_MODELSOURCE(event, g_model.swashR.collectiveSource, 0, MIXSRC_LAST_CH);
        putsMixerSource(HELI_PARAM_OFS, y, g_model.swashR.collectiveSource, attr);
        break;

      case ITEM_HELI_SWASHRING:
        lcd_putsLeft(y, STR_SWASHRING);
        lcd_outdezAtt(HELI_PARAM_OFS, y, g_model.swashR.value,  LEFT|attr);
        if (attr) CHECK_INCDEC_MODELVAR_ZERO(event, g_model.swashR.value, 100);
        break;

      case ITEM_HELI_ELEDIRECTION:
        g_model.swashR.invertELE = selectMenuItem(HELI_PARAM_OFS, y, STR_ELEDIRECTION, STR_MMMINV, g_model.swashR.invertELE, 0, 1, attr, event);
        break;

      case ITEM_HELI_AILDIRECTION:
        g_model.swashR.invertAIL = selectMenuItem(HELI_PARAM_OFS, y, STR_AILDIRECTION, STR_MMMINV, g_model.swashR.invertAIL, 0, 1, attr, event);
        break;

      case ITEM_HELI_COLDIRECTION:
        g_model.swashR.invertCOL = selectMenuItem(HELI_PARAM_OFS, y, STR_COLDIRECTION, STR_MMMINV, g_model.swashR.invertCOL, 0, 1, attr, event);
        break;
    }
  }
}
