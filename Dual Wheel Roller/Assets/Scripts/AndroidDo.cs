﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AndroidDo : MonoBehaviour
{
    AndroidJavaClass jc;
    AndroidJavaObject jo;

    static public AndroidDo instance{ get {return GameObject.Find("AndroidDo").GetComponent<AndroidDo>();}}
    
    void Start()
    {
        if(!GameObject.Find("AndroidDo"))
		{
			gameObject.name = "AndroidDo";
            DontDestroyOnLoad(gameObject);
			//Debug.Log("AndroidDo not exist! Now making.");
		}
		else
		{
			Debug.Log("AndroidDo exist! Now deleting new one.");
            Destroy(gameObject);
            return;
		}
        jc = new AndroidJavaClass ("JCxYIS.KartGen3.Act");
        jo = jc.GetStatic<AndroidJavaObject>("currentActivity");
    }

    /// <summary>
    /// 使用Toast
    /// </summary>
    public void makeText(string message)
    {
        //第一個參數為要呼叫的Method名稱
        jc.CallStatic("ShowToast", message);
    }
    /// <summary>
    /// 測試AddNum
    /// </summary>
    public int AddNum()
    {
        int i = jc.CallStatic<int> ("TestAddNum");
        return i;
    }
    /// <summary>
    /// open bt
    /// </summary>
    public void OpenBt()
    {
        jc.Call("BtTurnOnAndStartScan");
    }
}
