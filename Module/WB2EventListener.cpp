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
//���õ�ʱ��  Ҫ�Ȼ�ȡ IWebBrowser2* pWeb;
//
//Ȼ��
//
//IConnectionPointContainer* pCPC = NULL;
//IConnectionPoint* pCP = NULL;
//DWORD dwCookie = 0;
//
//pWeb->QueryInterface(IID_IConnectionPointContainer, (void**)&pCPC);
//pCPC->FindConnectionPoint(DIID_DWebBrowserEvents2, &pCP);
//WebBrwoser2EventListener* pEventListener = new WebBrwoser2EventListener;
//pCP->Advise((IUnknown*)(void*)pEventListener, &dwCookie);
//������  ���Ѿ����Դ� pWeb ������ļ����¼���

//pCP->Unadvise(dwCookie); //ʹ����ɺ�Ҫִ�����
//delete pEventListener;
