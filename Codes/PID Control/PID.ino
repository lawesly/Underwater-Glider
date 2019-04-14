  double PID(){  
  
    error = readAngle - setpoint;
    //Serial.print("error: ");
    //Serial.println(error);
    //Proporcional
    P = error * kP;
    //Serial.println(P);
    //Integral
    I = I + error * kI;
    //Derivada
    D = (lastAngle - readAngle) * kD;
    lastAngle = readAngle;

    //PID, quando o valor desta equação for 0, a angulação do robô esta "perfeita"
    //Serial.print("PID: ");
    //Serial.println(P+I+D);

 return (P+I+D);

  }
  
