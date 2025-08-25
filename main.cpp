// main.cpp 
#include "QuickMeme.h"
#include <QtWidgets/QApplication>


// 用来启动各个模块
// 1.QT 模块
// 2.Python OCR 模块
// 3.
int main(int argc, char* argv[])
{
    //QT部分
    QApplication a(argc, argv);
    // 重要设置：防止关闭最后一个窗口时退出程序
    QApplication::setQuitOnLastWindowClosed(false);

    QuickMeme w;

    return a.exec();
}
