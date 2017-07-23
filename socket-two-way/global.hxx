/**
 * @file
 *
 * Definitions for an global.
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
#ifndef SERVER_GLOBAL_HXX
#define SERVER_GLOBAL_HXX

// Qt.
#include <QtCore/qglobal.h>

#if defined(SERVER_LIBRARY)
#define SERVER_SHARED_EXPORT Q_DECL_EXPORT
#else
#define SERVER_SHARED_EXPORT Q_DECL_IMPORT
#endif

/// Namespace that contains access to the server module.
namespace server {

/// Namespace that contains access to the server commands.
namespace command {

/// Lists all (open) orders found on the server.
constexpr const char *SELECT = "SELECT";

/// Shows server information, eg: memory, processor, etc...
constexpr const char *INFO_SERVER = "INFO_SERVER";

/// Command called by server wheen error is unknown.
constexpr const char *ERROR_UNKNOWN_COMMAND = "ERROR_UNKNOWN_COMMAND";

} // Namespace.
} // Namespace.

#endif // SERVER_GLOBAL_HXX
