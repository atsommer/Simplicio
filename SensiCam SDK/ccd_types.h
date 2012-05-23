/*=============================================================*/
/* CCDCHIP DEFINES                                             */  
/*=============================================================*/

#ifndef CCD_TYPES_H
#define CCD_TYPES_H


/* ccdtype */
/* xxC are Color CCD-Chips*/
 
#define CCD74      0x0001
#define CCD74C     0x0002
#define CCD85      0x0003
#define CCD85C     0x0004

#define CCD85i     0x0005
#define CCD205Q    0x0009
#define CCD205QS   0x000A
#define CCD205F    0x000B
#define CCD285QE   0x0011
#define CCD285CT   0x0015
#define CCD285QEF  0x0017
#define CCD285QED  0x0019

#define CCDTIEM285 0x0020
#define CCDE2V97   0x0022

/* Parameters CCD74 */  
#define XRES74       640
#define YRES74       480

#define PDLINES74    1500
#define PDTIMEL74    3071
#define AOIOFF74     4*32

#define LINET74R     63.520000F


/* Parameters CCD85 */  

#define XRES85       1280
#define YRES85       1024

#define PDLINES85    1900
#define PDTIMEL85    3071
#define AOIOFF85     5*32

#define LINET85      117.280000F


/* Parameters CCD85i */ 

#define XRES85i      1312
#define YRES85i      1032

#define PDLINES85i   1900
#define PDTIMEL85i   3071
#define AOIOFF85i    4*32

#define LINET85i     117.280000F


/* Parameters CCD205Q */ 

#define XRES205Q     1280
#define YRES205Q     1024

#define PDLINES205Q   1900
#define PDTIMEL205Q   3071
#define AOIOFF205Q    5*32

#define LINET205Q     117.280000F

/* Parameters CCD205Q */ 

#define XRES205QS     1280
#define YRES205QS     1024

#define PDLINES205QS   1900
#define PDTIMEL205QS   3071
#define AOIOFF205QS    5*32

#define LINET205QS     117.280000F


/* Parameters CCD205F */ 

#define XRES205F     1280
#define YRES205F     1024

#define PDLINES205F   1900
#define PDTIMEL205F   3071
#define AOIOFF205F    5*32

#define LINET205F     117.280000F

/* Parameters CCD285QE */ 
/* Parameterts CCD285QEF + CCD285QED */

#define XRES285QE     1376
#define YRES285QE     1040

#define LINET285QE      95.500000F

#define PDLINES285QE   1900
#define PDTIMEL285QE   3071
#define AOIOFF285QE    3*32



#define XRES_TIEM285   1024
#define YRES_TIEM285   1002

#define LINET_TIEM285    75.000000F

#define PDLINES_TIEM285   1900
#define PDTIMEL_TIEM285   3071
#define AOIOFF_TIEM285    3*32

#define XRES_E2V97   512
#define YRES_E2V97   512

#define LINET_E2V97    50.000000F//@@@

#define PDLINES_E2V97   1900
#define PDTIMEL_E2V97   3071
#define AOIOFF_E2V97    3*32//@@@




#endif