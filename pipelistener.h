// SPDX-License-Identifier: MIT
// Copyright (c) 2024 Pedro López-Cabanillas <plcl@users.sf.net>

#ifndef PIPELISTENER_H
#define PIPELISTENER_H

#ifdef Q_OS_WINDOWS
#include <io.h>
#include <namedpipeapi.h>
#include <windows.h>
#define PipeRead(fd, ptr, size) _read(fd, ptr, size)
#define PipeWrite(fd, str, size) _write(fd, str, size)
#define PipeNew(fds) _pipe(pipe_fds, 4096, _O_BINARY | _O_NOINHERIT)
#define PipeClose(fd) _close(fd)
#define PipeNonBlock(fd) \
    DWORD lpMode = PIPE_READMODE_BYTE | PIPE_NOWAIT; \
    auto hfdPipe = reinterpret_cast<HANDLE>(_get_osfhandle(fd)); \
    SetNamedPipeHandleState(hfdPipe, &lpMode, nullptr, nullptr)
#else
#include <unistd.h>
#define PipeRead(fd, ptr, size) read(fd, ptr, size)
#define PipeWrite(fd, str, size) write(fd, str, size)
#define PipeNew(fds) pipe2(fds, O_NONBLOCK)
#define PipeClose(fd) close(fd)
#define PipeNonBlock(fd)
#endif
#include <fcntl.h>

#include <QObject>

class PipeListener : public QObject
{
    Q_OBJECT

    int m_fdread;

public:
    explicit PipeListener(int fd, QObject *parent = nullptr);

    void disableNotifier();
    void emitReadyRead();

signals:
    void dataRead(const QString &str);
    void readyRead();
};

#endif
