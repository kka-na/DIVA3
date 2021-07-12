#ifndef __QT_HEADER_H__
#define __QT_HEADER_H__

#include <QMainWindow>
#include <QCoreApplication>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QRadioButton>
#include <QDebug>
#include <QMessageBox>
#include <QObject>
#include <QWidget>
#include <QThread>
#include <QLabel>
#include <QRect>
#include <QLayout>
#include <QMap>
#include <QUrl>
#include <QTimer>
#include <QMetaType>
#include <QStorageInfo>
#include <QPalette>
#include <QDial>

#include <QFile>
#include <QString>
#include <QDebug>
#include <QDir>
#include <QTextStream>

#include <QtWebEngineWidgets/QtWebEngineWidgets>

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>


static QPalette colorTheme( const QColor& base )
{
    QPalette palette;
    palette.setColor( QPalette::Base, base );
    palette.setColor( QPalette::Window, base.darker( 150 ) );
    palette.setColor( QPalette::Mid, base.darker( 110 ) );
    palette.setColor( QPalette::Light, base.lighter( 170 ) );
    palette.setColor( QPalette::Dark, base.darker( 170 ) );
    palette.setColor( QPalette::Text, base.darker( 200 ).lighter( 800 ) );
    palette.setColor( QPalette::WindowText, base.darker( 200 ) );

    return palette;
}

#endif //__QT_HEADER_H