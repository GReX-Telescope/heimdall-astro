/***************************************************************************
 *
 *   Copyright (C) 2012 by Ben Barsdell and Andrew Jameson
 *   Licensed under the Academic Free License version 2.1
 *
 ***************************************************************************/

#ifndef CLIENT_SOCKET_HPP
#define CLIENT_SOCKET_HPP

#include "Socket.hpp"

class ClientSocket : private Socket {
public:
  ClientSocket(std::string host, int port);
  virtual ~ClientSocket(){};

  const ClientSocket &operator<<(const std::string &) const;
  const ClientSocket &operator<<(const char *) const;
  const ClientSocket &operator<<(const size_t n) const;
  const ClientSocket &operator<<(const float f) const;
  const ClientSocket &operator>>(std::string &) const;
};

#endif
