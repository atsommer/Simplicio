/***********************************************************
camera.h ----header for Cooke Camera Interface
Author: S. Zhao
Copyright The Cooke Corporation @2002
***********************************************************/

//revision 1.1


#ifndef UNIFORM_SDK_H
#define UNIFORM_SDK_H

#ifdef __cplusplus
extern "C" {            /* Assume C declarations for C++ */
#endif  /* __cplusplus */


#define DMA_ERR -60 
#define ERRNOINIT -59
#define ERROSVERSION -58
#define	ERRNODRIVER -57
#define ERRNODLL	-56
#define ERRBINROIPARA	-55
#define EXPTIMEOUT -54
#define MEMORYERR -53
#define ERRCAMTYPE -52
#define ERRBOARDNUM -51
#define DLL_ERR -50  //internal err or missing


int  SELECT_CAMERA(const char * cameratype, int board_num, int * ID, CAMINFO * camdata );
int  SETUP_CAMERA( int ID, CAMINFO* camdata, int mode, int submode, int trig,  int riox1, int roix2, int rioy1, int rioy2,int hbin, int vbin, int gain, int delay, int exptime);
int  GETIMAGE(int ID, CAMINFO* camdata, DWORD timeout);
int  SNAP(int ID,CAMINFO* camdata, int mode);
int  CLOSE_CAMERA(int ID, CAMINFO* camdata);
int  GETCAMINFO(int ID,CAMINFO* camdata, int *color, int * shutter, int * ccdx, int * ccdy, int * ele_temp, int *ccd_temp);
int  STOP_CCD(int ID, CAMINFO* camdata);


#ifdef __cplusplus
}           /* Assume C declarations for C++ */
#endif  /* __cplusplus */

#endif /* CAMERA_H */