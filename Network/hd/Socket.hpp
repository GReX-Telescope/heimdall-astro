/***************************************************************************
 *
 *   Copyright (C) 2012 by Ben Barsdell and Andrew Jameson
 *   Licensed under the Academic Free License version 2.1
 *
 ***************************************************************************/

#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

const int MAXHOSTNAME = 200;
const int MAXCONNECTIONS = 5;
const int MAXRECV = 500;

class Socket {
public:
  Socket();
  virtual ~Socket();

  // Server initialization
  bool create();
  bool bind(const char *address, const int port);
  bool listen() const;
  bool accept(Socket &) const;

  // Client initialization
  bool connect(const std::string host, const int port);

  // Data Transimission
  bool send(const std::string) const;
  int recv(std::string &) const;

  void set_non_blocking(const bool);

  bool is_valid() const { return m_sock != -1; }

  int select_timeout(float sleep_secs);

private:
  int m_sock;

  sockaddr_in m_addr;
};

#endif
