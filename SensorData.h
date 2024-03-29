#ifndef PCLDATA_H
#define PCLDATA_H

#include "Aria.h"
#include "ArNetworking.h"

#include "utils.h"

// Abstract base class for robot sensor data
class SensorData {
public:
  SensorData(ArServerBase *server, ArRobot *robot);
protected:
  ArServerBase *myServer;
  ArRobot *myRobot;

  virtual void send(ArServerClient *serverClient, ArNetPacket *packet) = 0;
  virtual void addData() = 0;
};

// Sends laser data
class SensorDataLaser : public SensorData {
public:
  SensorDataLaser(ArServerBase *server, ArRobot *robot,
      		  int tilt, const A3dpoint &laserToRobotTranslation,
		  int maxRange, int minRange);
  void send(ArServerClient *serverClient, ArNetPacket *packet);
  void addData();

  static const double pi;
  static const double toRadian;

private:
  ArFunctor2C<SensorDataLaser, ArServerClient *, ArNetPacket *> mySendFtr;
  ArLaser *myLaser;
  int myTilt;
  A3dpoint myLaserToRobotTranslation;
  int myMaxRange;
  int myMinRange;
};


#endif
