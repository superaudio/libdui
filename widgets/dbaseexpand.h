#ifndef DBASEEXPAND_H
#define DBASEEXPAND_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPropertyAnimation>
#include <QDebug>

#include "libdui_global.h"
#include "dseparatorhorizontal.h"
#include "dconstants.h"

DUI_BEGIN_NAMESPACE

class ContentLoader : public QLabel
{
    Q_OBJECT
    Q_PROPERTY(int height READ height WRITE setFixedHeight)
public:
    explicit ContentLoader(QWidget *parent = 0) : QLabel(parent){}
};

class LIBDUISHARED_EXPORT DBaseExpand : public QWidget
{
    Q_OBJECT
public:
    explicit DBaseExpand(QWidget *parent = 0);

    void setHeader(QWidget *header);
    void setContent(QWidget *content);
    void setHeaderHeight(int height);
    void setExpand(bool value);
    bool expand() const;
    void setAnimationDuration(int duration);
    void setAnimationEasingCurve(QEasingCurve curve);
    void resizeEvent(QResizeEvent *e);

signals:
    void expandChange(bool e);
    void sizeChanged(QSize s);

private:
    QWidget *m_content = NULL;
    QVBoxLayout *m_headerLayout = NULL;
    QVBoxLayout *m_contentLayout = NULL;
    ContentLoader *m_contentLoader = NULL;
    DSeparatorHorizontal * m_hSeparator = NULL;
    QPropertyAnimation *m_animation = NULL;
    bool m_expand = false;
    int m_headerHeight = DUI::EXPAND_HEADER_HEIGHT;
};

DUI_END_NAMESPACE

#endif // DBASEEXPAND_H
