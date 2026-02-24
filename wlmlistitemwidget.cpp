#include "wlmlistitemwidget.h"
#include <QGridLayout>
#define LISTITEMWIDGET_WIDTH 376
#define LISTITEMWIDGET_HEIGHT 90
#define DELETEBUTTON_WIDTH 145
#define DELETEBUTTON_HEIGHT 90


WLMListItemWidget::WLMListItemWidget(QWidget *parent)
    : QWidget{parent}
{
    LoadLayout();
}

void WLMListItemWidget::LoadLayout()
{
    m_pInfoWidget = new QWidget(this);
    m_pInfoWidget->setAutoFillBackground(true);
    m_pInfoWidget->setGeometry(0,0,LISTITEMWIDGET_WIDTH,LISTITEMWIDGET_HEIGHT);

    QGridLayout* pLayout = new QGridLayout(m_pInfoWidget);
    pLayout->setVerticalSpacing(1);
    pLayout->setContentsMargins(5,5,5,5);

    m_pPictureLabel = new QLabel(this);
    m_pPictureLabel->setFixedSize(QSize(90,90));

    m_pTitleLabel = new QLabel(this);
    m_pTitleLabel->setFont(QFont("Arial-Bold",25,50));

    m_pDetailsLabel = new QLabel(this);
    m_pDetailsLabel->setFont(QFont("Arial-Bold",15,50));

    pLayout->addWidget(m_pPictureLabel,0,0,2,1);
    pLayout->addWidget(m_pTitleLabel,0,1,Qt::AlignLeft);
    pLayout->addWidget(m_pDetailsLabel,1,1,Qt::AlignLeft);

    m_pInfoWidget->setLayout(pLayout);

    m_pDeleteButton = new QPushButton(this);
    m_pDeleteButton->setFixedSize(QSize(DELETEBUTTON_WIDTH,DELETEBUTTON_HEIGHT));
    m_pDeleteButton->setIcon(QIcon(":/ImageResources/img_delete.png"));
    m_pDeleteButton->setIconSize(QSize(DELETEBUTTON_WIDTH,DELETEBUTTON_HEIGHT));
    m_pDeleteButton->setAutoFillBackground(true);
    m_pDeleteButton->setFlat(true);
    m_pDeleteButton->setStyleSheet("QPushButton{background: transparent}");
    m_pDeleteButton->setGeometry(LISTITEMWIDGET_WIDTH-DELETEBUTTON_WIDTH,0,DELETEBUTTON_WIDTH,DELETEBUTTON_HEIGHT);
    m_pDeleteButton->setHidden(true);

    connect(m_pDeleteButton,&QPushButton::clicked,this,&WLMListItemWidget::onDeleteButtonSelected);
}

void WLMListItemWidget::ShowDeleteButton()
{
    if(m_pInfoWidget==nullptr)
        return;
    m_pInfoWidget->setGeometry(-DELETEBUTTON_WIDTH,0,LISTITEMWIDGET_WIDTH,LISTITEMWIDGET_HEIGHT);
    m_pDeleteButton->setHidden(false);
}

void WLMListItemWidget::HideDeleteButton()
{
    m_pInfoWidget->setGeometry(0,0,LISTITEMWIDGET_WIDTH,LISTITEMWIDGET_HEIGHT);
    m_pDeleteButton->setHidden(true);
}

void WLMListItemWidget::onDeleteButtonSelected()
{
    emit OnDeleteButtonClickdedSignal();
}

void WLMListItemWidget::SetPictureImage(QString picstr)
{
    QPixmap pixmap = QPixmap(picstr);
    if(m_pPictureLabel == nullptr || pixmap.isNull())
        return;
    //使pixmap变成m_pPictureLabel的尺寸并忽略其原有的宽高比，并设置平滑模式使得边缘更加平滑
    m_pPictureLabel->setPixmap(pixmap.scaled(m_pPictureLabel->width(),m_pPictureLabel->height(),Qt::IgnoreAspectRatio,Qt::TransformationMode::SmoothTransformation));
}

void WLMListItemWidget::SetItemIitle(QString nametitle)
{
    if(m_pTitleLabel == nullptr || nametitle.isNull())
        return;
    m_pTitleLabel->setText(nametitle);
}

void WLMListItemWidget::SetPersonDetails(QString personDetails)
{
    if(m_pDetailsLabel == nullptr || personDetails.isNull())
        return;
    m_pDetailsLabel->setText(personDetails);
}


