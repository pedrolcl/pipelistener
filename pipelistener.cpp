// SPDX-License-Identifier: MIT
// Copyright (c) 2024 Pedro López-Cabanillas <plcl@users.sf.net>

#include "pipelistener.h"

PipeListener::PipeListener(int fd, QObject *parent)
    : QObject(parent)
    , m_fdread{fd}
{
    PipeNonBlock(fd);
    QObject::connect(this, &PipeListener::readyRead, [&]() {
        QByteArray buf(4096, '\0');
        auto bytes_read = PipeRead(m_fdread, buf.data(), buf.capacity());
        if (bytes_read > 0) {
            buf.resize(bytes_read);
            QString strLine = QString::fromUtf8(buf);
            emit dataRead(strLine);
        }
    });
}

void PipeListener::emitReadyRead()
{
    emit readyRead();
}
