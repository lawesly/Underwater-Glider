void monitorSerial_GPS() {
  // Latitude in degrees (double)
  Serial.print("Latitude= ");
  Serial.println(gps.location.lat(), 6);
  // Longitude in degrees (double)
  Serial.print(" Longitude= ");
  Serial.println(gps.location.lng(), 6);

  // Raw date in DDMMYY format (u32)
  Serial.print("Raw date DDMMYY = ");
  Serial.println(gps.date.value());

  // Raw time in HHMMSSCC format (u32)
  Serial.print("Raw time in HHMMSSCC = ");
  Serial.println(gps.time.value());

  // Speed in meters per second (double)
  Serial.print("Speed in m/s = ");
  Serial.println(gps.speed.mps());

  // Course in degrees (double)
 // Serial.print("Course in degrees = ");
 // Serial.println(gps.course.deg());

  // Raw altitude in centimeters (i32)
 // Serial.print("Raw altitude in centimeters = ");
  //Serial.println(gps.altitude.value());
  // Altitude in meters (double)
 // Serial.print("Altitude in meters = ");
 // Serial.println(gps.altitude.meters());

  // Number of satellites in use (u32)
  Serial.print("Number os satellites in use = ");
  Serial.println(gps.satellites.value());

  // Horizontal Dim. of Precision (100ths-i32)
  Serial.print("HDOP = ");
  Serial.println(gps.hdop.value());
}
