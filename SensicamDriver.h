#pragma once
#include "CameraDriver.h"

namespace forms2{

	public ref class SensicamDriver : public CameraDriver
	{
	public:
		SensicamDriver(void);
		~SensicamDriver(){;}
		virtual int initCamera() override;
		virtual int openCameraDialog() override;
		virtual void closeCamera() override;
		virtual void lockCameraDialog(bool lock) override;

		//settings
		virtual int getRows() override;
		virtual int getCols() override;
		virtual bool isDouble() override;

/*
		static const int MODE = 1;
		static const int TRIG = 1<<1;
		static const int ROIX1 = 1<<2;
		static const int ROIX2 = 1<<3;
		static const int ROIY1 = 1<<4;
		static const int ROIY2 = 1<<5;
		static const int HBIN = 1<<6;
		static const int VBIN = 1<<7;
	//	static const int TABLE = 1<<8;
	*/
		static const int NULL_SETTING = -999;


	protected: 
		int mode;
		int trig;
		//char table[300];
		virtual void getSettings() override;
	};

	public class SensicamHelper
	{	
		SensicamHelper(){}
		~SensicamHelper(){}

	};
}

