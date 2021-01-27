//
// Created by hiram on 8/08/19.
//

#ifndef BOTBUSTERS_REBIRTH_ECTOMOTOR_H
#define BOTBUSTERS_REBIRTH_ECTOMOTOR_H

#include "EctoMotorMode.h"
#include "MotorFeedbackMode.h"

#include "Control/PID/PIDConfig.h"

/**
 * Base structure for a motor controller
 */
class EctoMotor{
public:
	explicit EctoMotor(int motorID, const std::string &motorName);
	
	
	std::string getName() const;
	
	virtual void factoryReset() = 0;
	
	void setControlMode(MotorControlMode controlMode);
	
	MotorControlMode getControlMode() const;
	
	/**
	 * Set the feedback mode used for frc::PIDSource
	 * @param feedbackMode
	 */
	void setFeedbackMode(MotorFeedbackMode feedbackMode);
	
	MotorFeedbackMode getFeedbackMode() const;
	
	/**
	 * True is normally closed, false is normally opened
	 * TODO create enum for this
	 */
	virtual void setLimitSwitchPolarity(bool switchPolarity) = 0;
	
	double getPosition() const;
	
	double getVelocity() const;
	
	int getId() const;
	
	void set(double value);
	
	void set(double value, MotorControlMode newControlMode);
	
	virtual std::string getFirmwareVersion() const = 0;
	
	virtual void invertMotor(bool state) = 0;
	
	virtual bool isMotorInverted() const = 0;
	
	virtual void invertSensor(bool state) = 0;
	
	virtual bool isSensorInverted() const = 0;
	
	virtual void setPIDConfig(const PIDConfig &pidConfig, int profileSlot = 0) = 0;
	
	virtual void enableBrakingOnIdle(bool state) = 0;
	
	virtual void enableCurrentLimit(bool state) = 0;
	
	virtual void setMotorCurrentLimit(double amps) = 0;
	
	virtual void setClosedLoopOutputRange(double minimum, double maximum) = 0;
	
	virtual void setClosedLoopRampRate(double rampRate) = 0;
	
	virtual void setOpenLoopRampRate(double rampRate) = 0;
	
	/**
	 * Set the current position in radians
	 * @param position
	 */
	virtual void setSensorPosition(double position) = 0;
	
	virtual double getTemperature() const = 0;
	
	virtual double getCurrent() const = 0;
	
	virtual double getVoltage() const = 0;
	
	virtual double getOutputPercent() const = 0;
	
	virtual void setEncoderCodesPerRev(int codes) = 0;
	
	virtual int getEncoderCodesPerRev() const = 0;
	
	/**
	 * (In volts)
	 * Feedforward is not set until the next set command is sent
	 */
	virtual void setArbitraryFeedForward(double feedForward) = 0;
	
	virtual void disable() = 0;
	
	virtual bool isDisabled() const = 0;

	
	virtual void setAnalogSensorOffset(double analogVoltageOffset) = 0;
	
	std::pair<MotorControlMode, double> getLastSetpoint() const;
	
	void outputSet(double set);
	
protected:
	
	virtual double getRawAnalogPosition() const = 0;
	
	virtual double getPotPosition() const = 0;
	
	virtual double getPotVelocity() const = 0;
	
	virtual double getQuadPosition() const = 0;
	
	virtual double getQuadVelocity() const = 0;
	
	virtual void setVoltageOutput(double voltage) = 0;
	
	virtual void setMotorOutputByCurrent(double amps) = 0;
	
	virtual void setOutputPercent(double value) = 0;
	
	virtual void setPositionSetpoint(double position) = 0;
	
	virtual void setVelocitySetpoint(double velocity) = 0;
		
	virtual void setPotAsClosedLoopSource() = 0;
	
	virtual void setQuadAsClosedLoopSource() = 0;
	
	int id;
	std::string name;
	MotorControlMode controlMode = MotorControlMode::Percent;
	MotorFeedbackMode feedbackMode = MotorFeedbackMode::QuadEncoder;
	std::pair<MotorControlMode, double> lastSetpoint{};
	bool disabled = false;
};

#endif //BOTBUSTERS_REBIRTH_ECTOMOTOR_H
