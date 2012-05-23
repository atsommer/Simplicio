#pragma once
//The CameraDriver is generic class that defines the interface to the camera. 
//Drivers for other cameras inherit from it
//It should be an abstract class but that generates a warning

namespace forms2{
using namespace System;

public ref class CameraDriver
{
public:
	CameraDriver(void);
	~CameraDriver();
	virtual int initCamera(){return 0;}
	virtual int openCameraDialog(){return 0;}
	virtual void lockCameraDialog(bool lock){}
	virtual void closeCamera(){}
	virtual void expose(){}
	virtual void stop(){}
	virtual int getImageStatus(){return 0;}
	virtual int getImageWidth(){return 0;}
	virtual int getImageHeight(){return 0;}
	virtual void readImage(UInt16 *buffer){}

	//settings
	virtual int getRows(){return 0;}
	virtual int getCols() {return 0;}
	virtual int getHBin(){getSettings();return hbin;}
	virtual int getVBin(){getSettings();return vbin;}
	virtual bool isDouble(){return false;}
	virtual void update(){}

protected:
	int roix1; 
	int roix2; 
	int roiy1; 
	int roiy2;
	int hbin;
	int vbin;

	virtual void getSettings(){}

};
}
