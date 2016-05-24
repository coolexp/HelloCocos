package org.cocos2dx.cpp;


import org.cocos2dx.lib.Cocos2dxHandler.DialogMessage;

import android.os.Handler;
import android.os.Message;

public class JniFuncHelper {
	private static Handler mHandler;
	
	public static void init(Handler handler)
	{
		JniFuncHelper.mHandler = handler;
	}
	
    public static native void setPackageName(String packageName);
    
    public static native void exitApp();
    
    private static void showTipDialog(final String title, final String text)
    {
    	Message msg = mHandler.obtainMessage();
    	msg.what = AppActivity.SHOW_DIALOG;
    	DialogMessage dm = new DialogMessage(title, text);
    	msg.obj = dm;
    	msg.sendToTarget();
    }
}
