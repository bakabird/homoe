#ifndef NETBOY_H
#define NETBOY_H
#include <QtNetwork>
#include <QObject>
#include <QString>

class NetBoy : public QObject
{
    Q_OBJECT
public:
    explicit NetBoy(QObject *parent = nullptr);
    bool hey();
    void refreshDB();
    int newRoom(int x, int y);
    int newLight(QString);
    void updateRoomPos(int roomId,int x, int y);
    void changeRoomName(int roomId, QString roomName);
    int switchMode(int aimMode);
    QJsonArray allLightsSta();
    int newEqp(QString eleType, QString eleName, int setOn);

    int updateEqpSet(int eid,int setOn);
    void changeEqpName(int eid, QString eqpName);

signals:

public slots:

private:
    QString baseUrl;
    QNetworkRequest req;
    QNetworkAccessManager* manager;
    QNetworkReply* res;
};

#endif // NETBOY_H
