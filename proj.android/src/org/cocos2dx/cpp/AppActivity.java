/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

import org.cocos2dx.cpp.ScreenObserver.ScreenStateListener;
import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;
import org.cocos2dx.lib.Cocos2dxHelper;
import org.cocos2dx.lib.Cocos2dxHandler.DialogMessage;

import com.tencent.bugly.crashreport.CrashReport;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;

public class AppActivity extends Cocos2dxActivity {
	public static final int SHOW_DIALOG = 0x0001;
	private String TAG = "ScreenObserverActivity";
	private ScreenObserver mScreenObserver;

	private Boolean m_pScreenIsOn = true;
	private Boolean m_pIsLock = false;
	private Boolean m_pIsPause = false;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
        CrashReport.initCrashReport(getApplicationContext());
        CrashReport.setUserId("TestUser");
        JniFuncHelper.init(mHandler);
        JniFuncHelper.setPackageName(this.getPackageName());
        //CrashReport.testJavaCrash();
        //CrashReport.testNativeCrash();
        mScreenObserver = new ScreenObserver(this);
		mScreenObserver.requestScreenStateUpdate(new ScreenStateListener() {
			
			public void onScreenOn() {
				doSomethingOnScreenOn();
			}
			
			public void onScreenOff() {
				// TODO Auto-generated method stub
				doSomethingOnScreenOff();
			}
			public void onUserPresent() {
				// TODO Auto-generated method stub
				doSomethingOnUserPresent();
			}
		});
	}
	private void doSomethingOnScreenOn() {
		Log.i(TAG, "Screen is on");
		m_pScreenIsOn = true;
		doResume();
	}

	private void doSomethingOnScreenOff() {
		Log.i(TAG, "Screen is off");
		m_pScreenIsOn = false;
		m_pIsLock = true;
	}
	private void doSomethingOnUserPresent() {
		Log.i(TAG, "nUserPresent");
		m_pIsLock = false;
		doResume();
	}
	private void doResume(){
		if(!m_pIsPause&&!m_pIsLock&&m_pScreenIsOn){
			 Cocos2dxHelper.onResume();
			 Cocos2dxGLSurfaceView.getInstance().onResume();
		}
	}
	@Override
    protected void onResume() {
		super.onResume();
		m_pIsPause = false;
		doResume();
    }
	@Override
    protected void onPause() {
		m_pIsPause = true;
        super.onPause();
    }
	@Override
    protected void onDestroy() {
		super.onDestroy();
		mScreenObserver.stopScreenStateUpdate();
	}
	private Handler mHandler = new Handler()
    {
		@Override
		public void handleMessage(Message msg) {

			switch(msg.what)

			{
			case SHOW_DIALOG:
				DialogMessage dm = (DialogMessage)msg.obj;

				new AlertDialog.Builder(AppActivity.this)
				.setTitle(dm.titile)
				.setMessage(dm.message).setNegativeButton("cancel", new DialogInterface.OnClickListener() {
					
					@Override
					public void onClick(DialogInterface dialog, int which) {
						dialog.dismiss();
					}
				})
				.setPositiveButton("Ok", 
						new DialogInterface.OnClickListener() {

					@Override
					public void onClick(DialogInterface dialog, int which) {
						dialog.dismiss();
						//JniFuncHelper.exitApp();
						CrashReport.testNativeCrash();
					}
				})
				.create().show();
				break;
			}

		}
    };
}
