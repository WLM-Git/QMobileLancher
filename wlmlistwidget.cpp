#include "wlmlistwidget.h"
#include <QMouseEvent>

WLMListWidget::WLMListWidget(QWidget* parent) : QListWidget(parent)
{
    setAttribute(Qt::WA_MacShowFocusRect,0);
}

void WLMListWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_dragPoint = event->pos();
        m_dragItem = this->itemAt(event->pos());
        emit hideDeleteButtonSignal();
    }

}

void WLMListWidget::mouseMoveEvent(QMouseEvent* event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        QPoint diffPoints = event->pos() - m_dragPoint;
        if(diffPoints.x() < -80)
        {
            if(m_dragItem!=nullptr)
                emit showDeleteItemSignal(m_dragItem);
        }
        else
            emit hideDeleteButtonSignal();
    }
}
