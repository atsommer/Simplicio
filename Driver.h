#ifndef DRIVER
#define DRIVER

namespace forms2{
	using namespace System;

	ref class Driver abstract{
	public:
			
		virtual int initCamera()=0;
		virtual int openCameraDialog(){return 0;}
		virtual void lockCameraDialog(bool lock){}
		virtual void closeCamera()=0;
		virtual void expose()=0;
		virtual void stop()=0;//stops acquistion
		virtual int getImageStatus()=0;
		virtual int getImageWidth()=0;
		virtual int getImageHeight()=0;
		virtual void readImage(UInt16 *buffer)=0;
		virtual int armCamera()=0;
		virtual String^ getDriverName()=0;
		//String^ getCameraName(){return new String(cameraName);}

		//settings
		virtual int getRows()=0;
		virtual int getCols()=0;
		virtual int getHBin(){getSettings();return hbin;}
		virtual int getVBin(){getSettings();return vbin;}
		virtual bool isDouble(){return false;}
		virtual void update()=0;

		static const int MODE = 1;
		static const int TRIG = 1<<1;
		static const int ROIX1 = 1<<2;
		static const int ROIX2 = 1<<3;
		static const int ROIY1 = 1<<4;
		static const int ROIY2 = 1<<5;
		static const int HBIN = 1<<6;
		static const int VBIN = 1<<7;
	//	static const int TABLE = 1<<8;
		static const int NULL_SETTING = -999;

		//status
		static const int CAMERA_IDLE = 0;
		static const int CAMERA_BUSY = 1;
		static const int IMAGE_ERROR = 2;

		//detecting the camera
		static const int NO_CAMERA = 1;
		static const int INIT_ERROR = 2;

	protected:
		//int mode;
		//int trig;
		int roix1; 
		int roix2; 
		int roiy1; 
		int roiy2;
		int hbin;
		int vbin;
		//char table[300];
		virtual void getSettings()=0;
	};
}
#endif