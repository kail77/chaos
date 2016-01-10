编译环境：WDK7600
From Unidriver, oemui + bitmap sample.

oemui: 增加DocProp-Adv, 自定义选项—图像格式bmp/tif;
  DocProp: Image属性页,选择
  OemDevmode: 图像格式iImageFormat, szOutputDir输出路径

oemdrv: 按文件名分页输出，(压缩tiff)
  EnablePDEV: 初始化和保存OemDevmode->PDEV
  废弃原方式：ImageProcessing: 分配内存，保存图像数据；OemEndDoc: 保存文件
  OemStartPage: 初始化图像为白色；
  OemSendPage: 按页保存文件。注意SendPage早于ImageProcessing.
