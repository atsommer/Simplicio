#pragma once

#include "CameraDriver.h"
using namespace System;

ref class SensicamDriver : CameraDriver
{
public:
	SensicamDriver(void);
	void initCamera();
	bool openCameraDialog();
	void lockCameraDialog(bool lock);
	void expose();
	void stop();
	int getImageStatus();
	int getImageWidth();
	int getImageHeight();
	void readImage(UInt16 *buffer);
};
