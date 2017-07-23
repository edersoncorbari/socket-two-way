/**                                                                                                                     
 * @file                                                                                                                
 *                                                                                                                      
 * Implementation for an runsocket.                                                                                           
 *                                                                                                                      
 * Socket-Two-Way - Simple bidirectional socket.                                                                        
 *                                                                                                                      
 * Copyright (c) 2017 Ederson de Moura Corbari                                                                          
 *                                                                                                                      
 * @author Ederson de Moura Corbari                                                                                     
 *                                                                                                                      
 * $Id: Exp$                                                                                                            
 */

// Socket Server.
#include <SocketTwoWay>

// Qt.
#include <QtCore>

// STD.
#include <iostream>
#include <csignal>
 
void signal_handler(int signum)                                                                                         
{                                                                                                                       
    QString msg = QString();                                                                                            
                                                                                                                        
    switch (signum) {                                                                                                   
    case SIGABRT:                                                                                                       
        msg = QObject::tr("SIGABRT received.");                                                                         
        break;                                                                                                          
    case SIGSEGV:                                                                                                       
        msg = QObject::tr("SIGSEGV received.");                                                                         
        if (qApp) {                                                               
            std::clog << "Closing the application because: " << msg.toStdString() << std::endl;                         
            qApp->quit();                                                                                               
            std::exit(1);                                                                   
            return;                                                                                                     
        }                                                                                                               
        break;                                                                                                          
    case SIGFPE:                                                                                                        
        msg = QObject::tr("SIGFPE received.");                                                                          
        break;                                                                                                          
    case SIGILL:                                                                                                        
        msg = QObject::tr("SIGILL received.");
        std::exit(0);                                                                     
        break;                                                                                                          
    case SIGINT:                                                                                                        
        msg = QObject::tr("SIGINT received.");                                                                          
        if (qApp) {                                                               
            std::clog << "Closing the application because: " << msg.toStdString() << std::endl;                         
            qApp->quit();                                                                                               
            return;                                                                                                     
        }                                                                                                               
        break;                                                                                                          
#if defined(Q_OS_LINUX) || defined(Q_OS_FREEBSD) || defined(Q_OS_DARWIN)                                                
    case SIGQUIT:                                                                                                       
        msg = QObject::tr("SIGQUIT received.");                                                                         
        break;                                                                                                          
#endif                                                                                                                  
    case SIGTERM:                                                                                                       
        msg = QObject::tr("SIGTERM received.");                                                                         
        break;                                                                                                          
    default:                                                                                                            
        msg = QObject::tr("Unknown signal received: %1" ).arg(signum);                                                  
    }
                                                                                                            
    std::clog << ": " << msg.toStdString() << std::endl;                                         
}

namespace tools {                                                                                                       
namespace runsocket {   

class RunSocket : public QCoreApplication                                                                                   
{                                                                                                                       
public:                                                                                                                 
    explicit RunSocket(int argc, char *argv[]) : QCoreApplication(argc, argv)
    {
        const QStringList args = this->arguments();
    
        if (args.count() != 5) {
            this->usage();
        } else {
            QHostAddress hostAddress;                                                                                           
            int port = 0;

            if (args.contains("-ip") && args.contains("-port")) {
                this->m_connection.host = args[2];                                                                                 
                this->m_connection.port = args[4].toInt();
            } else {
                this->usage();
            }
        }
    }

    virtual int run()
    {
        int go = EXIT_FAILURE;                                                                                              
                                                                                                                        
        try {                                                                                                               
            this->setup();                                                                                                  

            QHostAddress hostAddress;                                                                                           
            hostAddress.setAddress(this->m_connection.host);
                                                                                    
            QPointer<server::Tcp> server = new server::Tcp(0);                                                                                                                         
            bool ok = server->listen(hostAddress, this->m_connection.port);
                                                                                                
            if (ok) { 
                qInfo() << "The server is running on the IP: " + this->m_connection.host + 
                           " Port: " + QString::number(this->m_connection.port);
            } else {
                qCritical() << "Error starting server, check IP and port are correct...";
                return -1;
            }

            go = this->exec();                                                                                              
                                                                                                                        
        } catch (const std::exception &e) {
            qCritical() << "Error 1: " << QString::fromStdString(e.what());                                                                             
        } catch (const char *sz) {                                                                                          
            qCritical() << "Error 2: " << sz; 
        } catch (...) {
            qFatal("Unidentified error the program will exit.");
        }                                                                                                                   
                                                                                                                        
        return go; 
    }

protected:

    static void messageHandler(QtMsgType type, const QMessageLogContext &context,                                   
                               const QString &msg)
    {
        const QByteArray aux = msg.toLocal8Bit();                                                                           

        switch (type) {                                                                                                     
        case QtDebugMsg:                                                                                                    
            std::fprintf(stderr, "\033[1;31mSERVER-DEBUG-Handler> %s (%s:%u, %s)\033[0m\n", aux.constData(),                
                         context.file, context.line, context.function);                                                                                 
            break;                                                                                                          
        case QtWarningMsg:                                                                                                  
            std::fprintf(stderr, "\033[1;33mSERVER-WARN-Handler> %s (%s:%u, %s)\033[0m\n", aux.constData(),                 
                         context.file, context.line, context.function);                                                                                 
            break;                                                                                                          
        case QtCriticalMsg:                                                                                                                                                                        
            std::fprintf(stderr, "\033[1;36mSERVER-CRITICAL-Handler> %s (%s:%u, %s)\033[0m\n", aux.constData(),             
                         context.file, context.line, context.function);                                                                                 
        break;                                                                                                          
        case QtFatalMsg:                                                                                                    
            std::fprintf(stderr, "\033[1;31mSERVER-FATAL-Handler> %s (%s:%u, %s)\033[0m\n", aux.constData(),                
                         context.file, context.line, context.function);                                                                                 
            break;                                                                                                          
        case QtInfoMsg:                                                                       
            std::fprintf(stderr, "\033[1;32mSERVER-INFO-Handler> %s (%s:%u, %s)\033[0m\n", aux.constData(),                 
                         context.file, context.line, context.function);                                                                                 
            break;                                                                                                          
        default:                                                                                                            
            break;                                                                                                          
        }

        std::fflush(stderr);    
    }

    void setup()
    {
        qInstallMessageHandler(&messageHandler);
                                                                                                 
        std::signal(SIGABRT, signal_handler);                                                                               
        std::signal(SIGSEGV, signal_handler);                                                                               
        std::signal(SIGFPE,  signal_handler);                                                                               
        std::signal(SIGILL,  signal_handler);                                                                               
        std::signal(SIGINT,  signal_handler);                                                                               
#if defined(Q_OS_LINUX) || defined(Q_OS_FREEBSD) || defined(Q_OS_DARWIN)                                                
        std::signal(SIGQUIT, signal_handler);                                                                               
#endif                                                                                                                  
        std::signal(SIGTERM, signal_handler);
    }

    void usage()
    {
        std::cout << "Required arguments! Please use the IP and a port to start the server. E.g:\n\n";
        std::cout << "\t ./run-socket -ip 127.0.0.1 -port 5100\n" << std::endl;
        std::exit(0);
    }

    struct connection {
        QString host = QString();
        int port = 0;
    } m_connection;

};

} // Namespace.
} // Namespace.

int main(int argc, char *argv[])
{ 
    tools::runsocket::RunSocket app(argc, argv);
    return app.run();
}

