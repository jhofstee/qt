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
#include <QDebug>
#include <qtest.h>
#include <QtTest/QtTest>
#include <QtCore/QCoreApplication>
#include <QtCore/QFileInfo>
#include <QtCore/QFile>

#include "private/qfsfileengine_p.h"
#include "../../../../shared/filesystem.h"

class qfileinfo : public QObject
{
    Q_OBJECT
private slots:
    void canonicalFileNamePerformance();
#if defined(Q_OS_WIN) && !defined(Q_OS_WINCE)
    void symLinkTargetPerformanceLNK();
    void symLinkTargetPerformanceMounpoint();
#endif
    void initTestCase();
    void cleanupTestCase();
public:
    qfileinfo() : QObject() {};
};

void qfileinfo::initTestCase()
{
}

void qfileinfo::cleanupTestCase()
{
}

void qfileinfo::canonicalFileNamePerformance()
{
    QString appPath = QCoreApplication::applicationFilePath();
    QFSFileEnginePrivate::canonicalized(appPath); // warmup
    QFSFileEnginePrivate::canonicalized(appPath); // more warmup
    QBENCHMARK {
        for (int i = 0; i < 5000; i++) {
            QFSFileEnginePrivate::canonicalized(appPath);
        }
    }
}

#if defined(Q_OS_WIN) && !defined(Q_OS_WINCE)
void qfileinfo::symLinkTargetPerformanceLNK()
{
    QVERIFY(QFile::link("file","link.lnk"));
    QFileInfo info("link.lnk");
    info.setCaching(false);
    QVERIFY(info.isSymLink());
    QString linkTarget;
    QBENCHMARK {
        for(int i=0; i<100; i++)
            linkTarget = info.readLink();
    }
    QVERIFY(QFile::remove("link.lnk"));
}

void qfileinfo::symLinkTargetPerformanceMounpoint()
{
    wchar_t buffer[MAX_PATH];
    QString rootPath = QDir::toNativeSeparators(QDir::rootPath());
    QVERIFY(GetVolumeNameForVolumeMountPointW(rootPath.utf16(), buffer, MAX_PATH));
    QString rootVolume = QString::fromWCharArray(buffer);
    QString mountpoint = "mountpoint";
    rootVolume.replace("\\\\?\\","\\??\\");
    FileSystem::createNtfsJunction(rootVolume, mountpoint);

    QFileInfo info(mountpoint);
    info.setCaching(false);
    QVERIFY(info.isSymLink());
    QString linkTarget;
    QBENCHMARK {
        for(int i=0; i<100; i++)
            linkTarget = info.readLink();
    }
    QVERIFY(QDir().rmdir(mountpoint));
}
#endif

QTEST_MAIN(qfileinfo)

#include "main.moc"
