#include "PositionControl.h"

PositionControl::PositionControl(Motor* motor_d, Motor* motor_i, Encoder_p* encoder_d, Encoder_p* encoder_i)
{
    misMotores[LEFT] = motor_i;
    misMotores[RIGHT] = motor_d;
    misEncoders[LEFT] = encoder_i;
    misEncoders[RIGHT] = encoder_d;
}

void PositionControl::init()
{
    // Inicializacion de las variables de control
    input = 0;
    output = 0;
    setpoint = 0;
    vel_d = 0;
    vel_i = 0;
    kp = 0.5;
    ki = 0.5;
    kd = 0.5;
}

void PositionControl::setPosition(float setpoint_l, float setpoint_r)
{
    float gradosl, gradosr;
    float error_l, error_r;
    float error_l_prev, error_r_prev;
    float error_l_integral = 0.0, error_r_integral = 0.0;
    float error_l_deriv = 0.0, error_r_deriv = 0.0;



    //Obtenemos posicion en este instante
    gradosl = misEncoders[LEFT]->getPosicionGrados();
    gradosr = misEncoders[RIGHT]->getPosicionGrados();

    // Calculamos los errores
    error_l = setpoint_l - gradosl;
    error_r = setpoint_r - gradosr;

    // Se ejecuta el siguiente while hasta que se alcance un error determinado
    // TODO: Deberia haber un timeout para evitar que se quede en un bucle infinito
    while((error_l > 1.0 || error_l< -1.0) || (error_r > 1.0 || error_r < -1.0))
    {
        // Lectura
        gradosl = misEncoders[LEFT]->getPosicionGrados();
        gradosr = misEncoders[RIGHT]->getPosicionGrados();

        // Cálculos
        error_l = setpoint_l - gradosl;
        error_l_integral += error_l;
        error_l_deriv = error_l - error_l_prev;

        error_r = setpoint_r - gradosr;
        error_r_integral += error_r;
        error_r_deriv = error_r - error_r_prev;

        // Calculamos la velocidad de los motores
        // (salida del PID)
        vel_i = kp * error_l + ki * error_l_integral + kd * error_l_deriv;
        vel_d = kp * error_r + ki * error_r_integral + kd * error_r_deriv;


        // Se aplican las velocidades
        // Se hace un control por saturacion
        // Motor Izquierdo
        if (vel_i > 0.0)
        {
            misMotores[LEFT]->setFwd();
            misMotores[LEFT]->setPWM(vel_i > VEL_MAX_ENC? VEL_MAX_ENC : vel_i);
        }
        else{
            misMotores[LEFT]->setBack();
            misMotores[LEFT]->setPWM(-vel_d > VEL_MAX_ENC? VEL_MAX_ENC : -vel_d);
        }

        // Motor Derecho
        if (vel_d > 0.0)
        {
            misMotores[RIGHT]->setFwd();
            misMotores[RIGHT]->setPWM(vel_d > VEL_MAX_ENC? VEL_MAX_ENC : vel_d);
        }
        else
        {
            misMotores[RIGHT]->setBack();
            misMotores[RIGHT]->setPWM(-vel_d > VEL_MAX_ENC? VEL_MAX_ENC : -vel_d);
        }

        // Dejamos los motores libres
        misMotores[LEFT]->setFree();
        misMotores[RIGHT]->setFree();
    }
}

void PositionControl::avanzarDistancia(float distance)
{
    float angle = 360.0*distance/(ROBOT_RADIUS*PI);
    this->setPosition(angle, angle);
}

float PositionControl::girar(float beta)
{
    float phi = ROBOT_WIDTH*beta/ROBOT_RADIUS;
    this->setPosition(phi, -phi);
    return phi; 
}

void PositionControl::resetEncoders()
{
    misEncoders[LEFT]->resetPosicion();
    misEncoders[RIGHT]->resetPosicion();
}

void PositionControl::parar()
{
    misMotores[LEFT]->setFree();
    misMotores[RIGHT]->setFree();
}


    