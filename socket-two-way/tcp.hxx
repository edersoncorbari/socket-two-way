/**                                                                                                                     
 * @file                                                                                                                
 *                                                                                                                      
 * Definitions for an tcp.                                                                                           
 *                                                                                                                      
 * Socket-Two-Way - Simple bidirectional socket.                                                                        
 *                                                                                                                      
 * Copyright (c) 2017 Ederson de Moura Corbari                                                                          
 *                                                                                                                      
 * @author Ederson de Moura Corbari                                                                                     
 *                                                                                                                      
 * $Id: Exp$                                                                                                            
 */  

#pragma once
#ifndef SERVER_TCP_HXX
#define SERVER_TCP_HXX

// Application.
#include "global.hxx"
#include "tcpthread.hxx"

// Qt.
#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>
#include <QVariantList>

// STD.
#include <string>
#include <typeinfo>

namespace server {
/**
 * @brief The Tcp Class.
 *
 * This class is a bidirectional data server, the client
 * connects to the server by sending a command, and the
 * server responds to the command that was passed.
 */
class SERVER_SHARED_EXPORT Tcp : public QTcpServer
{
    Q_OBJECT

public:
    /// Properties of Tcp Class.
    struct self {
        std::string NAME; ///< Name of this class.
    } ///< Initialize objects.
    self = {
        this->metaObject()->className()
    };

    /**
     * Constructor.
     *
     * @param parent Object parent.
     * @param packageMessage Package message to send clients.
     */
    explicit Tcp(QObject *parent = Q_NULLPTR, const QString packageMessage = QString());

    /**
     * Destructor.
     */
    virtual ~Tcp();

    /**
     * Singleton design pattern.
     *
     * @return An instance of the class.
     */
    static Tcp *getInstance();

    /**
     * The data packet to be transferred when the client
     * connects to the server.
     *
     * @param packageMessage The data packet in string.
     */
    virtual void setPackageMessageTransfer(const QString packageMessage = QString());

private Q_SLOTS:
    /**
     * This slot is called every time a new connection is
     * opened on the server.
     */
    void onNewConnection()
    {
        Q_EMIT newConnectionReceived();
    }

    /**
     * This slot is called when an error occurred on the server.
     *
     * @param socketError The errors to be handled.
     */
    void onError(QTcpSocket::SocketError socketError);

Q_SIGNALS:
    /**
     * Signal triggered when a new connection happens on
     * the server.
     */
    void newConnectionReceived();

    /**
     * Signal is triggered when a server error occurs.
     *
     * @param explanation The error that occurred.
     */
    void error(QString explanation = QString());

protected:
    /**
     * Re-implemented method of QTcpServer class to create a new connection.
     *
     * @param socketDescriptor The data in the socket.
     */
    virtual void incomingConnection(qintptr socketDescriptor) override;

    /// Visible objects used by Tcp Class.
    struct selfData {
        /// Store the message to the client.
        QString packageTransfer = QString();
    } m_selfData;
};

} // Namespace.

#endif // SERVER_TCP_HXX
