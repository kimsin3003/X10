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

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.R;
import android.annotation.TargetApi;
import android.graphics.Color;
import android.graphics.Point;
import android.os.Build;
import android.os.Bundle;
import android.view.Display;
import android.view.View;
import android.view.WindowManager;
import android.widget.LinearLayout;

import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdListener;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdView;
import com.google.android.gms.ads.InterstitialAd;

public class AppActivity extends Cocos2dxActivity 
{
	private static final String AD_UNIT_ID = "ca-app-pub-1690383002847701/2009330075";
	private InterstitialAd mInterstitialAd;
	private static AppActivity _appActivity;
	private static AdRequest mAdReq;
	
	@Override
	protected void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		
		mInterstitialAd = new InterstitialAd(this);
	    mInterstitialAd.setAdUnitId(AD_UNIT_ID);
		

	    AdRequest adRequest = new AdRequest.Builder()
	    		.addTestDevice(AdRequest.DEVICE_ID_EMULATOR)
	    		.addTestDevice("717495186B4955BDA7D6A6B644CB1D72") //MC's Luna phone
	    		.addTestDevice("8F7E2107BC04D9292482870C9BC1CDB0") //JW's G2 phone
	    		.build();
	    mAdReq = adRequest;
	    mInterstitialAd.loadAd(adRequest);
	    
	    mInterstitialAd.setAdListener(new AdListener(){
			@Override
			public void onAdClosed() {
			    mInterstitialAd.loadAd(mAdReq);
			}
		});
	    
	    _appActivity = this;
	    
	} 
	
	public static void showAd()
	{
		_appActivity.runOnUiThread(new Runnable() {
			
			@Override
			public void run() {
				if(_appActivity.mInterstitialAd.isLoaded())
					_appActivity.mInterstitialAd.show();
				
			}
		});	
	}
	
	public static void hideAd()
	{
		
	}
	
	
//	private static AppActivity _appActivity;
//	private InterstitialAd mInterstitialAd;
//	private static final String AD_UNIT_ID = "ca-app-pub-1690383002847701/2009330075";
//
//	
//	@Override
//	protected void onCreate(Bundle savedInstanceState)
//	{
//		super.onCreate(savedInstanceState);
//
//		_appActivity.runOnUiThread(new Runnable() {	
//			@Override
//			public void run() {
//				// TODO Auto-generated method stub
//
//				mInterstitialAd.setAdUnitId(AD_UNIT_ID);
//				mInterstitialAd.setAdListener(new AdListener(){
//					@Override
//					public void onAdClosed() {
//						requestNewInterstitial();
//					}
//				});
//				
//						
//			}
//		});
//		
//		requestNewInterstitial();
//
//		_appActivity = this;
//		
//	}
//	
//	
//	public static void hideAd()    
//	{
//	     _appActivity.runOnUiThread(new Runnable()
//	     {
//		     @Override
//		     public void run()
//		     {
//		    	 
//		     }
//	     });
//	}
//	
//	
//	public static void showAd()
//	{
//		_appActivity.runOnUiThread(new Runnable()
//		{
//			 @Override
//			 public void run()
//			 {	
//				if(_appActivity.mInterstitialAd.isLoaded())
//					_appActivity.mInterstitialAd.show();	
//			 }
//	     });
//	}
//	
//	private void requestNewInterstitial() {
//		_appActivity.runOnUiThread(new Runnable() {
//			@Override
//			public void run() {
//				// TODO Auto-generated method stub
//
//		        AdRequest adRequest = new AdRequest.Builder()
//		        		.addTestDevice(AdRequest.DEVICE_ID_EMULATOR)
//		        		.addTestDevice("717495186B4955BDA7D6A6B644CB1D72") //MC's Luna phone
//		        		.addTestDevice("8F7E2107BC04D9292482870C9BC1CDB0") //JW's G2 phone
//		        		.build();
//
//		        mInterstitialAd.loadAd(adRequest);
//			}
//		});			
//	}
//	
//
//	@Override
//	protected void onResume() 
//	{
//		super.onResume();
//		if (mInterstitialAd != null) 
//		{
//
//		}
//	}
//	
//	@Override
//	protected void onPause() 
//	{
//		if (mInterstitialAd != null) 
//		{
//			
//		}
//		super.onPause();
//	}
//	
//    @Override
//    protected void onDestroy() 
//    {
//        super.onDestroy();
//    }
//	
}
