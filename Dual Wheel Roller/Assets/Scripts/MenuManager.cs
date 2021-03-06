﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class MenuManager : MonoBehaviour {
	[SerializeField]private Text tiptext, ver;

	
	void Start()
	{
		AndroidDo.instance.CloseBt();
		if(ver != null)
			ver.text = GameManager.version;
	}
	public void GoScene(string scene)
	{
		Debug.Log("GO "+scene);
		StartCoroutine(SwitchToScene(scene));
	}
	IEnumerator SwitchToScene(string scene)
	{
		AsyncOperation async = SceneManager.LoadSceneAsync(scene);
		while(!async.isDone)
		{
			tiptext.text = string.Format("Now loading: {0}%",async.progress*100);
			yield return false;
		}
		yield return true;
	}
}
