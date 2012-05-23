#ifndef SENCAM_DRIVER
#define SENCAM_DRIVER
#include "Driver.h"

namespace forms2{
	
	ref class SencamDriver : Driver {
	public:
		SencamDriver();
		~SencamDriver(){}
		virtual int initCamera() override;
		virtual int openCameraDialog() override;
		virtual void lockCameraDialog(bool lock) override;
		virtual void closeCamera() override;
		virtual void expose() override;
		virtual void stop() override;
		virtual int getImageStatus() override;
		virtual int getImageWidth() override;
		virtual int getImageHeight() override;
		virtual void readImage(UInt16 *buffer) override;
		virtual String^ getDriverName() override {return gcnew String("Sensicam");}
		virtual int armCamera() override;

		//settings
		virtual int getRows() override;
		virtual int getCols() override;
		virtual bool isDouble() override;
		virtual void update() override;
	protected:
		int mode;
		int trig;
		//char table[300];
		
		virtual void getSettings() override;
	};
}
#endif