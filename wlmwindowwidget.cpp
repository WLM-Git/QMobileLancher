#include "wlmwindowwidget.h"
#include "wlmlistitemcontent.h"
#include "wlmlistitemwidget.h"
#include <QPainter>
#include <QScreen>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTime>
#include <QRandomGenerator>

WLMWindowWidget::WLMWindowWidget(QWidget *parent)
    : QWidget{parent}
{
    //独立顶层窗口|无边框|可最小化
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
    //自动填充背景
    setAutoFillBackground(true);
    //背景透明
    setAttribute(Qt::WA_TranslucentBackground);

    //加载窗口背景图片
    m_bgPixMap.load(":/ImageResources/img_background.png");

    //获取主屏幕对象
    QScreen* screen = QGuiApplication::primaryScreen();

    //获取屏幕的可用尺寸
    QRect screenGeometry = screen->availableGeometry();

    //计算widget居中
    int startX = (screenGeometry.width() - m_bgPixMap.width()) / 2;
    int startY = (screenGeometry.height() - m_bgPixMap.height()) / 2;
    //设置widget居中并设置widget尺寸
    setGeometry(startX,startY,m_bgPixMap.width(),m_bgPixMap.height());

    loadListWidget();
    loadContents();
}

void WLMWindowWidget::loadListWidget()
{
    //整体布局
    QVBoxLayout* pVBoxLayout = new QVBoxLayout(this);
    pVBoxLayout->setContentsMargins(28, 70, 32, 55);
    pVBoxLayout->setSpacing(0);

    //顶部工具栏
    QHBoxLayout* pHBoxLayout = new QHBoxLayout();
    pHBoxLayout->setContentsMargins(0,0,10,10);
    pHBoxLayout->setSpacing(0);

    //顶部工具栏的添加按钮
    QPushButton* addItemButton = new QPushButton();
    addItemButton->setIcon(QIcon(":/ImageResources/img_add.png"));
    addItemButton->setIconSize(QSize(25,25));
    addItemButton->setFixedSize(QSize(25,25));
    addItemButton->setAutoFillBackground(true);
    addItemButton->setFlat(true);
    addItemButton->setStyleSheet("QPushButton{background: transparent;}");

    connect(addItemButton,&QPushButton::clicked,this,&WLMWindowWidget::OnAddButtonClicked);

    //顶部工具栏的弹簧
    pHBoxLayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::MinimumExpanding,QSizePolicy::Fixed));
    pHBoxLayout->addWidget(addItemButton);

    pVBoxLayout->addLayout(pHBoxLayout);

    //下部窗口
    m_pListWidget = new WLMListWidget(this);
    m_pListWidget->setFocusPolicy(Qt::NoFocus);             //无焦点
    m_pListWidget->setCursor(Qt::ArrowCursor);              //鼠标指针为箭头模式

    m_pListWidget->setStyleSheet("QListWidget::item{background: transparent;}");

    connect(m_pListWidget,&WLMListWidget::showDeleteItemSignal,this,&WLMWindowWidget::OnShowDeleteItemEvent);
    connect(m_pListWidget,&WLMListWidget::hideDeleteButtonSignal,this,&WLMWindowWidget::OnHideDeleteButtonEvent);

    pVBoxLayout->addWidget(m_pListWidget);

    setLayout(pVBoxLayout);
}

//
void WLMWindowWidget::loadContents()
{
    WLM_ListitemContent* content_p0 = new WLM_ListitemContent;
    content_p0->picturePath = ":/ImageResources/img_p0.png";
    content_p0->nameTitle = "库克";
    content_p0->personDetails = "蒂姆库克,苹果公司CEO,帮助乔布斯把苹果打造成全球最高市值公司的大神.";
    m_contentList.append(content_p0);

    WLM_ListitemContent* content_p1 = new WLM_ListitemContent;
    content_p1->picturePath = ":/ImageResources/img_p1.png";
    content_p1->nameTitle = "章子怡";
    content_p1->personDetails = "章子怡，著名演员，曾经出演过著名的电影，英雄，获得最佳女配角.";
    m_contentList.append(content_p1);

    WLM_ListitemContent* content_p2 = new WLM_ListitemContent;
    content_p2->picturePath = ":/ImageResources/img_p2.png";
    content_p2->nameTitle = "汪峰";
    content_p2->personDetails = "汪峰，著名音乐家，写过很多非常流行的歌曲，比如春天里，怒放的青春.";
    m_contentList.append(content_p2);

    WLM_ListitemContent *content_p3= new WLM_ListitemContent();
    content_p3->picturePath=":/ImageResources/img_p3.png";
    content_p3->nameTitle= "赵薇";
    content_p3->personDetails ="赵薇，著名演员，2000年内地四小花旦之一，琼瑶最喜欢的女郎。";
    m_contentList.append(content_p3);

    WLM_ListitemContent *content_p4= new WLM_ListitemContent();
    content_p4->picturePath=":/ImageResources/img_p4.png";
    content_p4->nameTitle= "王力宏";
    content_p4->personDetails ="王力宏，著名音乐人，出生于美国，毕业于名校，非常好的音乐才华，天赋";
    m_contentList.append(content_p4);

    WLM_ListitemContent *content_p5= new WLM_ListitemContent();
    content_p5->picturePath=":/ImageResources/img_p5.png";
    content_p5->nameTitle= "任泉";
    content_p5->personDetails ="任泉，著名演员，参与了当年非常火爆的电视剧，少年包青天，出演公孙策一角色";
    m_contentList.append(content_p5);

    WLM_ListitemContent *content_p6= new WLM_ListitemContent();
    content_p6->picturePath=":/ImageResources/img_p6.png";
    content_p6->nameTitle= "秦岚";
    content_p6->personDetails ="秦岚，著名演员，曾经与陈道明一起出演火爆电视剧，楚汉争霸，饰演吕雉，出神入化。";
    m_contentList.append(content_p6);
}

