#!/bin/sh
#
#############################################################################
##
## Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
## Contact: http://www.qt-project.org/
##
## This file is part of the test suite of the Qt Toolkit.
##
## $QT_BEGIN_LICENSE:LGPL$
## GNU Lesser General Public License Usage
## This file may be used under the terms of the GNU Lesser General Public
## License version 2.1 as published by the Free Software Foundation and
## appearing in the file LICENSE.LGPL included in the packaging of this
## file. Please review the following information to ensure the GNU Lesser
## General Public License version 2.1 requirements will be met:
## http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
##
## In addition, as a special exception, Nokia gives you certain additional
## rights. These rights are described in the Nokia Qt LGPL Exception
## version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
##
## GNU General Public License Usage
## Alternatively, this file may be used under the terms of the GNU General
## Public License version 3.0 as published by the Free Software Foundation
## and appearing in the file LICENSE.GPL included in the packaging of this
## file. Please review the following information to ensure the GNU General
## Public License version 3.0 requirements will be met:
## http://www.gnu.org/copyleft/gpl.html.
##
## Other Usage
## Alternatively, this file may be used in accordance with the terms and
## conditions contained in a signed written agreement between you and Nokia.
##
##
##
##
##
##
## $QT_END_LICENSE$
##
############################################################################/

if [ "$(uname)" = Linux ]
then
    Xnest :7 2>/dev/null &
    sleep 1
    trap "kill $!" EXIT
    export DISPLAY=:7
    export LANG=en_US
    kwin 2>/dev/null &
    sleep 1
fi

function filter
{
    exe=$1
    skip=0
    while read line
    do
        if [ $skip != 0 ]
        then
            let skip=skip-1
        else
            case "$line" in
            make*Error) echo "$line";;
            make*Stop) echo "$line";;
            /*/bin/make*) ;;
            make*) ;;
            install*) ;;
            QDeclarativeDebugServer:*Waiting*) ;;
            QDeclarativeDebugServer:*Connection*) ;;
            */qmake*) ;;
            */bin/moc*) ;;
            *targ.debug*) ;;
            g++*) ;;
            cd*) ;;
            XFAIL*) skip=1;;
            SKIP*) skip=1;;
            PASS*) ;;
            QDEBUG*) ;;
            Makefile*) ;;
            Config*) ;;
            Totals*) ;;
            \**) ;;
            ./*) ;;
            *tst_*) echo "$line" ;;
            *) echo "$exe: $line"
            esac
        fi
    done
}

make -k -j1 install 2>&1 | filter build
for exe in $(make install | sed -n 's/^install .* "\([^"]*qt4\/tst_[^"]*\)".*/\1/p')
do
    echo $exe
    $exe 2>&1 | filter $exe
done

