// handle PPS interrupt

#include "../../Common.h"

#if TIME_LOCATION_PPS_SENSE == ON

#include "PPS.h"

void ppsIsr() {
  unsigned long t = micros();
  unsigned long oneSecond = t - pps.lastMicros;
  if (oneSecond > 1000000 - PPS_WINDOW_MICROS && oneSecond < 1000000 + PPS_WINDOW_MICROS) {
    pps.averageMicros = (pps.averageMicros*(PPS_SECS_TO_AVERAGE - 1) + oneSecond)/PPS_SECS_TO_AVERAGE;
    pps.synced = true;
  } else pps.synced = false;
  pps.lastMicros = t;
}

void Pps::init() {
  #if SENSE_PPS_PIN != OFF
    pinMode(SENSE_PPS_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(SENSE_PPS_PIN), ppsIsr, RISING);
  #endif
}

Pps pps;

#endif