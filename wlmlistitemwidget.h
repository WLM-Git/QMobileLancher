#ifndef WLMLISTITEMWIDGET_H
#define WLMLISTITEMWIDGET_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>

//用以替代原生的QListItem
class WLMListItemWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WLMListItemWidget(QWidget *parent = nullptr);

public:
    void LoadLayout();
    void ShowDeleteButton();
    void HideDeleteButton();
    void onDeleteButtonSelected();
    void SetPictureImage(QString);
    void SetItemIitle(QString);
    void SetPersonDetails(QString);
private:
    QLabel *m_pPictureLabel;
    QLabel *m_pTitleLabel;
    QLabel *m_pDetailsLabel;

    QWidget* m_pInfoWidget;

    QPushButton* m_pDeleteButton;

signals:
    void OnDeleteButtonClickdedSignal();
};

#endif // WLMLISTITEMWIDGET_H
