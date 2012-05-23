using System;
using System.Collections.Generic;
using System.Text;
using WINX32Lib;

namespace WinXWrapper
{
    public class WinXWrapperClass
    {
        public static short GetExpParam(ExpSetupClass expObj, EXP_CMD paramID)
        {
            short p = new short();
            expObj.GetParam(paramID , out p);
            return p;
        }
    }
}
