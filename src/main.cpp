#include <Arduino.h>

#include "Config.h"
#include "Encoder.h"
#include "Motor.h"
#include "Pinout.h"
#include "Config.h"
#include "PositionControl.h"
#include "Display.h"


// ################# Objetos globales #################

// Objetos para los dos motores (NO control de posicion)
Motor Motor_derecho(PIN_MOTOR_D_IN1, PIN_MOTOR_D_IN2, PIN_MOTOR_D_PWM, PWM_CH_D, PWM_FREC, PWM_RES);   // Motor derecho
Motor Motor_izquierdo(PIN_MOTOR_I_IN1, PIN_MOTOR_I_IN2, PIN_MOTOR_I_PWM, PWM_CH_I, PWM_FREC, PWM_RES); // Motor izquierdo

// Objetos globales para los dos encoders
Encoder_p encoderL = Encoder_p(PIN_ENCODER_I_CA, PIN_ENCODER_I_CB , 4.0);
Encoder_p encoderR = Encoder_p(PIN_ENCODER_D_CA, PIN_ENCODER_D_CB , 4.0);

// Objetos globales para el control de posicion
PositionControl control( &Motor_derecho, &Motor_izquierdo, &encoderR, &encoderL);

// ############ Callbacks interrupciones encoders ######

void header_encoderL()
{
  encoderL.actualizar_posicion();
}

void header_encoderR()
{
  encoderR.actualizar_posicion();
}


void setup() {
  
  Serial.begin(9600);

  // Inicializaciones
  Motor_derecho.init();
  Motor_izquierdo.init();
  encoderR.init();
  encoderL.init();
  control.init();
  display_config();
  

  // Configuracion de interrupciones
  attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_I_CA), header_encoderL, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_D_CA), header_encoderR, CHANGE);

  // Set de los Gains del PID
  control.setGains(kp, ki, kd);
  display_printLogo();
}

void loop() {
  
#ifdef PID_TUNING
  control.resetEncoder();
  control.setPosition(90, 90);
  delay(1000);

  control.resetEncoder();
  control.setPosition(-90, -90);
  delay(1000);
#endif

#ifdef TEST
  control.resetEncoder();
  control.girar(90);
  delay(500);	
  control.girar(0);
  delay(500);
  control.girar(-90);
  delay(500);
  control.girar(0);
  delay(500);

  control.resetEncoder();
  control.avanzarDistancia(100);
  delay(500);
  control.avanzarDistancia(0);
  delay(500);
#endif

#ifdef CUADRADO

  control.avanzarDistancia(L_CUADRADO);
  control.resetEncoders();
  delay(200);
  control.girar(90);
  control.resetEncoders();
  delay(200);
  control.avanzarDistancia(L_CUADRADO);
  control.resetEncoders();
  delay(200);
  control.girar(90);
  control.resetEncoders();
  delay(200);
  control.avanzarDistancia(L_CUADRADO);
  control.resetEncoders();
  delay(200);	
  control.girar(90);
  control.resetEncoders();
  delay(200);
  control.avanzarDistancia(L_CUADRADO);
  control.resetEncoders();

  for(;;)
  {}

#endif

#ifdef TRIANGULO

control.avanzarDistancia(L_TRIANGULO);
control.resetEncoders();
delay(200);
control.girar(120);
control.resetEncoders();
delay(200);
control.avanzarDistancia(L_TRIANGULO);
control.resetEncoders();
delay(200);
control.girar(120);
control.resetEncoders();
delay(200);
control.avanzarDistancia(L_TRIANGULO);
control.resetEncoders();
delay(200);

  for(;;)
  {}

#endif

#ifdef RECTANGULO
control.resetEncoders();
delay(200);
control.avanzarDistancia(L_RECTANGULO_C);
control.resetEncoders();
delay(200);
control.girar(90);
control.resetEncoders();
delay(200);
control.avanzarDistancia(L_RECTANGULO_L);
control.resetEncoders();
delay(200);
control.girar(90);
control.resetEncoders();
delay(200);
control.avanzarDistancia(L_RECTANGULO_C);
control.resetEncoders();
delay(200);
control.girar(90);
control.resetEncoders();
delay(200);
control.avanzarDistancia(L_RECTANGULO_L);
control.resetEncoders();
delay(200);

  for(;;)
  {}

#endif

#ifdef PRINT_POSITION

display.clearDisplay();
display.setCursor(0,0);
display.setTextColor(SSD1306_WHITE);
display.setTextSize(1);
display.print("M_right: ");
display.print(control.getEncoders()[RIGHT].getPosicionGrados());
display.print(" M_left: ");
display.print(control.getEncoders()[LEFT].getPosicionGrados());
display.display();

#endif

}