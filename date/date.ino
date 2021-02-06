#include "date.h"

String getYear(String isoString) {
  String date = getDate(isoString);
  return getValue(date, '-', 0);
}

String getMonth(String isoString) {
  String date = getDate(isoString);
  return getValue(date, '-', 1);
}

String getMonthDay(String isoString) {
  String date = getDate(isoString);
  return getValue(date, '-', 2);
}

String getDate(String isoString) {
  return getValue(isoString, 'T', 0);
}

String getTime(String isoString) {
  return getValue(isoString, 'T', 1);
}

String currentIsoString() {
  String time = get("http://worldtimeapi.org/api/ip.txt");
  String isoString = getValue(getValue(time, '\n', 2), ' ', 1);
  return isoString;
}
