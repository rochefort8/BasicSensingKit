
#include "Sensors.h"

#define DHT_DATA_PIN   (1)
static DHT dht(DHT_DATA_PIN, DHT11);

extern DS323x_Rtc rtc ;
extern BT_HC05 bt ;

static int readHumidityAndTemperature(float *p_humidity, float *p_temperature) ;

void Sensors::begin(void) 
{
  dht.begin();
  bh1750.begin() ;
}

int Sensors::read(void) 
{

  int ret ;

  this->m_available = false ;

  do {

    float humidity, temperature ;
    sensing_data_t *p_table = &data_table[N_SENSING_DATA - m_repeat] ;

    ret = readHumidityAndTemperature (&humidity, &temperature) ;
    if (!ret) {
      Serial.println("readHumidityAndTemperature failed.") ;
      break ;
    }

    p_table->humidity = humidity ;
    p_table->temperature = temperature ;
  
    //
    uint16_t lx ;
    bh1750.read(&lx) ;  
    if (!ret) {
      Serial.println("bh1750.read failed.") ;
    }
  
    p_table->lx = lx ;

    int buf_size = 60;

    char buf_h[buf_size];
    char buf_t[buf_size];

    snprintf(buf_h, buf_size, "Humidity: %.1f / Temperature: %.1f / LX: %d", 
        p_table->humidity,
        p_table->temperature,
        p_table->lx
      );
    Serial.println(buf_h) ;

    if (m_repeat > 0) {
      m_repeat-- ;
    } 
    if (m_repeat == 0) {
      float humidity_ave = 0.0f,temperature_ave = 0.0f ;
      uint16_t lx_ave = 0 ;
      p_table = &data_table[0] ;

      for (int i = 0;i < N_SENSING_DATA;i++) {
        humidity_ave += p_table->humidity ;
        temperature_ave += p_table->temperature ;
        lx_ave += p_table->lx ;
        p_table++ ;
      }
      humidity_ave /= N_SENSING_DATA ;
      temperature_ave /= N_SENSING_DATA ;
      lx_ave /= N_SENSING_DATA ;

      DateTime now = rtc.get();
      String s = now.timestamp() ;

      snprintf(buf_h, buf_size, "%s/H:%.1f/T:%.1f/L:%d", 
          s.c_str(),
          humidity_ave,
          temperature_ave,
          lx_ave
        );
      Serial.println(buf_h) ;
      bt.write(buf_h);

    }
  } while (false) ;

  return false ;
}

int Sensors::save(void) 
{

}

void Sensors::timer(int count) 
{
  int buf_size=40 ;
  char buf_t[buf_size];

  if (m_repeat > 0) {
    this->m_available = true ;
  } 
  if (m_sensing_interval > 0) {
    m_sensing_interval-- ;
  } 
  if (m_sensing_interval == 0) {
    m_repeat = N_SENSING_DATA ;
    m_sensing_interval = SENSING_INTERVAL_SECONDS ;
    this->m_available = true ;
  } 
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
  return true ;

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