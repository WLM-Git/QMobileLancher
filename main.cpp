#include <QApplication>
#include "wlmwindowwidget.h"

int main(int argc, char *argv[])
{
    //1个qt像素=0.5逻辑像素=1物理像素
    qputenv("QT_SCALE_FACTOR", "0.5");
    QApplication a(argc, argv);

    WLMWindowWidget windowWidget;
    windowWidget.show();

    return a.exec();
}
