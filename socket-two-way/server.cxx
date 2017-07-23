/**                                                                                                                     
 * @file                                                                                                                
 *                                                                                                                      
 * Implementation for an server.                                                                                           
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
#ifndef SERVER_SERVER_HXX
#include "server.hxx"
#endif

// Qt.
#include <QtCore>

// Start static variable and objects.
server::Server *server::Server::m_instance = nullptr;

namespace server {

Server *Server::getInstance()
{
    if (m_instance == nullptr) {
        m_instance = new Server(0);
        Q_CHECK_PTR(m_instance);
    }
    return m_instance;
}

std::string Server::printLibName() const
{
    return std::string(LIB_NAME); 
}

std::string Server::printVersion()
{
    return std::string(LIB_VERSION);
}

QByteArray Server::printJsonServerInfo() const
{
    qInfo() << QString::fromStdString(this->self.NAME) + ": Print json server information.";

    QJsonObject jsonObject = QJsonObject();
    jsonObject.insert("version", QJsonValue(QString::fromStdString(this->printVersion())));
    jsonObject.insert("name", QJsonValue(QString::fromStdString(this->printLibName())));

    QJsonArray jsonArray = QJsonArray();
    QJsonObject jsonMachine = QJsonObject();

    jsonMachine.insert("productVersion", QJsonValue(QSysInfo::productVersion()));
    jsonMachine.insert("kernelType", QJsonValue(QSysInfo::kernelType()));
    jsonMachine.insert("cpuBuilArch", QJsonValue(QSysInfo::buildCpuArchitecture()));
    jsonMachine.insert("currentCpuArch", QJsonValue(QSysInfo::currentCpuArchitecture()));
    jsonMachine.insert("hostName", QJsonValue(QSysInfo::machineHostName()));

    jsonArray.append(jsonMachine);
    jsonObject.insert("machine", jsonArray);

    QJsonDocument jsonDocument = QJsonDocument(jsonObject);
    return QByteArray(jsonDocument.toJson());
}

} // Namespace.
