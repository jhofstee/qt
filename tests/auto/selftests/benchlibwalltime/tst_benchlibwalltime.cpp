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


#include <QtCore>
#include <QtTest/QtTest>

class tst_BenchlibWalltime: public QObject
{
    Q_OBJECT

private slots:
    void waitForOneThousand();
    void waitForFourThousand();
    void qbenchmark_once();
};

void tst_BenchlibWalltime::waitForOneThousand()
{
    QBENCHMARK {
        QTest::qWait(1000);
    }
}

void tst_BenchlibWalltime::waitForFourThousand()
{
    QBENCHMARK {
        QTest::qWait(4000);
    }
}

void tst_BenchlibWalltime::qbenchmark_once()
{
    int iterations = 0;
    QBENCHMARK_ONCE {
        ++iterations;
    }
    QCOMPARE(iterations, 1);
}


QTEST_MAIN(tst_BenchlibWalltime)

#include "tst_benchlibwalltime.moc"
