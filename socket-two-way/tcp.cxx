/**                                                                                                                     
 * @file                                                                                                                
 *                                                                                                                      
 * Implementation for an tcp.                                                                                           
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
#ifndef SERVER_TCP_HXX
#include "tcp.hxx"
#endif

// Qt.
#include <QtCore>
#include <QtNetwork>

namespace server {

Tcp::Tcp(QObject *parent, const QString packageMessage)
    : QTcpServer(parent)
{
    qInfo() << QString::fromStdString(this->self.NAME) + ": Contructor class.";

    // Set package message.
    if (!packageMessage.isEmpty())
        this->m_selfData.packageTransfer = packageMessage;
}

Tcp::~Tcp()
{
    qInfo() << QString::fromStdString(this->self.NAME) + ": Destructor class.";
}

void Tcp::setPackageMessageTransfer(const QString packageMessage)
{
    qInfo() << QString::fromStdString(this->self.NAME) + ": Package message transfer.";

    if (packageMessage.isEmpty())
        return;

    this->m_selfData.packageTransfer = packageMessage;
}

void Tcp::incomingConnection(qintptr socketDescriptor)
{
    qInfo() << QString::fromStdString(this->self.NAME) + ": Server open new connection.";

    // The package message.
    const QString package = this->m_selfData.packageTransfer;

    // TcpThread runnable instance.
    QPointer<server::TcpThread> tcpThread = new server::TcpThread(socketDescriptor, package, 0);
    QObject::connect(tcpThread, &server::TcpThread::error, this, &server::Tcp::onError);

    // Start TcpThread.
    QThreadPool::globalInstance()->start(tcpThread);
}

void Tcp::onError(QTcpSocket::SocketError socketError)
{
    QString explanation = QString();

    switch (socketError) {
    case QAbstractSocket::ConnectionRefusedError:
        explanation = "The connection was refused by the peer (or timed out).";
        break;
    case QAbstractSocket::RemoteHostClosedError:
        explanation = "The remote host closed the connection.";
        break;
    case QAbstractSocket::HostNotFoundError:
        explanation = "The host address was not found.";
        break;
    case QAbstractSocket::SocketAccessError:
        explanation = "The socket operation failed because the application lacked the required privileges.";
        break;
    case QAbstractSocket::SocketResourceError:
        explanation = "The local system ran out of resources (e.g., too many sockets).";
        break;
    case QAbstractSocket::SocketTimeoutError:
        explanation = "The socket operation timed out.";
        break;
    case QAbstractSocket::DatagramTooLargeError:
        explanation = "The datagram was larger than the operating system's.";
        break;
    case QAbstractSocket::NetworkError:
        explanation = "An error occurred with the network.";
        break;
    case QAbstractSocket::AddressInUseError:
        explanation = "The address specified to bind is already in use and was set to be exclusive.";
        break;
    case QAbstractSocket::SocketAddressNotAvailableError:
        explanation = "The address specified to bind does not belong to the host.";
        break;
    case QAbstractSocket::UnsupportedSocketOperationError:
        explanation = "The requested socket operation is not supported by the local operating system.";
        break;
    case QAbstractSocket::ProxyAuthenticationRequiredError:
        explanation = "The socket is using a proxy, and the proxy requires authentication.";
        break;
    case QAbstractSocket::SslHandshakeFailedError:
        explanation = "The SSL/TLS handshake failed, so the connection was closed.";
        break;
    case QAbstractSocket::UnfinishedSocketOperationError:
        explanation = "The last operation attempted has not finished.";
        break;
    case QAbstractSocket::ProxyConnectionRefusedError:
        explanation = "Could not contact the proxy server because the connection was denied.";
        break;
    case QAbstractSocket::ProxyConnectionClosedError:
        explanation = "The connection to the proxy server was closed unexpectedly.";
        break;
    case QAbstractSocket::ProxyConnectionTimeoutError:
        explanation = "The connection to the proxy server timed out or the proxy server stopped.";
        break;
    case QAbstractSocket::ProxyNotFoundError:
        explanation = "The proxy address set with setProxy() (or the application proxy) was not found.";
        break;
    case QAbstractSocket::ProxyProtocolError:
        explanation = "The connection negotiation with the proxy server failed.";
        break;
    case QAbstractSocket::OperationError:
        explanation = "An operation was attempted while the socket was in a state that did not permit it.";
        break;
    case QAbstractSocket::SslInternalError:
        explanation = "The SSL library being used reported an internal error.";
        break;
    case QAbstractSocket::SslInvalidUserDataError:
        explanation = "Invalid data SSL (certificate, key, cypher, etc.).";
        break;
    case QAbstractSocket::TemporaryError:
        explanation = "A temporary error occurred (e.g., operation would block).";
        break;
    case QAbstractSocket::UnknownSocketError:
        explanation = "An unidentified error occurred.";
        break;
    default:
        explanation = "An unidentified error occurred.";
        break;
    }

    qWarning() << QString::fromStdString(this->self.NAME) + ": Server error = " + explanation;
    Q_EMIT error(explanation);
}

} // Namespace.
