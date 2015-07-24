#include <QApplication>
#include <QFile>
#include <QDebug>

#include "dthememanager.h"

DUI_BEGIN_NAMESPACE

class DThemeManagerPrivate : public DThemeManager
{

};

Q_GLOBAL_STATIC(DThemeManagerPrivate, DThemeManagerStatic)

DThemeManager * DThemeManager::instance()
{
    return DThemeManagerStatic;
}

void DThemeManager::setTheme(QString theme) const
{
    QApplication * app = qobject_cast<QApplication*>(QApplication::instance());
    if (app != NULL) {
        QFile themeFile(QString(":/%1/%1.theme").arg(theme));

        if (themeFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QString theme = themeFile.readAll();
            app->setStyleSheet(theme);

            themeFile.close();
        }
    }
}

// private methods
DThemeManager::DThemeManager() :
    QObject()
{
    this->setTheme("dark");
}

DUI_END_NAMESPACE
