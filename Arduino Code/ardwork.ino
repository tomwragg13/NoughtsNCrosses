#include <SoftwareSerial.h>
#include <Pixy2.h>

Pixy2 pixy;

SoftwareSerial xbeeserial(0, 1); // RX, TX pins of XBee module
void setup() {
  xbeeserial.begin(9600);
  Serial.begin(9600);
  pixy.init();
}

void loop() {
  pixy.ccc.getBlocks();
  // If there are detected blocks
  if (pixy.ccc.numBlocks)
  {

    for (int i=0; i<pixy.ccc.numBlocks; i++)
    {
      //if block is within these coordindates
      if(pixy.ccc.blocks[i].m_x < 94 && pixy.ccc.blocks[i].m_x > 41 && pixy.ccc.blocks[i].m_y < 160 && pixy.ccc.blocks[i].m_y > 110){
        Serial.write("e");
      }
      if(pixy.ccc.blocks[i].m_x < 170 && pixy.ccc.blocks[i].m_x > 110 && pixy.ccc.blocks[i].m_y < 170 && pixy.ccc.blocks[i].m_y > 110){
        Serial.write("w");
      }  
      if(pixy.ccc.blocks[i].m_x < 245 && pixy.ccc.blocks[i].m_x > 190 && pixy.ccc.blocks[i].m_y < 166 && pixy.ccc.blocks[i].m_y > 110){
        Serial.write("q");
      }   
      if(pixy.ccc.blocks[i].m_x < 191 && pixy.ccc.blocks[i].m_x > 242 && pixy.ccc.blocks[i].m_y < 95 && pixy.ccc.blocks[i].m_y > 52){
        Serial.write("a");
      }    
      if(pixy.ccc.blocks[i].m_x < 173 && pixy.ccc.blocks[i].m_x > 121 && pixy.ccc.blocks[i].m_y < 95 && pixy.ccc.blocks[i].m_y > 52){
        Serial.write("s");
      }   
      if(pixy.ccc.blocks[i].m_x < 105 && pixy.ccc.blocks[i].m_x > 55 && pixy.ccc.blocks[i].m_y < 95 && pixy.ccc.blocks[i].m_y > 52){
        Serial.write("d");
      }        
      if(pixy.ccc.blocks[i].m_x < 115 && pixy.ccc.blocks[i].m_x > 74 && pixy.ccc.blocks[i].m_y < 41 && pixy.ccc.blocks[i].m_y > 12){
        Serial.write("c");
      }    
      if(pixy.ccc.blocks[i].m_x < 172 && pixy.ccc.blocks[i].m_x > 126 && pixy.ccc.blocks[i].m_y < 41 && pixy.ccc.blocks[i].m_y > 12){
        Serial.write("x");
      }
      if(pixy.ccc.blocks[i].m_x < 227 && pixy.ccc.blocks[i].m_x > 186 && pixy.ccc.blocks[i].m_y < 41 && pixy.ccc.blocks[i].m_y > 12){
        Serial.write("z");
      }                               
    }

  }

  if (xbeeserial.available() > 0)
  {
    Serial.println(xbeeserial.read());
  }
  delay(1000);
}