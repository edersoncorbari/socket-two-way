/**                                                                                                                     
 * @file                                                                                                                
 *                                                                                                                      
 * Implementation for an tcpthread.                                                                                           
 *                                                                                                                      
 * Socket-Two-Way - Simple bidirectional socket.                                                                        
 *                                                                                                                      
 * Copyright (c) 2017 Ederson de Moura Corbari                                                                          
 *                                                                                                                      
 * @author Ederson de Moura Corbari                                                                                     
 *                                                                                                                      
 * $Id: Exp$                                                                                                            
 */

// Application.
#ifndef SERVER_TCPTHREAD_HXX
#include "tcpthread.hxx"
#endif
#ifndef SERVER_SERVER_HXX
#include "server.hxx"
#endif

// Qt.
#include <QtCore>
#include <QtNetwork>

// Start static variables and objects.
int server::TcpThread::m_countThreadInteraction = 1;

namespace server {

TcpThread::TcpThread(int socketDescriptor, const QString packageMessage, QObject *parent)
    : QObject(parent)
{
    qInfo() << QString::fromStdString(this->self.NAME) + ": Contructor class.";

    this->setAutoDelete(true);

    this->m_selfData.socketDescriptor = socketDescriptor;
    this->m_selfData.packageTransfer = packageMessage;
}

TcpThread::~TcpThread()
{
    qInfo() << QString::fromStdString(this->self.NAME) + ": Destructor class.";
    TcpThread::m_countThreadInteraction = 1;
}

void TcpThread::getClientInfo()
{
    qInfo() << QString::fromStdString(this->self.NAME) + ": Run client information.";

    const QString date = QDate::currentDate().toString(QString("dd/MM/yyyy"));
    const QString hour = QTime::currentTime().toString(QString("hh:mm:ss:zz"));
    const QString datetime = (date + QString(" ") + hour);

    QVariantList dataClient = QVariantList();
    dataClient.append(m_tcpSocket->peerName());
    dataClient.append(m_tcpSocket->peerPort());
    dataClient.append(m_selfData.clientConnection);
    dataClient.append(m_tcpSocket->peerAddress().toString());
    dataClient.append(datetime);

    qDebug() << "Client infor connected to the server: " << dataClient;
}

void TcpThread::run()
{
    qInfo() << QString::fromStdString(this->self.NAME) + ": Running server thread.";

    m_eventLoop = QSharedPointer<QEventLoop>(new QEventLoop, &QObject::deleteLater);
    m_tcpSocket = QSharedPointer<QTcpSocket>(new QTcpSocket, &QObject::deleteLater);

    const QString strInteraction = QString::number(server::TcpThread::m_countThreadInteraction);
    qInfo() << QString::fromStdString(this->self.NAME) + ": Total interaction = " + strInteraction;

    if (m_tcpSocket->setSocketDescriptor(this->m_selfData.socketDescriptor)) {
        QObject::connect(m_tcpSocket.data(), &QTcpSocket::connected, this, &server::TcpThread::onConnected,
                         Qt::DirectConnection);
        QObject::connect(m_tcpSocket.data(), &QTcpSocket::readyRead, this, &server::TcpThread::onReadSocket,
                         Qt::DirectConnection);
        QObject::connect(m_tcpSocket.data(), &QTcpSocket::disconnected, this,
                         &server::TcpThread::onDisconnected,
                         Qt::DirectConnection);

        this->getClientInfo();
    } else {
        Q_EMIT error(m_tcpSocket->error());
    }

    m_eventLoop->exec();
    m_tcpSocket.clear();
    m_eventLoop.clear();
}

void TcpThread::onConnected()
{
    qInfo() << QString::fromStdString(this->self.NAME) + ": Open connection with server.";
    Q_EMIT newConnection();
}

void TcpThread::onDisconnected()
{
    qInfo() << QString::fromStdString(this->self.NAME) + ": Close connection with server.";
    m_eventLoop->exit();
}

void TcpThread::onReadSocket()
{
    qInfo() << QString::fromStdString(this->self.NAME) + ": Run slot read socket.";

    QByteArray block = QByteArray();
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    out.setByteOrder(QDataStream::ByteOrder(QSysInfo::ByteOrder));

    const QByteArray data = m_tcpSocket->readAll();

    const QString date = QDate::currentDate().toString(QString("dd/MM/yyyy"));
    const QString hour = QTime::currentTime().toString(QString("hh:mm:ss:zz"));
    const QString datetime = (date + QString(" ") + hour);

    if (data == QByteArray(server::command::SELECT)) {

        const QString cmd = server::command::SELECT;
        qWarning() << QString::fromStdString(this->self.NAME) + ": Run command = " + cmd;
        this->m_selfData.packageTransfer = "SELECT command executed at " + datetime + ".";

    } else if (data == QByteArray(server::command::INFO_SERVER)) {

        const QString cmd = server::command::INFO_SERVER;                                                                    
        qWarning() << QString::fromStdString(this->self.NAME) + ": Run command = " + cmd;                                  
        this->m_selfData.packageTransfer = server::Server::getInstance()->printJsonServerInfo();

    } else {

        const QString cmd = server::command::ERROR_UNKNOWN_COMMAND;
        qInfo() << QString::fromStdString(this->self.NAME) + ": Run command = " + cmd;
        this->m_selfData.packageTransfer = cmd; 

    }

    out << this->m_selfData.packageTransfer.toUtf8();
    out.device()->seek(0);
    out.device()->reset();

    // Workaround: removing dirt from bytes.
    block.replace(char(0x00), QByteArray()); 
    block.replace(char(0x01), QByteArray()); 
    block.replace(char(0x02), QByteArray()); 
    block.replace(char(0x03), QByteArray()); 
    block.replace(char(0x04), QByteArray()); 
    block.replace(char(0x05), QByteArray()); 
    block.replace(char(0x06), QByteArray()); 
    block.replace(char(0x07), QByteArray()); 
    block.replace(char(0x08), QByteArray()); 
    block.replace(char(0x09), QByteArray());
    block.replace(char(0x10), QByteArray()); 
    block = block.mid(1);

    m_tcpSocket->write(block.data(), block.size());
    m_tcpSocket->flush();

    m_tcpSocket->waitForBytesWritten();
    m_tcpSocket->disconnectFromHost();
    m_tcpSocket->close();
}

} // Namespace.
