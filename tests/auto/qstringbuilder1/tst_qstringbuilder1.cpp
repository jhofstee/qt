/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the test suite module of the Qt Toolkit.
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


// SCENARIO 1
// this is the "no harm done" version. Only operator% is active,
// with NO_CAST * defined
#define P %
#undef QT_USE_QSTRINGBUILDER
#define QT_NO_CAST_FROM_ASCII
#define QT_NO_CAST_TO_ASCII


#include <QtTest/QtTest>

//TESTED_CLASS=QStringBuilder
//TESTED_FILES=qstringbuilder.cpp

#define LITERAL "some literal"

void runScenario(); // Defined in stringbuilder.cpp #included below.

class tst_QStringBuilder1 : public QObject
{
    Q_OBJECT

private slots:
    void scenario() { runScenario(); }
};

#include "stringbuilder.cpp"
#include "tst_qstringbuilder1.moc"

QTEST_APPLESS_MAIN(tst_QStringBuilder1)