//添加项到m_contentList中
void WLMWindowWidget::OnAddButtonClicked()
{
    //从7张人物数据库中随机选取一张添加到m_contentList中
    int rand_num = QRandomGenerator::global()->bounded(7);
    qDebug()<<rand_num<<Qt::endl;
    if(rand_num>=0 && rand_num<=6)
    {
        //取出m_contentList的一个元素
        WLM_ListitemContent* content = m_contentList.at(rand_num);

        //根据content，得到m_pListWidget的项，然后将其放入其中
        if(content!=nullptr)
        {
            QListWidgetItem* listWidgetItem = new QListWidgetItem(m_pListWidget);
            listWidgetItem->setSizeHint(QSize(0,90));

            //new一个WLMListItemWidget对象
            WLMListItemWidget* itemWidget = new WLMListItemWidget();
            itemWidget->SetPictureImage(content->picturePath);
            itemWidget->SetItemIitle(content->nameTitle);
            itemWidget->SetPersonDetails(content->personDetails);

            connect(itemWidget,&WLMListItemWidget::OnDeleteButtonClickdedSignal,this,&WLMWindowWidget::OnDeleteItemWidgetButtonClicked);

            m_pListWidget->addItem(listWidgetItem);
            m_pListWidget->setItemWidget(listWidgetItem,itemWidget);
        }
    }
}

void WLMWindowWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);

    p.drawPixmap(rect(),m_bgPixMap);
}

void WLMWindowWidget::OnShowDeleteItemEvent(QListWidgetItem *selectedItem)
{
    //如果item为空，则说明没有选中的项
    if(selectedItem == nullptr)
    {
        qDebug()<<"ERROR...selectedItem NULL"<<Qt::endl;
        return;
    }
    WLMListItemWidget* itemWidget = (WLMListItemWidget*) m_pListWidget->itemWidget(selectedItem);
    if(itemWidget == nullptr)
    {
        qDebug()<<"ERROR...itemWidget NULL"<<Qt::endl;
        return;
    }
    itemWidget->ShowDeleteButton();

    m_currentWidgetItem = selectedItem;
}

void WLMWindowWidget::OnHideDeleteButtonEvent()
{
    //将所有的项都做判断，如果其存在则将其删除按钮隐藏
    if(m_pListWidget == nullptr)
        return;
    for(int i = 0; i < m_pListWidget->count(); i++)
    {
        QListWidgetItem* item = m_pListWidget->item(i);
        if(item != nullptr)
        {
            WLMListItemWidget* itemWidget = (WLMListItemWidget*) m_pListWidget->itemWidget(item);
            if(itemWidget != nullptr)
                itemWidget->HideDeleteButton();
        }
    }
}

void WLMWindowWidget::OnDeleteItemWidgetButtonClicked()
{
    if(m_currentWidgetItem == nullptr)
        return;

    WLMListItemWidget* itemWidget = (WLMListItemWidget*)m_pListWidget->itemWidget(m_currentWidgetItem);

    //将itemWidget移出m_currentWidgetItem
    m_pListWidget->removeItemWidget(m_currentWidgetItem);

    if(itemWidget != nullptr)
    {
        delete itemWidget;
    }

    //将m_currentWidgetItem移出m_pListWidget
    int row = m_pListWidget->row(m_currentWidgetItem);
    m_pListWidget->takeItem(row);

    delete m_currentWidgetItem;
    m_currentWidgetItem = nullptr;
}
