#ifndef DOPTIONLIST_H
#define DOPTIONLIST_H

#include "libdui_global.h"
#include "dobject.h"
#include "doption.h"

#include <QListWidget>

DUI_BEGIN_NAMESPACE

class DOptionListPrivate;
class LIBDUISHARED_EXPORT DOptionList : public QListWidget, public DObject
{
    Q_OBJECT
    Q_DISABLE_COPY(DOptionList)
    D_DECLARE_PRIVATE(DOptionList)

public:
    explicit DOptionList(QWidget *parent = nullptr);

    void addOption(DOption *option);
    void insertOption(int pos, DOption *option);

    void setCurrentSelected(int pos);
    void setCurrentSelected(const QString &value);

protected:
    D_PRIVATE_SLOT(void _q_currentItemChanged(QListWidgetItem*,QListWidgetItem*))
};

DUI_END_NAMESPACE

#endif // DOPTIONLIST_H
