/*=============================================================

	SENCAM_DEF.H

	Header file for SENCAM DLL
	Author MB

	Compiler: MS VISUAL C++ 6.0
==================================================================*/

#ifndef CAM_TYPES_H
#define CAM_TYPES_H

/*=============================================================*/
/* BOARD DEFINES                                               */  
/*=============================================================*/
#ifndef BOARD_DEF
#define BOARD_DEF

//boardtyp
 #define NOBOARD    0x0000
 #define PCI520     0x0001
 #define PCI525     0x0002
 #define PCI525C    0x0003

#endif


/*=============================================================*/
/*  CAMERA TYPES                                               */
/*=============================================================*/


//cam_typ
#define NOCAM      0x0
#define FASTEXP    0x1
#define LONGEXP    0x2
#define OEM        0x3 //reserved
#define TEST       0x4 //reserved
#define DICAM      0x5
#define LONGEXPI   0x6
#define LONGEXPQE  0x7

#define FASTEXPQE  0x8

//mode
#define M_LONG     0x00
#define M_FAST     0x01
#define M_DICAM    0x05

//submode FASTEXP
#define NORMALFAST 0x0
#define DOUBLE     0x1 //special hardware needed
#define DOUBLEL    0x2 //special hardware needed
#define FMODU      0x3 //special hardware needed
#define TRIPLE     0x4 //special hardware needed
#define CYCLE      0x5 
#define ABB        0x6 //special hardware needed
#define QUAD       0x7 //special hardware needed
#define QUADT      0x8 //special hardware needed
#define QUADL      0x9 //special hardware needed

//submode LONGEXP
#define NORMALLONG 0x0
#define VIDEO      0x1
#define MECHSHUT   0x2
#define MECHSHUTV  0x3
#define BINNING32  0x4
#define FASTFRAME  0x5 
#define DOUBLELONG 0x6

#define QE_FAST    0x8
#define QE_DOUBLE  0x9 //special hardware needed

#define ASYNC_INT   0x10
#define ASYNC_INT_D 0x11
#define ASYNC_EXT   0x12
#define ASYNC_EXT_D 0x13

//@ver3.30
#define EM_FAST     0x14
#define EM_FAST_V   0x15
#define EM_FAST_M   0x16
#define EM_FAST_MV  0x17

//submode DICAM
#define DPSINGLE   0x0
#define DPMULTI    0x1
#define DPDOUBLE   0x2

#endif

