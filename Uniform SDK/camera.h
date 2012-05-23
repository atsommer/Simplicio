//header for Cooke Camera Interface
#include <windows.h>
#ifndef CAMERA_H
#define CAMERA_H

#ifdef __cplusplus
extern "C" {            /* Assume C declarations for C++ */
#endif  /* __cplusplus */

#ifndef BOOL
#define BOOL int
#endif  

#ifndef DWORD
#define DWORD unsigned long
#endif  


#ifndef HANDLE
#define HANDLE void *
#endif  


typedef struct
{
	BOOL setupOK;		//true if setup successful;  
	int mode;			//the current mode
	int trig;			// trigger 
	DWORD exptime;		//exposure time
	int hbin;			//horizontal binning
	int vbin;			//vertical binning
	int delay;			//sensicam only
	int gain;			
	RECT roi;		//current setting of ROI
	int imgx;		//image size in x dimension (pixels)
	int imgy;		//image size in y dimension (pixels)
	int submode;
} CAMSETTING;

typedef struct
{
	BOOL initOK;
	// TRUE if board initialized sucessfully
	int		boardnum;			//reserved
	char	camname[20];		//camera name
	int		color;
	int		shutter; 
	int		version;
	int		x_max;
	int		y_max;
	char *	pictptr; 
	//pointing to image data, alternating for pixelfly
	CAMSETTING setting;

	//pixelfly exclusive
	HANDLE camhandle;
	BOOL fp; //flips to alternate pixelfly buffers, points to the active buffer
	int bufnr[2];	//
	DWORD linaddr[2];	//buffer mapped user space address, pictptr point to one of them
	HINSTANCE PixLib;
	HINSTANCE SenLib;
} CAMINFO;

#ifdef __cplusplus
}           /* Assume C declarations for C++ */
#endif  /* __cplusplus */

#endif /* CAMERA_H */

