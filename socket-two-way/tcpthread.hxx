/**                                                                                                                     
 * @file                                                                                                                
 *                                                                                                                      
 * Definitions for an tcpthread.                                                                                           
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
#ifndef SERVER_TCPTHREAD_HXX
#define SERVER_TCPTHREAD_HXX

// Application.
#include "global.hxx"

// Qt.
#include <QObject>
#include <QTcpSocket>
#include <QRunnable>
#include <QEventLoop>
#include <QMap>
#include <QVariantList>

// STD.
#include <string>

namespace server {
/**
 * @brief The TcpThread Class.
 *
 * This class is a bidirectional data server running in thread mode,
 * it is called by class Tcp we read the command that the client
 * reported and we answer that accordingly.
 *
 *  @see See http://doc.qt.io/qt-5/qthreadpool.html
 */
class SERVER_SHARED_EXPORT TcpThread : public QObject, public QRunnable
{
    Q_OBJECT

public:
    /// Properties of TcpThread Class.
    struct self {
        std::string NAME; ///< Name of this class.
    } ///< Initialize objects.
    self = {
        this->metaObject()->className()
    };

    /**
     * Constructor.
     *
     * @param socketDescriptor The socket data.
     * @param packageMessage The message to be sent to the client.
     * @param parent Object The object parent.
     */
    explicit TcpThread(int socketDescriptor = 0, const QString packageMessage = QString(),
                       QObject *parent = Q_NULLPTR);

    /**
     * Destructor.
     */
    virtual ~TcpThread();

    /**
     * Re-implemented method that handles the client server connection.
     */
    virtual void run();

    /**
     * Count number thread interaction in system.
     *
     * @see http://doc.qt.io/qt-4.8/qthread.html#idealThreadCount
     * @return Return number thread interaction.
     */
    static int countThreadInteraction()
    {
        return TcpThread::m_countThreadInteraction;
    }

Q_SIGNALS:
    /**
     * Signal is triggered when a server error occurs.
     *
     * @param socketError The error that occurred.
     */
    void error(QTcpSocket::SocketError socketError);

    /**
     * Signal triggered when a new connection happens on
     * the server.
     */
    void newConnection();

private Q_SLOTS:
    /**
     * The slot is called when the client sends a command,
     * in this method other treatments are made of the received
     * commands.
     */
    void onReadSocket();

    /**
     * The slot is called when the client is connected in server.
     */
    void onConnected();

    /**
     * The slot is called when the client disconnects from
     * the server.
     */
    void onDisconnected();

private:
    /**
     * Used to get information from the client that is connecting
     * to the server.
     */
    void getClientInfo();

protected:
    /// Visible objects used by TcpThread Class.
    struct selfData {
        /// Socket descriptor.
        int socketDescriptor = 0;

        /// The number of connections made by a client.
        unsigned int clientConnection = 1;

        /// Data to be sent to the client.
        QString packageTransfer = QString();
    } m_selfData;

    /// The server instance.
    QSharedPointer<QTcpSocket> m_tcpSocket;

    /// Create event loop in thread.
    QSharedPointer<QEventLoop> m_eventLoop;

    /// Store thread interaction.
    static int m_countThreadInteraction;
};

} // Namespace.

#endif // SERVER_TCPTHREAD_HXX
