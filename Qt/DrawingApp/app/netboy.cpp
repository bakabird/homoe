#include "netboy.h"
#include <QString>
#include <QJsonValue>


NetBoy::NetBoy(QObject *parent) : QObject(parent)
{
    baseUrl = "http://127.0.0.1:8360/";
    manager = new QNetworkAccessManager(this);
}

bool NetBoy::hey()
{
    // 构造请求
    req.setUrl(QUrl(baseUrl + "control/hey"));

    // 发送请求
    res = manager->get(req);

    // 开启一个局部的事件循环，等待响应结束，退出
    QEventLoop eventLoop;
    QObject::connect(manager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    // 获取响应信息
    QByteArray jsBytes = res->readAll();
    qDebug() << jsBytes;

    QJsonDocument resJsonDocument = QJsonDocument::fromJson(jsBytes);
    if( resJsonDocument.isNull() ){
        return false;
    }else{
        return true;
    }
}

//该API用以在程序运行过程中初始化数据库。
void NetBoy::refreshDB()
{
    // 构造请求
    req.setUrl(QUrl(baseUrl + "control/flash"));

    // 发送请求
    res = manager->get(req);

    // 开启一个局部的事件循环，等待响应结束，退出
    QEventLoop eventLoop;
    QObject::connect(manager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    // 获取响应信息
    QByteArray bytes = res->readAll();
    qDebug() << bytes;
}
int NetBoy::newRoom(int x, int y)
{
    // 准备数据
    QJsonObject json;
    json.insert("x",x);
    json.insert("y",y);

    QJsonDocument document;
    document.setObject(json);
    QByteArray dataArray = document.toJson(QJsonDocument::Compact);

    // 构造请求
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    req.setUrl(QUrl(baseUrl + "room/new"));

    // 发送请求
    res = manager->post(req,dataArray);

    // 开启一个局部的事件循环，等待响应结束，退出
    QEventLoop eventLoop;
    QObject::connect(manager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    // 获取响应信息
    QByteArray jsBytes = res->readAll();
    qDebug() << jsBytes;

    QJsonDocument resJsonDocument = QJsonDocument::fromJson(jsBytes);
    if( resJsonDocument.isNull() ){
        qDebug()<< "===> QJsonDocument："<< jsBytes;
    }
    QJsonObject jsonObject = resJsonDocument.object();

    qDebug() << QString::number( jsonObject.value("data").toObject().value("roomId").toInt() );
    return jsonObject.value("data").toObject().value("roomId").toInt();
}

void NetBoy::updateRoomPos(int roomId,int x, int y)
{
    // 准备数据
    QJsonObject json;
    json.insert("roomId",roomId);
    json.insert("x",x);
    json.insert("y",y);

    QJsonDocument document;
    document.setObject(json);
    QByteArray dataArray = document.toJson(QJsonDocument::Compact);

    // 构造请求
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    req.setUrl(QUrl(baseUrl + "room/update"));

    // 发送请求
    res = manager->post(req,dataArray);

    // 开启一个局部的事件循环，等待响应结束，退出
    QEventLoop eventLoop;
    QObject::connect(manager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    // 获取响应信息
    QByteArray jsBytes = res->readAll();
    qDebug() << jsBytes;
}

void NetBoy::changeRoomName(int roomId, QString roomName)
{

    QJsonObject json;
    json.insert("roomId",roomId);
    json.insert("name", roomName);

    QJsonDocument document;
    document.setObject(json);
    QByteArray dataArray = document.toJson(QJsonDocument::Compact);

    // 构造请求
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    req.setUrl(QUrl(baseUrl + "room/update"));

    // 发送请求
    res = manager->post(req,dataArray);

    // 开启一个局部的事件循环，等待响应结束，退出
    QEventLoop eventLoop;
    QObject::connect(manager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    // 获取响应信息
    QByteArray jsBytes = res->readAll();
    qDebug() << jsBytes;
}

int NetBoy::switchMode(int aimMode)
{

    QJsonObject json;
    json.insert("aimMode",aimMode);


    QJsonDocument document;
    document.setObject(json);
    QByteArray dataArray = document.toJson(QJsonDocument::Compact);

    // 构造请求
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    req.setUrl(QUrl(baseUrl + "control/modeSwitch"));

    // 发送请求
    res = manager->post(req,dataArray);

    // 开启一个局部的事件循环，等待响应结束，退出
    QEventLoop eventLoop;
    QObject::connect(manager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    // 获取响应信息
    QByteArray jsBytes = res->readAll();
    qDebug() << jsBytes;

    //对响应信息的处理
    QJsonDocument resJsonDocument = QJsonDocument::fromJson(jsBytes);
    if( resJsonDocument.isNull() ){
        qDebug()<< "===> QJsonDocument："<< jsBytes;
    }
    QJsonObject jsonObject = resJsonDocument.object();

    qDebug() << QString::number( jsonObject.value("data").toObject().value("curMode").toInt() );
    return jsonObject.value("data").toObject().value("curMode").toInt();
}

QJsonArray NetBoy::allLightsSta()
{
    QJsonObject json;

    // 构造请求
    req.setUrl(QUrl(baseUrl + "light/all"));

    // 发送请求
    res = manager->get(req);

    // 开启一个局部的事件循环，等待响应结束，退出
    QEventLoop eventLoop;
    QObject::connect(manager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    // 获取响应信息
    QByteArray jsBytes = res->readAll();
    qDebug() << jsBytes;


    //对响应信息的处理
    QJsonDocument resJsonDocument = QJsonDocument::fromJson(jsBytes);
    if( resJsonDocument.isNull() ){
        qDebug()<< "===> QJsonDocument："<< jsBytes;
    }
    QJsonObject jsonObject = resJsonDocument.object();

    qDebug() << jsonObject.value("data").toArray();
    return jsonObject.value("data").toArray();
}

int NetBoy::newLight(QString name)
{
    return this->newEqp("light",name,0);
}

int NetBoy::newEqp(QString eleType, QString eleName, int setOn)
{
    // 准备数据
    QJsonObject json;
    json.insert("eleType",eleType);
    json.insert("name",eleName);
    json.insert("setOn",setOn);

    QJsonDocument document;
    document.setObject(json);
    QByteArray dataArray = document.toJson(QJsonDocument::Compact);

    // 构造请求
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    req.setUrl(QUrl(baseUrl + "eleEqp/new"));

    // 发送请求
    res = manager->post(req,dataArray);

    // 开启一个局部的事件循环，等待响应结束，退出
    QEventLoop eventLoop;
    QObject::connect(manager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    // 获取响应信息
    QByteArray jsBytes = res->readAll();
    qDebug() << jsBytes;

    QJsonDocument resJsonDocument = QJsonDocument::fromJson(jsBytes);
    if( resJsonDocument.isNull() ){
        qDebug()<< "===> QJsonDocument："<< jsBytes;
    }
    QJsonObject jsonObject = resJsonDocument.object();

    qDebug() << QString::number( jsonObject.value("data").toObject().value("eid").toInt() );
    return jsonObject.value("data").toObject().value("eid").toInt();
}

int NetBoy::updateEqpSet(int eid,int setOn)
{
    // 准备数据
    QJsonObject json;
    json.insert("eid",eid);
    json.insert("setOn",setOn);

    QJsonDocument document;
    document.setObject(json);
    QByteArray dataArray = document.toJson(QJsonDocument::Compact);

    // 构造请求
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    req.setUrl(QUrl(baseUrl + "eleEqp/update"));

    // 发送请求
    res = manager->post(req,dataArray);

    // 开启一个局部的事件循环，等待响应结束，退出
    QEventLoop eventLoop;
    QObject::connect(manager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    // 获取响应信息
    QByteArray jsBytes = res->readAll();
    qDebug() << jsBytes;


    QJsonDocument resJsonDocument = QJsonDocument::fromJson(jsBytes);
    if( resJsonDocument.isNull() ){
        qDebug()<< "===> QJsonDocument："<< jsBytes;
    }
    QJsonObject jsonObject = resJsonDocument.object();

    qDebug() << QString::number( jsonObject.value("data").toObject().value("setOn").toInt() );
    return jsonObject.value("data").toObject().value("setOn").toInt();
}

void NetBoy::changeEqpName(int eid, QString eqpName)
{

    QJsonObject json;
    json.insert("eid",eid);
    json.insert("name", eqpName);

    QJsonDocument document;
    document.setObject(json);
    QByteArray dataArray = document.toJson(QJsonDocument::Compact);

    // 构造请求
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    req.setUrl(QUrl(baseUrl + "eleEqp/update"));

    // 发送请求
    res = manager->post(req,dataArray);

    // 开启一个局部的事件循环，等待响应结束，退出
    QEventLoop eventLoop;
    QObject::connect(manager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    // 获取响应信息
    QByteArray jsBytes = res->readAll();
    qDebug() << jsBytes;


}
