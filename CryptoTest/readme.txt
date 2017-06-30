AES加密算法，CBC-Mode, UTF8格式，key_len=32,iv_len=16, PKCS7-Padding

CryptoCppTest: 调用cryptopp.dll Crypto++ 支持多种加解密算法，RSA,DES,AES(ECB,CBC,CFB,OFB,CTR: 5modes)... 但在XP无法运行？
CryptoCsTest: C# encrypt lib UTF8编码
CryptoTest: C++ Rijndael 源代码(AES只是其中的一个特例)
SparseCode: 文件稀疏加密，对文件的内容部分加密，使其内容改变，不被识别。

CryptoCsTest: C#-RSA
非对称，密文比原数据长，速度较慢。使用公钥加密数据，私钥解密。使用私钥签名数据，公钥验证签名，不能加解密数据？

CryptoCsTest: C#-ECC(ECDiffieHellman)
非对称加密，比RSA强度高，速度快。密文与原数据等长，16字节对齐。
该加密的模式为，A-B双方各自创建ECDiffieHellmanCng/Aes加密对象，并交换公钥pubkeyA,pubkeyB/aes.IV_A,aes.IV_B，各自产生keyA/keyB.
A加密数据后，传输密文给B, B使用keyB,IV_A解密；B加密数据时，A使用keyA,IV_B解密。

