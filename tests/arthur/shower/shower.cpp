/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the test suite of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include "shower.h"

#include "qengines.h"

#include <QApplication>
#include <QSvgRenderer>
#include <QPainter>
#include <QPaintEvent>
#include <QFile>
#include <QTextStream>
#include <QTemporaryFile>
#include <QDir>
#include <QtDebug>

static QString loadFile(const QString &name)
{
    QFile file(name);
    if (!file.open(QFile::ReadOnly)) {
        qDebug("Can't open file '%s'", qPrintable(name));
        return QString();
    }
    QTextStream str(&file);
    return str.readAll();
}

Shower::Shower(const QString &file,
               const QString &engineName)
    : QWidget(0)
{
    foreach(QEngine *qengine, QtEngines::self()->engines()) {
        if (qengine->name() == engineName) {
            engine = qengine;
            break;
        }
    }

    QFileInfo fi(file);
    baseDataDir = fi.absolutePath();
    if (file.endsWith("svg")) {
        renderer = new QSvgRenderer(this);
        renderer->load(file);
    } else {
        qps = QFileInfo(file);
        QString script = loadFile(qps.absoluteFilePath());
        qpsScript = script.split("\n", QString::SkipEmptyParts);
        renderer = 0;
        if (qpsScript.isEmpty()) {
            printf("failed to read file: '%s'\n", qPrintable(qps.fileName()));
            return;
        }
    }
}


QSize Shower::sizeHint() const
{
    return QSize(600, 600);
}


void Shower::paintEvent(QPaintEvent *)
{
    if (buffer.size() != size()) {
        buffer = QImage(size(), QImage::Format_ARGB32_Premultiplied);
        QPainter p(&buffer);
        p.setViewport(0, 0, width(), height());
        p.eraseRect(0, 0, width(), height());
        engine->prepare(size());
        if (renderer) {
            engine->render(renderer, QString("sample"));
        } else {
            engine->render(qpsScript, qps.absoluteFilePath());
        }
        if (!engine->drawOnPainter(&p)) {
            QString tempFileName = QString("%1sample.png").arg(QDir::tempPath());
            engine->save(tempFileName);
            QImage img(tempFileName);
            engine->cleanup();
            QFile::remove(tempFileName);
            p.drawImage(0, 0, img);
        }
    }
    QPainter pt(this);
    pt.drawImage(0, 0, buffer);
}
