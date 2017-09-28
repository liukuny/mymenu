#include "WB2EventListener.h"


CWB2EventListener::CWB2EventListener()
{
}


CWB2EventListener::~CWB2EventListener()
{
}

void _stdcall CWB2EventListener::BeforeNavigate2(IDispatch *pDisp, VARIANTARG &URL, VARIANTARG &Flags, VARIANTARG &TargetFrameName, VARIANTARG &PostData, VARIANTARG &Headers, BOOL &Cancel)
{
	//Form1->Memo1->Lines->Add(URL.bstrVal);
	//Form1->Memo1->Lines->Add(Headers.bstrVal);
	//Cancel=true;
}
//---------------------------------------------------------------------------
void _stdcall CWB2EventListener::DocumentComplete(IDispatch *pDisp, VARIANTARG &URL)
{
	IWebBrowser2 *po = (IWebBrowser2 *)pDisp;
	//Form1->Memo1->Lines->Add(po->LocationName);
	//Form1->Memo1->Lines->Add(URL.bstrVal);
}
//---------------------------------------------------------------------------
void _stdcall CWB2EventListener::DownloadBegin()
{
	//
}
//---------------------------------------------------------------------------
void _stdcall CWB2EventListener::DownloadComplete()
{
	//
}
//---------------------------------------------------------------------------
void _stdcall CWB2EventListener::ProgressChange(int Progress, int ProgressMax)
{
	//Form1->Memo1->Lines->Add((String)Progress+"  "+(String)ProgressMax);    //TEST
}
//---------------------------------------------------------------------------
void _stdcall CWB2EventListener::NewWindow3(VARIANT_BOOL* Cannel, BSTR url)
{
}

//
//
//调用的时候  要先获取 IWebBrowser2* pWeb;
//
//然后
//
//IConnectionPointContainer* pCPC = NULL;
//IConnectionPoint* pCP = NULL;
//DWORD dwCookie = 0;
//
//pWeb->QueryInterface(IID_IConnectionPointContainer, (void**)&pCPC);
//pCPC->FindConnectionPoint(DIID_DWebBrowserEvents2, &pCP);
//WebBrwoser2EventListener* pEventListener = new WebBrwoser2EventListener;
//pCP->Advise((IUnknown*)(void*)pEventListener, &dwCookie);
//到这里  就已经可以从 pWeb 捕获定义的几个事件了

//pCP->Unadvise(dwCookie); //使用完成后要执行这个
//delete pEventListener;
