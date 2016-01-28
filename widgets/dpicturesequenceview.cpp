#include "dpicturesequenceview.h"
#include "private/dpicturesequenceview_p.h"

#include <QGraphicsPixmapItem>

DUI_BEGIN_NAMESPACE

DPictureSequenceViewPrivate::DPictureSequenceViewPrivate(DPictureSequenceView *q) :
    DObjectPrivate(q)
{

}

void DPictureSequenceViewPrivate::init()
{
    D_Q(DPictureSequenceView);

    m_scene = new QGraphicsScene(q);
    m_refreshTimer = new QTimer(q);
    m_refreshTimer->setInterval(33);
    m_refreshTimer->start();

    q->setScene(m_scene);
    q->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    q->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    q->connect(m_refreshTimer, &QTimer::timeout, [this] {refreshPicture();});
}

void DPictureSequenceViewPrivate::play()
{
    m_refreshTimer->start();
}

void DPictureSequenceViewPrivate::setPictureSequence(const QStringList &sequence)
{
    for (const QString &pic : sequence)
        addPicture(QPixmap(pic));
}

int DPictureSequenceViewPrivate::speed() const
{
    return m_refreshTimer->interval();
}

void DPictureSequenceViewPrivate::setSpeed(int speed)
{
    m_refreshTimer->setInterval(speed);
}

bool DPictureSequenceViewPrivate::singleShot() const
{
    return m_singleShot;
}

void DPictureSequenceViewPrivate::setSingleShot(bool singleShot)
{
    m_singleShot = singleShot;
}

void DPictureSequenceViewPrivate::refreshPicture()
{
    m_pictureList[m_lastItemPos++]->hide();

    if (m_lastItemPos == m_pictureList.count())
    {
        m_lastItemPos = 0;

        if (m_singleShot)
            m_refreshTimer->stop();

        D_QC(DPictureSequenceView);

        emit q->playEnd();
    }

    m_pictureList[m_lastItemPos]->show();
}

void DPictureSequenceViewPrivate::addPicture(const QPixmap &pixmap)
{
    QGraphicsPixmapItem *item = m_scene->addPixmap(pixmap);
    item->hide();
    m_pictureList.append(item);
}

DPictureSequenceView::DPictureSequenceView(QWidget *parent) :
    QGraphicsView(parent),
    DObject(*new DPictureSequenceViewPrivate(this))
{
    D_D(DPictureSequenceView);

    d->init();
}

void DPictureSequenceView::setPictureSequence(const QStringList &sequence)
{
    D_D(DPictureSequenceView);

    d->setPictureSequence(sequence);

    setStyleSheet("background-color:transparent;");
}

void DPictureSequenceView::play()
{
    D_D(DPictureSequenceView);

    d->play();
}

int DPictureSequenceView::speed() const
{
    D_DC(DPictureSequenceView);

    return d->speed();
}

void DPictureSequenceView::setSpeed(int speed)
{
    D_D(DPictureSequenceView);

    d->setSpeed(speed);
}

bool DPictureSequenceView::singleShot() const
{
    D_DC(DPictureSequenceView);

    return d->singleShot();
}

void DPictureSequenceView::setSingleShot(bool singleShot)
{
    D_D(DPictureSequenceView);

    d->setSingleShot(singleShot);
}

DUI_END_NAMESPACE

#include "moc_dpicturesequenceview.cpp"