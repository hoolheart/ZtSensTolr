#ifndef ZTLOGGER_H
#define ZTLOGGER_H
#include <QString>
#include <QQueue>
#include <QDateTime>

class ZtLog
{
public:
    typedef enum enumLogType {
        error, warning, record
    }LOG_TYPE;
    LOG_TYPE type;
    QString content;
    QDateTime time;
};

class ZtLogger
{
private:
    QQueue<ZtLog *> logger;
    void addLog(ZtLog::LOG_TYPE _t, QString _c) {
        ZtLog *log = new ZtLog();
        log->type = _t;
        log->content = _c;
        log->time = QDateTime::currentDateTime();
        logger.enqueue(log);
    }

public:
    ZtLogger() {cleanAll();}
    ~ZtLogger() {cleanAll();}
    void cleanAll() {
        while(!logger.isEmpty()) {
            delete logger.dequeue();
        }
    }

    void reportError(QString _c) {addLog(ZtLog::error,_c);}
    void reportWarning(QString _c) {addLog(ZtLog::warning,_c);}
    void report(QString _c) {addLog(ZtLog::record,_c);}
    bool isEmpty() {return logger.isEmpty();}
    bool pop(ZtLog &_log) {
        if (logger.isEmpty())
            return false;
        ZtLog *log = logger.dequeue();
        _log.type = log->type;
        _log.content = log->content;
        return true;
    }
};

#endif // ZTLOGGER_H
