#pragma once

#include "OAIdl.h"
#include <ExDispid.h>
#include <ExDisp.h>

class CWB2EventListener : public IDispatch
{
public:
	CWB2EventListener();
	~CWB2EventListener();
private:
	void _stdcall BeforeNavigate2(IDispatch *pDisp, VARIANTARG &URL, VARIANTARG &Flags, VARIANTARG &TargetFrameName,
		VARIANTARG &PostData, VARIANTARG &Headers, BOOL &Cancel);
	void _stdcall DocumentComplete(IDispatch *pDisp, VARIANTARG &URL);
	void _stdcall DownloadBegin();
	void _stdcall DownloadComplete();
	void _stdcall ProgressChange(int Progress, int ProgressMax);
	void _stdcall NewWindow3(VARIANT_BOOL* Cannel, BSTR url);

public: // IDispatch methods
	STDMETHOD(QueryInterface)(REFIID riid, void **ppvObject)
	{
		HRESULT hr = E_NOINTERFACE;
		if (riid == __uuidof(IDispatch))
		{
			*ppvObject = (IDispatch*)this;
			AddRef();
			hr = S_OK;
		}
		else if (riid == __uuidof(DWebBrowserEvents2))
		{
			*ppvObject = (IDispatch*)this;     // DWebBrowserEvents2*
			AddRef();
			hr = S_OK;
		}

		return hr;
	}
	STDMETHODIMP_(ULONG) AddRef(void)
	{
		return 1;
	};
	STDMETHODIMP_(ULONG) Release(void)
	{
		return 1;
	}
	STDMETHOD(GetTypeInfoCount)(UINT*)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(GetTypeInfo)(UINT, LCID, ITypeInfo**)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(GetIDsOfNames)(REFIID, LPOLESTR *rgszNames, UINT, LCID, DISPID *rgDispId)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(Invoke)(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS FAR* pDispParams, VARIANT FAR* pVarResult, EXCEPINFO FAR* pExcepInfo, unsigned int FAR* puArgErr)
	{
		HRESULT hr = S_OK;

		if (dispIdMember == DISPID_BEFORENAVIGATE2)
		{
			//BOOL Cancel = false;
			//IDispatch *pDisp = pDispParams->rgvarg[6].pdispVal;
			//VARIANTARG URL = VARIANTARG(pDispParams->rgvarg[5].pvarVal->bstrVal);
			//VARIANTARG Flags = VARIANTARG(pDispParams->rgvarg[4].pvarVal->bstrVal);
			//VARIANTARG TargetFrameName = VARIANTARG(pDispParams->rgvarg[3].pvarVal->bstrVal);
			//VARIANTARG PostData = VARIANTARG(pDispParams->rgvarg[2].pvarVal->bstrVal);
			//VARIANTARG Headers = VARIANTARG(pDispParams->rgvarg[1].pvarVal->bstrVal);
			//BeforeNavigate2(pDisp, URL, Flags, TargetFrameName, PostData, Headers, Cancel);
			//*pDispParams->rgvarg[0].pboolVal = Cancel ? TRUE : FALSE;
		}
		if (dispIdMember == DISPID_DOCUMENTCOMPLETE)
		{
			//VARIANTARG URL = VARIANTARG(pDispParams->rgvarg[0].pvarVal->bstrVal);
			//DocumentComplete(pDispParams->rgvarg[1].pdispVal, URL);
		}
		if (dispIdMember == DISPID_DOWNLOADBEGIN)
		{
			DownloadBegin();
		}
		if (dispIdMember == DISPID_DOWNLOADCOMPLETE)
		{
			DownloadComplete();
		}
		if (dispIdMember == DISPID_PROGRESSCHANGE)
		{
			ProgressChange(pDispParams->rgvarg[1].lVal, pDispParams->rgvarg[0].lVal);
		}
		if (dispIdMember == DISPID_NEWWINDOW3)
		{
			NewWindow3((pDispParams->rgvarg[3].pboolVal), (pDispParams->rgvarg->bstrVal));
		}

		return hr;
	}
};

