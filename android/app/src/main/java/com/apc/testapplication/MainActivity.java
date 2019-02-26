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
        pointerIds[0] = -1;
        pointerIds[1] = -1;
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
    private int[] pointerIds = new int[2];

    @Override
    public boolean onTouch(View v, MotionEvent event) {
        int index = event.getActionIndex();
        int action = event.getActionMasked();
        int pointerId = event.getPointerId(index);

        Log.v("APC", "Even. Type: " + event.getAction() + ", index: " + index + ", action: " + action + ", pointer: " + pointerId);

        int x = (int)MotionEventCompat.getX(event, index);
        int y = (int)MotionEventCompat.getY(event, index);

        // TODO: rework multitouch
        switch (action) {
            case MotionEvent.ACTION_DOWN:
                pointerIds[0] = pointerId;
                holdTimer = new Timer();
                holdTimerTask = new HoldTouchTask(x, y);
                holdTimer.schedule(holdTimerTask, 2000);
                break;
            case MotionEvent.ACTION_POINTER_DOWN:
                if(pointerIds[1] == -1)
                {
                    pointerIds[1] = pointerId;
                    holdTimer.cancel();
                }
                break;
            case MotionEvent.ACTION_MOVE:
                if( pointerIds[0] != -1 )
                {
                    if( pointerIds[1] != -1 )
                    {
                        if( pointerId == pointerIds[0] || pointerId == pointerIds[1] )
                        {
                            // calc dist, zoom
                            APCLib.zoom(1.f);
                        }
                    }
                    else if( pointerId == pointerIds[0] )
                    {
                        holdTimer.cancel();
                        APCLib.holdedMove(x, y);
                    }
                }
                break;
            case MotionEvent.ACTION_UP:
            case MotionEvent.ACTION_CANCEL:
                if( pointerId == pointerIds[0])
                {
                    if( pointerIds[1] == -1)
                    {
                        pointerIds[0] = -1;
                        holdTimer.cancel();
                        APCLib.button(x, y);
                    }
                    // else
                    // {
                    //     pointerIds[0] = pointerIds[1];
                    //     pointerIds[1] = -1;
                    // }
                } 
                break;
            case MotionEvent.ACTION_POINTER_UP:
                if( pointerId == pointerIds[1] )
                {
                    pointerIds[1] = -1;
                } 
                else if( pointerId == pointerIds[0] )
                {
                    pointerIds[0] = pointerIds[1];
                    pointerIds[1] = -1;
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
            if( pointerIds[1] == -1 )
            {
                pointerIds[0] = -1;
                APCLib.altButton(x, y);
            }
		}
	}
}