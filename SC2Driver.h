#ifndef SC2_DRIVER
#define SC2_DRIVER
#include "Driver.h"
#include "windows.h"
#include "sc2_SDKAddendum.h"
#include "sc2_SDKStructures.h"
#include "SC2_CamExport.h"
#include "pco_structures.h"
#include "pco_convstructures.h"
#include "pco_convexport.h"
#include "pco_convdlgexport.h"
#include "PCO_Err.h"
#include "PCO_Errt.h"
#include "Sc2_DialogExport.h"
#include "sc2_defs.h"

namespace forms2{
	
	public ref class SC2Driver : Driver {
	public:
		SC2Driver();
		~SC2Driver(){}
		virtual int initCamera() override;
		virtual int openCameraDialog() override;
		virtual void lockCameraDialog(bool lock) override;
		virtual void closeCamera() override;
		virtual void expose() override;
		virtual void stop() override;
		virtual int getImageStatus() override;
		virtual int getImageWidth() override;
		virtual int getImageHeight() override;
		virtual int armCamera() override;
		virtual void readImage(UInt16 *buffer) override;
		virtual String^ getDriverName() override {return gcnew String("SC2 Cam");}
		
		//settings
		virtual int getRows() override;
		virtual int getCols() override;
		virtual bool isDouble() override;
		virtual void update() override;
	protected:
		//int mode;
		//int trig;
		//char table[300];
		HANDLE hCam;
		HANDLE hDialog;
		SHORT sBufNr;
		HANDLE hEvent;
		WORD* wBuf;
		PCO_General strGeneral;
		PCO_CameraType strCamType;
		PCO_Sensor strSensor;
		PCO_Description strDescription;
		PCO_Timing strTiming;
		PCO_Storage strStorage;
		PCO_Recording strRecording;
		PCO_Image strImage;

		virtual void getSettings() override;
		virtual void disconnected();
	};
}
#endif