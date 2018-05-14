package JCxYIS.KartGen3;

import com.unity3d.player.UnityPlayerActivity;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Intent;
import android.widget.Toast;
import com.unity3d.player.UnityPlayer;

import java.util.ArrayList;
import java.util.Set;


public class Act extends UnityPlayerActivity
{
    static public BluetoothAdapter bt;
    static public int i = 0;



    static public int TestAddNum()
    {
        i += 1;
        ShowToast("i is now" + i);
        return i;
    }

    static public void ShowToast(final String content)//傳入的參入必須為final，才可讓Runnable()內部使用
    {
        UnityPlayer.currentActivity.runOnUiThread(new Runnable()
        {
            @Override
            public void run()
            {
                Toast.makeText(UnityPlayer.currentActivity, content, Toast.LENGTH_SHORT).show();
            }
        });
    }

    static public void BtTurnOnAndStartScan()
    {
        i = 8787;
        bt = BluetoothAdapter.getDefaultAdapter();
        if (!bt.isEnabled())
            bt.enable();
        bt.startDiscovery();
    }
    /*
    public boolean BtTryConnectToKart()
    {
        bluetooth.connectToName("DualWheelRoller");
        if(bluetooth.isConnected())
            return true;
        else
            return false;
    }

    public void BtSendMessage(String message)
    {
        bluetooth.send(message);
    }
    */
}

