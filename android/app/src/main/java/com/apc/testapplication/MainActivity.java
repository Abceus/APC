package com.apc.testapplication;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.view.WindowManager;
import android.view.View.OnTouchListener;
import android.support.v4.view.MotionEventCompat;
import android.util.Log;
import java.util.Timer;
import java.util.TimerTask;
import java.lang.Math;

public class MainActivity extends Activity implements OnTouchListener {

    GL2JNIView mView;

    @Override protected void onCreate(Bundle icicle) {
        super.onCreate(icicle);
        mView = new GL2JNIView(getApplication());
        mView.setOnTouchListener(this);
        setContentView(mView);
    }

    @Override protected void onPause() {
        super.onPause();
        mView.onPause();
    }

    @Override protected void onResume() {
        super.onResume();
        mView.onResume();
    }
 
	private Timer holdTimer;
    private HoldTouchTask holdTimerTask;
    private boolean dragged = false;
    private boolean click = true;
    private int[][] mTouches = new int[2][2];
    private int initDist;

    @Override
    public boolean onTouch(View v, MotionEvent event) {
        int index = event.getActionIndex();
        int action = event.getActionMasked();
        int pointerId = event.getPointerId(index);

        int x = (int)MotionEventCompat.getX(event, index);
        int y = (int)MotionEventCompat.getY(event, index);

        switch (action) {
            case MotionEvent.ACTION_DOWN:
                holdTimer = new Timer();
                holdTimerTask = new HoldTouchTask(x, y);
                holdTimer.schedule(holdTimerTask, 2000);
                click = true;
                mTouches[0][0] = x;
                mTouches[0][1] = y;
                break;
            case MotionEvent.ACTION_POINTER_DOWN:
                if( pointerId == 1 )
                {
                    click = false;
                    holdTimer.cancel();
                    mTouches[1][0] = x;
                    mTouches[1][1] = y;
                    initDist = Math.abs(mTouches[0][0] - mTouches[1][0]) + Math.abs(mTouches[0][1] - mTouches[1][1]);
                }
                break;
            case MotionEvent.ACTION_MOVE:
                if( event.getPointerCount() > 1 )
                {
                    int otherX = (int)MotionEventCompat.getX(event, 1);
                    int otherY = (int)MotionEventCompat.getY(event, 1);
                    mTouches[0][0] = x;
                    mTouches[0][1] = y;
                    mTouches[1][0] = otherX;
                    mTouches[1][1] = otherY;
                    int currentDist = Math.abs(mTouches[0][0] - mTouches[1][0]) + Math.abs(mTouches[0][1] - mTouches[1][1]);
                    APCLib.zoom((currentDist - initDist) / 100.f);
                    initDist = currentDist;
                }
                else
                {
                    holdTimer.cancel();
                    if( !dragged )
                    {
                        dragged = true;
                        APCLib.drag(x, y);
                    }
                    else
                    {
                        APCLib.holdedMove(x, y);
                        mTouches[0][0] = x;
                        mTouches[0][1] = y;
                    }
                }
                break;
            case MotionEvent.ACTION_UP:
            case MotionEvent.ACTION_CANCEL:
                holdTimer.cancel();
                if( dragged )
                {
                    dragged = false;
                    APCLib.drop(x, y);
                }
                else if( click )
                {
                    APCLib.button(x, y);
                }
                break;
        }
        return true;
    }

	class HoldTouchTask extends TimerTask {
        private int x;
        private int y;
        HoldTouchTask( int x, int y )
        {
            this.x = x;
            this.y = y;
        }
		@Override
		public void run() {
            click = false;
            APCLib.altButton(x, y);
		}
	}
}