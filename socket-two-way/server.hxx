/**                                                                                                                     
 * @file                                                                                                                
 *                                                                                                                      
 * Definitions for an server.                                                                                           
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
#ifndef SERVER_SERVER_HXX
#define SERVER_SERVER_HXX

// Application.
#include "global.hxx"

// Qt.
#include <QObject>
#include <QString>
#include <QByteArray>

// STD.
#include <string>

namespace server {
/**
 * @brief The Server Class.
 *
 * Base class of the server library.
 */
class SERVER_SHARED_EXPORT Server : public QObject
{
public:
    /// Properties of Server Class.
    struct self {
        std::string NAME; ///< Name of this class.
    } ///< Initialize objects.
    self = {
        this->metaObject()->className()
    };

    /// Class name, used in static methods.
    static constexpr const char *NAME = "Server*";

    /**                                                                                                                 
     * Constructor.                                                                                                     
     *                                                                                                                  
     * @param parent Object parent.                                                                                     
     */                                                                                                                 
    Server(QObject *parent = Q_NULLPTR) : QObject(parent)
    {
    }

    /**
     * Destructor.
     */
    ~Server() = default;

    /**
     * Singleton design pattern.
     *
     * @return An instance of the class.
     */
    static Server *getInstance();

    /**
     * Print name librarie.
     *
     * @return Librarie name.
     */
    std::string printLibName() const;

    /**
     * Print version librarie.
     *
     * @return Return version.
     */
    static std::string printVersion();

    /**
     * Print json server information.
     *
     * @return Return json server information.
     */
    QByteArray printJsonServerInfo() const;

protected:
    /// Instance server reference.
    static Server *m_instance;
};

} // Namespace.

#endif // SERVER_SERVER_HXX
