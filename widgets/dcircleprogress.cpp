#include "dcircleprogress.h"
#include "private/dcircleprogress_p.h"

#include <QPaintEvent>
#include <QPainter>
#include <QDebug>
#include <QVBoxLayout>

DUI_USE_NAMESPACE

DCircleProgressPrivate::DCircleProgressPrivate(DCircleProgress *q)
    : DObjectPrivate(q)
{
    m_displayLabel.setAttribute(Qt::WA_TranslucentBackground);
    m_displayLabel.setAlignment(Qt::AlignCenter);
    m_displayLabel.setObjectName("DisplayLabel");

    QBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addStretch();
    mainLayout->addWidget(&m_displayLabel);
    mainLayout->addStretch();
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);

    q->setLayout(mainLayout);
}

void DCircleProgressPrivate::paint(QPainter *painter)
{
    Q_Q(const DCircleProgress);

    painter->setRenderHints(QPainter::HighQualityAntialiasing);

    QPen pen(m_chunkColor);
    pen.setWidth(m_lineWidth);
    painter->setPen(pen);
    const QRect widgetRect = q->rect();
    QRect outerCircleRect = widgetRect;
    outerCircleRect.setWidth(outerCircleRect.width() - (m_lineWidth - 1) * 2);
    outerCircleRect.setHeight(outerCircleRect.height() - (m_lineWidth - 1) * 2);
    if (outerCircleRect.width() < outerCircleRect.height())
     outerCircleRect.setHeight(outerCircleRect.width());
    else
     outerCircleRect.setWidth(outerCircleRect.height());
    outerCircleRect.setTop((widgetRect.height() - outerCircleRect.height()) / 2);
    outerCircleRect.setLeft((widgetRect.width() - outerCircleRect.width()) / 2);

    const double percent = double(m_currentValue) / (m_maximumValue - m_minmumValue);
    const int splitPos = -percent * 16 * 360;
    painter->drawArc(outerCircleRect, 90 * 16, splitPos);
    pen.setColor(m_backgroundColor);
    painter->setPen(pen);
    painter->drawArc(outerCircleRect, 90 * 16, 16 * 360 + splitPos);
}

DCircleProgress::DCircleProgress(QWidget *parent)
    : QWidget(parent),
      DObject(*new DCircleProgressPrivate(this))
{
    D_THEME_INIT_WIDGET(DCircleProgress);
}

int DCircleProgress::value() const
{
    Q_D(const DCircleProgress);

    return d->m_currentValue;
}

void DCircleProgress::setValue(int value)
{
    Q_D(DCircleProgress);

    d->m_currentValue = value;
    update();
}

const QString DCircleProgress::text() const
{
    Q_D(const DCircleProgress);

    return d->m_displayLabel.text();
}

void DCircleProgress::setText(const QString &text)
{
    Q_D(DCircleProgress);

    return d->m_displayLabel.setText(text);
}

void DCircleProgress::setPixmap(const QPixmap &pm)
{
    Q_D(DCircleProgress);

    d->m_displayLabel.setPixmap(pm);
}

const QColor DCircleProgress::backgroundColor() const
{
    Q_D(const DCircleProgress);

    return d->m_backgroundColor;
}

void DCircleProgress::setBackgroundColor(const QColor &color)
{
    Q_D(DCircleProgress);

    d->m_backgroundColor = color;
}

const QColor DCircleProgress::chunkColor() const
{
    Q_D(const DCircleProgress);

    return d->m_chunkColor;
}

void DCircleProgress::setChunkColor(const QColor &color)
{
    Q_D(DCircleProgress);

    d->m_chunkColor = color;
}

void DCircleProgress::paintEvent(QPaintEvent *e)
{
    Q_D(DCircleProgress);

    QPainter p(this);
    d->paint(&p);

    QWidget::paintEvent(e);
}
