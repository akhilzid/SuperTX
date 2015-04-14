void Menu() {
  SWStep();
  if (  menu_redraw_required != 0 ) {
    u8g.firstPage();
    do  {
      drawMenu();
    } while ( u8g.nextPage() );
    menu_redraw_required = 0;
  }
  updateMenu();                            // update menu bar
}

void drawMenu(void) {
  uint8_t i, h, p;
  u8g_uint_t w, d;

  u8g.setFont(u8g_font_6x13);
  u8g.setFontRefHeightText();
  u8g.setFontPosTop();

  h = u8g.getFontAscent() - u8g.getFontDescent();
  w = u8g.getWidth();
  for ( i = 0; i < MENU_ITEMS; i++ ) {
    u8g.setDefaultForegroundColor();
    if (menu_current < 5)  p = i;
    else p = i - (menu_current - 5);

    if ( i == menu_current ) {
      u8g.drawBox(0, p * h + 1, w, h);
      u8g.setDefaultBackgroundColor();
    }
    if ((menu_current - 5) <= i) {
      u8g.setPrintPos(10, p * h);
      u8g.print( menu_strings[i]);
    }
  }
}

void updateMenu(void) {
  last_key_code = uiKeyCode;
  switch ( uiKeyCode ) {
    case KEY_NEXT:
      menu_current++;
      if ( menu_current >= MENU_ITEMS )
        menu_current = 0;
      menu_redraw_required = 1;
      break;
    case KEY_PREV:
      if ( menu_current == 0 )
        menu_current = MENU_ITEMS;
      menu_current--;
      menu_redraw_required = 1;
      break;
    case KEY_SELECT:
      if (submenu_current == 0) {
        submenu_current = menu_current + 1;
        switch (menu_current) {
          case 0:
            MENU_ITEMS = SMI_1;
            for (int i = 0; i <  MENU_ITEMS; i++) {
              menu_strings[i] = menu_Sub1[i];
            }
            menu_redraw_required = 1;
            break;
          case 1:
            MENU_ITEMS = CHANNELS;
            for (int i = 0; i <  MENU_ITEMS; i++) {
              menu_strings[i] = "CH " + String (i + 1) + " : " + channels[CH[i]];
            }
            menu_redraw_required = 1;
            break;
          case 2:
            MENU_ITEMS = CHANNELS;
            for (int i = 0; i <   MENU_ITEMS; i++) {
              if (CH_Reversed[i] == 1) {
                menu_strings[i] = "CH " + String (i + 1) + " : "  + channels[CH[i]] + " Yes" ;
              }
              else
              {
                menu_strings[i] = "CH " + String (i + 1) + " : "  + channels[CH[i]] + " No" ;
              }

            }
            break;
          case 3:
            MENU_ITEMS = CHANNELS;
            for (int i = 0; i <   MENU_ITEMS; i++) {
              menu_strings[i] = "CH " + String (i + 1) + " : "  + channels[CH[i]] + " " + CH_EMIN[i] + " " + CH_EMAX[i];
            }
            break;
          case 5:
            MENU_ITEMS = 3;
            menu_strings[0] = "Screen Update: " + String(GapTime);
            menu_strings[1] = "Voltage Div  : " + String(VoltageDiv);
            menu_strings[2] = "Dead Band    : " + String(Deadband);
            break;
        }
        menu_current = 0;
        menu_redraw_required = 1;
      }
      break;
    case KEY_INC:
    case KEY_DEC:
      if  (uiKeyCode == KEY_INC) Serial.print("KEY_INC \t");
      else if  (uiKeyCode == KEY_DEC) Serial.print("KEY_DEC \t");

      Serial.println(String(submenu_current) + "\t" + String(menu_current));
      if (submenu_current != 0)
      {
        //submenu_current = menu_current + 1;
        switch (submenu_current) {
          case 2:
            if  (uiKeyCode == KEY_INC) CH[menu_current]++;
            else if  (uiKeyCode == KEY_DEC) CH[menu_current]--;
            if ( CHNUM <= CH[menu_current] )
            {
              CH[menu_current] = 0;
            };
            setData();
            for (int i = 0; i <   MENU_ITEMS; i++) {
              menu_strings[i] = "CH " + String (i + 1) + " : "  + channels[CH[i]];
            }
            break;
          case 3:
            if ( CH_Reversed[menu_current] == 0 ) CH_Reversed[menu_current] = 1;
            else CH_Reversed[menu_current] = 0;
            setData();
            for (int i = 0; i <   MENU_ITEMS; i++) {
              if (CH_Reversed[i] == 1) {
                menu_strings[i] = "CH " + String (i + 1) + " : "  + channels[CH[i]] + " Yes" ;
              }
              else
              {
                menu_strings[i] = "CH " + String (i + 1) + " : "  + channels[CH[i]] + " No" ;
              }

            }
            break;
          case 4:
            if (StickVal[2] < 250) {
              if  (uiKeyCode == KEY_INC) CH_EMIN[menu_current] += 10;
              else if  (uiKeyCode == KEY_DEC) CH_EMIN[menu_current] -= 10;
            }
            else if (StickVal[2] > 750) {
              if  (uiKeyCode == KEY_INC) CH_EMAX[menu_current] += 10;
              else if  (uiKeyCode == KEY_DEC) CH_EMAX[menu_current] -= 10;
            }
            SaveEP();
            for (int i = 0; i <   MENU_ITEMS; i++) {
              menu_strings[i] = "CH " + String (i + 1) + " : "  + channels[CH[i]] + " " + CH_EMIN[i] + " " + CH_EMAX[i];
            }
            break;
          case 6:
            if (menu_current == 0) {
              if  (uiKeyCode == KEY_INC) GapTime++;
              else if  (uiKeyCode == KEY_DEC) GapTime--;
              eeprom_write_int(CHANNELS * 9 + 2, constrain(GapTime, 0, 125));
              menu_strings[0] = "Screen Update: " + String(GapTime);
            } else if (menu_current == 1) {
              if  (uiKeyCode == KEY_INC) VoltageDiv++;
              else if  (uiKeyCode == KEY_DEC) VoltageDiv--;
              eeprom_write_int(CHANNELS * 9 + 3, VoltageDiv);
              menu_strings[1] = "Voltage Div  : " + String(VoltageDiv);
            } else if (menu_current == 2) {
              if  (uiKeyCode == KEY_INC) Deadband++;
              else if  (uiKeyCode == KEY_DEC) Deadband--;
              eeprom_write_int(CHANNELS * 9 + 4, constrain(Deadband, 0, 15));
              menu_strings[2] = "Dead Band    : " + String(Deadband);
            }
            break;
        }
        menu_redraw_required = 1;
      }
      break;
    case KEY_BACK:
      if (submenu_current > 0) {
        menu_current = submenu_current - 1;
        submenu_current = 0;
        MENU_ITEMS = MAIN_MENU;
        for (int i = 0; i <  MENU_ITEMS; i++) {
          menu_strings[i] = menu_Main[i];
        }
        menu_redraw_required = 1;
      }
      break;
  }
}
