#ifndef WLMWINDOWWIDGET_H
#define WLMWINDOWWIDGET_H

#include <QWidget>
#include "wlmlistwidget.h"
#include "wlmlistitemcontent.h"

class WLMWindowWidget : public QWidget
{
    Q_OBJECT
public:
    //这是一个自定义的widget，要求无边框
    explicit WLMWindowWidget(QWidget *parent = nullptr);

private:
    QPixmap m_bgPixMap;
    QListWidgetItem* m_currentWidgetItem;

private:
    void loadListWidget();
    void loadContents();
    void OnAddButtonClicked();
protected:
    void paintEvent(QPaintEvent* event);
    WLMListWidget* m_pListWidget;
    QList<WLM_ListitemContent*> m_contentList;
private slots:
    void OnShowDeleteItemEvent(QListWidgetItem* selectedItem);
    void OnHideDeleteButtonEvent();
    void OnDeleteItemWidgetButtonClicked();
signals:
};

#endif // WLMWINDOWWIDGET_H
