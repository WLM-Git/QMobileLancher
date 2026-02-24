#ifndef WLMLISTWIDGET_H
#define WLMLISTWIDGET_H

#include <QListWidget>

class WLMListWidget : public QListWidget
{
    Q_OBJECT
public:
    WLMListWidget(QWidget* parent = 0);
protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
private:
    //开始拖拽的点
    QPoint m_dragPoint;
    //拖拽的项
    QListWidgetItem* m_dragItem;
signals:
    void showDeleteItemSignal(QListWidgetItem* item);
    void hideDeleteButtonSignal();
};

#endif // WLMLISTWIDGET_H
