package com.apc.testapplication;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.view.WindowManager;
import android.view.View.OnTouchListener;
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
 
    private boolean buttonPressed = false;
	private Timer holdTimer;
	private HoldTouchTask holdTimerTask;

    @Override
    public boolean onTouch(View v, MotionEvent event) {
        int x = (int)event.getX();
        int y = (int)event.getY();

        switch (event.getAction()) {
            case MotionEvent.ACTION_DOWN:
                buttonPressed = true;
				holdTimer = new Timer();
                holdTimerTask = new HoldTouchTask(x, y);
                holdTimer.schedule(holdTimerTask, 2000);
                break;
            case MotionEvent.ACTION_MOVE:
                if( buttonPressed )
                {
                    holdTimer.cancel();
                    APCLib.holdedMove(x, y);
                }
                break;
            case MotionEvent.ACTION_UP:
            case MotionEvent.ACTION_CANCEL:   
                if(buttonPressed)
                {
                    holdTimer.cancel();
                    APCLib.button(x, y);
                }
                buttonPressed = false;
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
            buttonPressed = false;
			APCLib.altButton(x, y);
		}
	}
}