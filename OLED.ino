void FSmsg(int h, int v, const char* msg) {
  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_unifont);
    u8g.drawStr( h, v, msg );
  } while ( u8g.nextPage() );
};

void CalibVals() {
  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_6x10);
    u8g.drawStr( 0, 22, "Calibration Mode:" );

    //thr up
    u8g.setPrintPos(24, 32);
    u8g.print(StickMax[2]);

    //thr down
    u8g.setPrintPos(24, 55);
    u8g.print(StickMin[2]);

    //rud up
    u8g.setPrintPos(10, 43);
    u8g.print(StickMax[3]);

    //rud down
    u8g.setPrintPos(40, 43);
    u8g.print(StickMin[3]);

    //ele up
    u8g.setPrintPos(80, 32);
    u8g.print(StickMax[1]);

    //ele down
    u8g.setPrintPos(80, 55);
    u8g.print(StickMin[1]);

    //ail up
    u8g.setPrintPos(70, 43);
    u8g.print(StickMax[0]);

    //ail down
    u8g.setPrintPos(100, 43);
    u8g.print(StickMin[0]);
  } while ( u8g.nextPage() );
};


void Screen() {
  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_6x10);

    u8g.setPrintPos(8, 12);
    u8g.print("VRA: " + String(StickVal[4]));
    u8g.setPrintPos(64, 12);
    u8g.print("VRB: " + String(StickVal[5]));
    u8g.setPrintPos(46, 26);
    u8g.print("M:" + String(SWA + SWB));
    u8g.setPrintPos(46, 40);
    u8g.print("V:" + String(average));
    u8g.setPrintPos(46, 54);
    u8g.print("L:" + String(LTIME)); // LTIME

    u8g.drawFrame(4, 17, 37, 37); // Left Stick
    u8g.drawFrame(40, 17, 4, 37); 
    u8g.drawFrame(4, 53, 37, 4); 
    u8g.drawPixel(22, 36);
    u8g.drawPixel(map( 500, 350 , 650, 5, 40), 52);
    u8g.drawPixel(map( StickTRIM[3], 350 , 650, 5, 40), 54);
    u8g.drawPixel(map( StickTRIM[3], 350 , 650, 5, 40), 55);
    u8g.drawCircle(map( StickVal[3], -500 , 500, 5, 40), map( StickVal[2], -500 , 500, 53, 18), 2);
    
    u8g.drawFrame(89, 17, 37, 37); // Right Stick
    u8g.drawFrame(86, 17, 4, 37);
    u8g.drawFrame(89, 53, 37, 4);
    u8g.drawPixel(108, 36);
    u8g.drawPixel(map( 500, 350 , 650, 90, 125), 52);
    u8g.drawPixel(map( StickTRIM[0], 350 , 650, 90, 125), 54);
    u8g.drawPixel(map( StickTRIM[0], 350 , 650, 90, 125), 55);
    u8g.drawCircle(map( StickVal[0], -500 , 500, 90, 125),  map( StickVal[1], -500 , 500, 53, 18), 2);

  } while ( u8g.nextPage() );
};


void ScreenPPM() {
  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_6x10);
    uint8_t h = u8g.getFontAscent() - u8g.getFontDescent();
    
    u8g.setPrintPos(6, h);
    u8g.print("Ch1: " + String(ppm[0]));
    u8g.setPrintPos(66, h);
    u8g.print("Ch2: " + String(ppm[1]));

    u8g.setPrintPos(6, h*2);
    u8g.print("Ch3: " + String(ppm[2]));
    u8g.setPrintPos(66, h*2);
    u8g.print("Ch4: " + String(ppm[3]));

    u8g.setPrintPos(6, h*3);
    u8g.print("Ch5: " + String(ppm[4]));
    u8g.setPrintPos(66, h*3);
    u8g.print("Ch6: " + String(ppm[5]));

    u8g.setPrintPos(6, h*4);
    u8g.print("Ch7: " + String(ppm[6]));
    u8g.setPrintPos(66, h*4);
    u8g.print("Ch8: " + String(ppm[7]));
    
    u8g.setPrintPos(6, h*5);
    u8g.print("Ch9: " + String(ppm[8]));
  
  } while ( u8g.nextPage() );
};


