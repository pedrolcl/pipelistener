#include <QCoreApplication>
#include <QDebug>
#include <QTimer>

#include "pipelistener.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    enum PIPES { READ, WRITE };

    int count{0};
    int pipe_fds[2];
    int res = PipeNew(pipe_fds);
    Q_ASSERT_X(res == 0, "main", "Error creating the pipe");

    PipeListener listener(pipe_fds[READ]);
    QObject::connect(&listener, &PipeListener::dataRead, [&](const QString &str) {
        qDebug() << "Echo :" << str;
        if (str.compare("q", Qt::CaseInsensitive) == 0) {
            qDebug() << "adios!";
            app.quit();
        }
    });

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&] {
        if (count++ < 5) {
            PipeWrite(pipe_fds[WRITE], "hola!", 5);
        } else {
            PipeWrite(pipe_fds[WRITE], "q", 1);
            timer.stop();
        }
        listener.emitReadyRead();
    });

    qDebug() << "Listening to pipe input:";
    timer.start(600);

    res = app.exec();

    PipeClose(pipe_fds[WRITE]);
    PipeClose(pipe_fds[READ]);

    return res;
}
