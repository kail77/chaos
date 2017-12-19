testdll xxmod.dll funcname1 strParam1 *int=4 *pint=1 *str16=hello *byte6=1a2b3c4d5e6f

icce17cdc: AES(Rijndael) ECB,keybit=256(32bytes),Padding=' '
testdll icce17cdc.dll IccEncryptFile Qk/yxNCPeuXij39UClMSkuVBKahWqQwH cdjob.zip cdjob1.dat
testdll icce17cdc.dll IccDecryptFile Qk/yxNCPeuXij39UClMSkuVBKahWqQwH cdjob.dat cdjob.zip

testdll ICCE17CDC.dll EncryptData Qk/yxNCPeuXij39UClMSkuVBKahWqQwH plaintext16bytes *byte16=00 *int=16
  testso:ret=0 7655A011CC84BE8EE15045D032988E42
testdll ICCE17CDC.dll DecryptData Qk/yxNCPeuXij39UClMSkuVBKahWqQwH *byte16=7655A011CC84BE8EE15045D032988E42 *str32=x *int=16
  testso:ret=0 7655A011CC84BE8EE15045D032988E42 plaintext16bytes
