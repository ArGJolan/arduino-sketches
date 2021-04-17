#include "temperature.h"

float get_temperature (int ThermistorPin) {
  // https://sanjit.wtf/Calibrator/webCalibrator.html
  float A = 0.00117219681549321;
  float B = 0.00022863121356163843;
  float C = 1.031456603963255e-7;

  int Vo;
  float R1 = 10000;
  float logR2, R2, T;
  // float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
  float c1 = A, c2 = B, c3 = C;

  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;

  return T;
}