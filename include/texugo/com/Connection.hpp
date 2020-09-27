#pragma once
#include "texugo/log/Logger.hpp"
#include <cstdlib>
#include <iostream>
#include <memory>
#include <queue>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

// Session Class
class Session: public std::enable_shared_from_this<Session> {
public:
    explicit Session(tcp::socket, short);
    void start();

private:
    void doRead();
    void doWrite(const std::string&);

    tcp::socket m_socket;
    enum { maxLength = 1024 };
    char m_data[maxLength]{};
    short m_port;
};

// Server Class
class Connection {
public:
    Connection(boost::asio::io_context&, short);
    void doAccept();
    void writeMessage(const std::string &message);

private:
    const short m_port;
    tcp::acceptor m_acceptor;
    boost::asio::io_context& m_ioContext;
};