#ifndef DCIRCLEPROGRESS_H
#define DCIRCLEPROGRESS_H

#include "libdui_global.h"
#include "dthememanager.h"
#include "dobject.h"

#include <QWidget>
#include <QLabel>
#include <QPixmap>

DUI_BEGIN_NAMESPACE

class DCircleProgressPrivate;
class LIBDUISHARED_EXPORT DCircleProgress : public QWidget, public DObject
{
    Q_OBJECT
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor DESIGNABLE true)
    Q_PROPERTY(QColor chunkColor READ chunkColor WRITE setChunkColor DESIGNABLE true)
    Q_PROPERTY(int lineWidth READ lineWidth WRITE setLineWidth DESIGNABLE true)

signals:
    void clicked();
    void mouseEntered();
    void mouseLeaved();

public:
    explicit DCircleProgress(QWidget *parent = 0);

    int value() const;
    void setValue(int value);

    const QString text() const;
    void setText(const QString &text);

    const QColor backgroundColor() const;
    void setBackgroundColor(const QColor &color);

    const QColor chunkColor() const;
    void setChunkColor(const QColor &color);

    int lineWidth() const;
    void setLineWidth(const int width);

    QLabel *topLabel();
    QLabel *bottomLabel();

signals:
    void valueChanged(const int value) const;

protected:
    void paintEvent(QPaintEvent *e) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void enterEvent(QEvent *e) Q_DECL_OVERRIDE;
    void leaveEvent(QEvent *e) Q_DECL_OVERRIDE;

private:
    D_DECLARE_PRIVATE(DCircleProgress)
};

DUI_END_NAMESPACE

#endif // DCIRCLEPROGRESS_H
