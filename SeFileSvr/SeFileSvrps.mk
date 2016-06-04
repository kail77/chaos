
SeFileSvrps.dll: dlldata.obj SeFileSvr_p.obj SeFileSvr_i.obj
	link /dll /out:SeFileSvrps.dll /def:SeFileSvrps.def /entry:DllMain dlldata.obj SeFileSvr_p.obj SeFileSvr_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del SeFileSvrps.dll
	@del SeFileSvrps.lib
	@del SeFileSvrps.exp
	@del dlldata.obj
	@del SeFileSvr_p.obj
	@del SeFileSvr_i.obj
