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
                break;
            case MotionEvent.ACTION_POINTER_DOWN:
                holdTimer.cancel();
                break;
            case MotionEvent.ACTION_MOVE:
                if( event.getPointerCount() > 1 )
                {
                    if( pointerId <= 1 )
                    {
                        // calc dist, zoom
                        APCLib.zoom(1.f);
                    }
                }
                else
                {
                    holdTimer.cancel();
                    APCLib.holdedMove(x, y);
                }
                break;
            case MotionEvent.ACTION_UP:
            case MotionEvent.ACTION_CANCEL:
                holdTimer.cancel();
                APCLib.button(x, y);
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
            APCLib.altButton(x, y);
		}
	}
}