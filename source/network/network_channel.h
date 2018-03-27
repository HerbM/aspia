//
// PROJECT:         Aspia
// FILE:            network/network_channel.h
// LICENSE:         GNU Lesser General Public License 2.1
// PROGRAMMERS:     Dmitry Chapyshev (dmitry@aspia.ru)
//

#ifndef _ASPIA_NETWORK__NETWORK_CHANNEL_H
#define _ASPIA_NETWORK__NETWORK_CHANNEL_H

#include <QByteArray>
#include <functional>

namespace aspia {

class NetworkChannelProxy;

class NetworkChannel
{
public:
    NetworkChannel();
    virtual ~NetworkChannel();

    enum class Status { CONNECTED, DISCONNECTED };

    using StatusChangeHandler = std::function<void(Status status)>;
    using SendCompleteHandler = std::function<void()>;
    using ReceiveCompleteHandler = std::function<void(QByteArray& buffer)>;

    virtual void StartChannel(StatusChangeHandler status_change_callback) = 0;

    std::shared_ptr<NetworkChannelProxy> network_channel_proxy() const;

protected:
    friend class NetworkChannelProxy;

    virtual void Send(QByteArray&& buffer, SendCompleteHandler handler) = 0;
    virtual void Send(QByteArray&& buffer) = 0;
    virtual void Receive(ReceiveCompleteHandler handler) = 0;
    virtual void Disconnect() = 0;
    virtual bool IsDiconnecting() const = 0;

private:
    std::shared_ptr<NetworkChannelProxy> proxy_;

    Q_DISABLE_COPY(NetworkChannel)
};

} // namespace aspia

#endif // _ASPIA_NETWORK__NETWORK_CHANNEL_H
