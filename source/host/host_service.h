//
// PROJECT:         Aspia
// FILE:            host/host_service.h
// LICENSE:         GNU Lesser General Public License 2.1
// PROGRAMMERS:     Dmitry Chapyshev (dmitry@aspia.ru)
//

#ifndef _ASPIA_HOST__HOST_SERVICE_H
#define _ASPIA_HOST__HOST_SERVICE_H

#include "base/message_loop/message_loop_proxy.h"
#include "base/win/service.h"
#include "host/host_pool.h"

namespace aspia {

class HostService : public Service
{
public:
    HostService();

    enum Status
    {
        STATUS_INSTALLED = 1,
        STATUS_STARTED = 2
    };

    static uint32_t GetStatus();
    static bool Install();
    static bool Remove();
    static bool Start();
    static bool Stop();

private:
    // Service implementation.
    void Worker() override;
    void OnStop() override;

    std::shared_ptr<MessageLoopProxy> runner_;

    Q_DISABLE_COPY(HostService)
};

} // namespace aspia

#endif // _ASPIA_HOST__HOST_SERVICE_H
