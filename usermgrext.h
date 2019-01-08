#ifndef _USERMGREXT_H
#define _USERMGREXT_H

#ifdef _AFXEXT
	// this is only used when building this Extension DLL..  Force the define
	#ifndef _FUN_AFXDLL
		#define _FUN_AFXDLL
	#endif
#endif

////////////////////////////////////////////////////////////
// This section is meaningless when Exporting by ordinals
#ifdef _FUN_AFXDLL
	// When building HVWNT as a MFC Extension DLL
	#ifdef _USERMGR
		#define USERMGR_EXT_CLASS	AFX_CLASS_EXPORT
		#define USERMGR_EXT_DATA		AFX_DATA_EXPORT
	#else
		#define USERMGR_EXT_CLASS	AFX_CLASS_IMPORT
		#define USERMGR_EXT_DATA		AFX_DATA_IMPORT
	#endif	
#else
	#define USERMGR_EXT_CLASS	
	#define USERMGR_EXT_DATA    
#endif

#ifndef _USERMGR
	#ifdef _AFXDLL
	#   pragma comment(lib, "usermanagerd")
	#else
	#   pragma comment(lib, "usermanager")
	#endif
#endif

#endif