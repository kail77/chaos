���뻷����WDK7600
From Unidriver, oemui + bitmap sample.

oemui: ����DocProp-Adv, �Զ���ѡ�ͼ���ʽbmp/tif;
  DocProp: Image����ҳ,ѡ��
  OemDevmode: ͼ���ʽiImageFormat, szOutputDir���·��

oemdrv: ���ļ�����ҳ�����(ѹ��tiff)
  EnablePDEV: ��ʼ���ͱ���OemDevmode->PDEV
  ����ԭ��ʽ��ImageProcessing: �����ڴ棬����ͼ�����ݣ�OemEndDoc: �����ļ�
  OemStartPage: ��ʼ��ͼ��Ϊ��ɫ��
  OemSendPage: ��ҳ�����ļ���ע��SendPage����ImageProcessing.
