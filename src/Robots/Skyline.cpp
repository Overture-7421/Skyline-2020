#include "Skyline.h"
#include "frc2/command/CommandScheduler.h"
#include <frc/smartdashboard/SmartDashboard.h>

Skyline::Skyline() : TimedRobot() {}

void Skyline::RobotInit() {

}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want to run during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Skyline::RobotPeriodic() {

}

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Skyline::DisabledInit() {}

void Skyline::DisabledPeriodic() {}

/**
 * This autonomous runs the autonomous command selected by your {@link
 * RobotContainer} class.
 */
void Skyline::AutonomousInit() {}

void Skyline::AutonomousPeriodic() {


    double leftY = -xboxController.GetRawAxis(1);
    double rightY = -xboxController.GetRawAxis(4);

    /**
     * Los Joysticks son analogos, cuando los soltamos no regresan magicamente a cero por cuestiones mecanicas.
     * Esto puede causar que sigan dandonos una salida, cercana a cero, pero no cero. Por lo tanto los motores pueden seguirse moviendo sin que queramos.
     * Para arreglar esto podemos utilizar un "deadband", esto significa que lo obtenido del joystick tiene que ser mayor del "deadband" para ser usado,
     * si no, lo mandamos a cero.
     *
     * Esta es la manera más sencilla de arreglarlo.
     */
    if (std::abs(leftY) < deadband) { // Usamos el valor absoluto para que no importe si es negativo o positivo.
        leftY = 0;
    }

    if (std::abs(rightY) < deadband) {
        rightY = 0;
    }

    leftMotor.set(leftY);
    rightMotor.set(rightY);

}

void Skyline::TeleopInit() {}

/**
 * This function is called periodically during operator control.
 */
void Skyline::TeleopPeriodic() {


    /**
     * Ahora vamos a controlar el robot de una manera un poco más formal. Es más util pensar en el control del chassis en velocidades,
     * "Quiero que el chassis se mueva a X velocidad lineal (Que tan rapido se mueve en linea recta), y a Y velocidad angular (Que tan rapido queremos que gire)."
     *
     * Para esto podemos hacer uso de la siguiente ecuación.
     *
     * Motor Izquierdo: velLinear - velAngular;
     * Motor Derecho: velLinear + velAngular;
     *
     * Ahora, la variable velLinear controla la velocidad linear del chassis, y velAngular la angular.
     *
     * Podemos darles valores a esas dos variables usando el joystick:
     */


    double velLinear = -xboxController.GetRawAxis(1);
    double velAngular = -xboxController.GetRawAxis(3); // Usamos un eje para controlar la velocidad angular usando el joystick derecho, de lado a lado

    if (std::abs(velLinear) < deadband) { // Usamos el valor absoluto para que no importe si es negativo o positivo.
        velLinear = 0;
    }

    if (std::abs(velAngular) < deadband) {
        velAngular = 0;
    }


    /**
     * Aqui estamos usando algo llamado Kinematics, a grandes rasgos, si quiero que el chassis haga X cosa, ¿Que tengo que
     * pedirle a cada motor para que se cumpla?
     */
    leftMotor.set(velLinear - velAngular);
    rightMotor.set(velLinear + velAngular);

}

/**
 * This function is called periodically during test mode.
 */
void Skyline::TestPeriodic() {}
