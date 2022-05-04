#ifndef POSITIONCONTROL_H
#define POSITIONCONTROL_H

#include <Arduino.h>
#include "Encoder.h"
#include "Motor.h"

#ifndef RIGHT
    #define RIGHT 1
#endif

#ifndef LEFT
    #define LEFT 0
#endif

//Punto de saturacion para el PID
#ifndef VEL_MAX_ENC
    #define VEL_MAX_ENC 255
#endif

class PositionControl
{
    private:

        //velocidad de los motores
        int vel_d, vel_i; 

        //constantes de control
        double kp, ki, kd; 

        //variables de control
        double input, output, setpoint;

        //Objetos atributos
        Motor* misMotores[2];
        Encoder_p* misEncoders[2];

    public:

        // Constructor con parametros 
        //(Motor de la izquierda, Motor de la derecha, Encoder de la izquierda, Encoder de la derecha, Sensores de distancia)
        PositionControl(Motor*, Motor*, Encoder_p*, Encoder_p*);

        // Inicializa el pid y algunas cosas mas
        void init();

        // Avanza una distancia determinada
        // (metodo bloqueante)
        void avanzarDistancia(float );
        
        // Gira X grados sobre sí mismo
        // (metodo bloqueante)
        float girar(float beta);

        // Setea la posicion de los dos motores independientemente
        void setPosition(float setpoint_l, float setpoint_r);

        // Resetea la posicion relativa de los encoders
        void resetEncoders();
    
        //Para el robot
        void parar();

        // ######### Geters #########

        // Devuelve array de encoders
        Encoder_p*& getEncoders(){return *misEncoders;};

        // Devuelve array de motores
        Motor*& getMotores(){return *misMotores;};

        int getVelI(){return vel_i;};

        int getVelD(){return vel_d;};

        // ######### Seters #########
        void setGains(double kp, double ki, double kd)
        {
            this->kp = kp;
            this->ki = ki;
            this->kd = kd;
        };
};






#endif