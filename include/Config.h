#ifndef CONFIG_H
#define CONFIG_H

// ----------------- Seleccion de prueba -----

#define CUADRADO
//#define TRIANGULO
//#define RECTANGULO
//#define TEST
//#define PID_TUNING

#define PRINT_POSITION

//(mm)
#define L_CUADRADO 200
#define L_TRIANGULO 250
#define L_RECTANGULO_L 100
#define L_RECTANGULO2_C 300

// ----------------- Parametros robot -------

    // Dimensions (mm)
    const float ROBOT_WIDTH = 83.0;
    const float ROBOT_RADIUS = 30.0;

    // Motor ticks por grado
    const float TICKS_PER_DEGREE = 4.0;

// ----------------- Parametros PID -------

    // Parametros PID
    const float kp = 0.5;
    const float ki = 0.0;
    const float kd = 0.0;

    // Velocidad maxima
    #define VEL_MAX_ENC  255.0

// ----------------- Display -----------------

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET     4 
#define SCREEN_ADDRESS 0x3

// ----------------- PWM ---------------------

#define PWM_FREC 5000 //frecuencia de la senal pwm
#define PWM_RES 8// resolucion de la senal pwm. En nuestro caso 8 bits (0 - 255)
#define PWM_CH_D 0 //canal para el pwm del motor derecho 
#define PWM_CH_I 1 //canal para el pwm del motor izquierdo



#endif