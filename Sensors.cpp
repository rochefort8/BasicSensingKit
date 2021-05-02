
#include "Sensors.h"

#define DHT_DATA_PIN   (1)
DHT dht(DHT_DATA_PIN, DHT11);

BH1750 bh1750 ;

static int readHumidityAndTemperature(float *p_humidity, float *p_temperature) ;

void Sensors::begin(void) 
{
  dht.begin();
  bh1750.begin() ;
}

int Sensors::read(void) 
{
  float humidity, temperature ;
  int ret ;

  ret = readHumidityAndTemperature (&humidity, &temperature) ;
  if (!ret) {

  }
  int buf_size = 40;
  
  char buf_h[buf_size];
  char buf_t[buf_size];

  snprintf(buf_h, buf_size, "Humidity: %.1f", humidity);
  snprintf(buf_t, buf_size, "Temperature: %.1f", temperature);  

  Serial.println(buf_h);
  Serial.println(buf_t);    

  //
  uint16_t lx ;
  bh1750.read(&lx) ;  
  if (!ret) {

  }
  Serial.print(lx,DEC); //val十进制输出
  Serial.println("[lx]");
}

int Sensors::save(void) 
{

}


static int readHumidityAndTemperature(float *p_humidity, float *p_temperature)
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (!p_humidity || !p_temperature) {
    return false;
  }
  if (isnan(h) || isnan(t)) {
//    Serial.println("Failed...");
    return false;
  }
  *p_humidity = h ;
  *p_temperature = t ;
  return 0 ;

#if 0
  int buf_size = 40;
  
  char buf_h[buf_size];
  char buf_t[buf_size];

  snprintf(buf_h, buf_size, "Humidity: %.1f", h);
  snprintf(buf_t, buf_size, "Temperature: %.1f", t);  

  Serial.println(buf_h);
  Serial.println(buf_t);  
#endif  
}