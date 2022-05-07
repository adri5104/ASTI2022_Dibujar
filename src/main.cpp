/* Codigo para la prueba de dibujar del 
Asti Challenge 2022.

Equipo SkyRumba

Author: Adrian
Created: 2022-05-04

Creditos a Jaime Bravo Algaba
*/

// ################# Includes ########################

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
Encoder_p encoderL = Encoder_p(PIN_ENCODER_I_CA, PIN_ENCODER_I_CB , 0.142857);
Encoder_p encoderR = Encoder_p(PIN_ENCODER_D_CA, PIN_ENCODER_D_CB , 0.142857);

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
  delay(1000);
  display_printLogo();
  
  // Configuracion de interrupciones
  attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_D_CA), header_encoderR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_I_CA), header_encoderL, CHANGE);
  

  // Set de los Gains del PID
  control.setGains(kp, ki, kd);
  
  //display_printLogo();
  delay(1500);
  display.clearDisplay();
}

void loop() {
  
#ifdef PID_TUNING
  control.resetEncoders();
  control.setPosition(90, 90);
  delay(1000);

  control.resetEncoders();
  control.setPosition(-90, -90);
  delay(1000);
#endif

#ifdef TEST

  control.girar(90);


  /*
  control.resetEncoders();
  control.girar(90);
  delay(500);	
  control.girar(0);
  delay(500);
  control.girar(-90);
  delay(500);
  control.girar(0);
  delay(500);

  control.resetEncoders();
  control.avanzarDistancia(100);
  delay(500);
  control.avanzarDistancia(0);
  delay(500);
  */
#endif

#ifdef CUADRADO



  display_printLine("CUADRADO");
  delay(1000);
  display.clearDisplay();


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
  control.girar(90);
  control.resetEncoders();
  delay(200);
  control.avanzarDistancia(L_CUADRADO);
  control.resetEncoders();

  for(;;)
  {
    display_printLine("FIN CUADRADO");
  }

#endif

#ifdef TRIANGULO

display_printLine("TRIANGULO");
delay(1000);
display.clearDisplay();

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
  {
    display_printLine("FIN TRIANGULO");
  }

#endif

#ifdef RECTANGULO

display_printLine("RECTANGULO");
delay(1000);
display.clearDisplay();

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
  {
    display_printLine("FIN RECTANGULO");
  }

#endif

#ifdef PRINT_POSITION


float pos1 = control.getPos(RIGHT);
float pos2 = control.getPos(LEFT);

int vel1 = control.getVelD();
int vel2 = control.getVelI();


display.clearDisplay();
display.setCursor(0,0);
display.setTextColor(SSD1306_WHITE);
display.setTextSize(1);
display.print("P_right: ");
display.print(pos1);
display.print("P_left: ");
display.print(pos2);
display.print(" V_right: ");
display.print(vel1);
display.print(" V_left: ");
display.print(vel2);

display.display();

Serial.println(pos1);
Serial.println(pos2);


#endif

}