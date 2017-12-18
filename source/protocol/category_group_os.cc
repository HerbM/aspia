//
// PROJECT:         Aspia
// FILE:            protocol/category_group_os.cc
// LICENSE:         Mozilla Public License Version 2.0
// PROGRAMMERS:     Dmitry Chapyshev (dmitry@aspia.ru)
//

#include "base/user_enumerator.h"
#include "base/user_group_enumerator.h"
#include "base/session_enumerator.h"
#include "base/datetime.h"
#include "protocol/category_group_os.h"
#include "proto/system_info_session_message.pb.h"
#include "ui/system_info/output.h"
#include "ui/resource.h"

namespace aspia {

//
// CategoryTaskScheduler
//

const char* CategoryTaskScheduler::Name() const
{
    return "Task Scheduler";
}

Category::IconId CategoryTaskScheduler::Icon() const
{
    return IDI_CLOCK;
}

const char* CategoryTaskScheduler::Guid() const
{
    return "{1B27C27F-847E-47CC-92DF-6B8F5CB4827A}";
}

void CategoryTaskScheduler::Parse(Table& /* table */, const std::string& /* data */)
{
    // TODO
}

std::string CategoryTaskScheduler::Serialize()
{
    // TODO
    return std::string();
}

//
// CategoryEnvironmentVariables
//

const char* CategoryEnvironmentVariables::Name() const
{
    return "Environment Variables";
}

Category::IconId CategoryEnvironmentVariables::Icon() const
{
    return IDI_APPLICATIONS;
}

const char* CategoryEnvironmentVariables::Guid() const
{
    return "{AAB8670A-3C90-4F75-A907-512ACBAD1BE6}";
}

void CategoryEnvironmentVariables::Parse(Table& /* table */, const std::string& /* data */)
{
    // TODO
}

std::string CategoryEnvironmentVariables::Serialize()
{
    // TODO
    return std::string();
}

//
// CategoryEventLogsApplications
//

const char* CategoryEventLogsApplications::Name() const
{
    return "Applications";
}

Category::IconId CategoryEventLogsApplications::Icon() const
{
    return IDI_ERROR_LOG;
}

const char* CategoryEventLogsApplications::Guid() const
{
    return "{0DD03A20-D1AF-4D1F-938F-956EE9003EE9}";
}

void CategoryEventLogsApplications::Parse(Table& /* table */, const std::string& /* data */)
{
    // TODO
}

std::string CategoryEventLogsApplications::Serialize()
{
    // TODO
    return std::string();
}

//
// CategoryEventLogsSecurity
//

const char* CategoryEventLogsSecurity::Name() const
{
    return "Security";
}

Category::IconId CategoryEventLogsSecurity::Icon() const
{
    return IDI_ERROR_LOG;
}

const char* CategoryEventLogsSecurity::Guid() const
{
    return "{7E0220A8-AC51-4C9E-8834-F0F805D40977}";
}

void CategoryEventLogsSecurity::Parse(Table& /* table */, const std::string& /* data */)
{
    // TODO
}

std::string CategoryEventLogsSecurity::Serialize()
{
    // TODO
    return std::string();
}

//
// CategoryEventLogsSystem
//

const char* CategoryEventLogsSystem::Name() const
{
    return "System";
}

Category::IconId CategoryEventLogsSystem::Icon() const
{
    return IDI_ERROR_LOG;
}

const char* CategoryEventLogsSystem::Guid() const
{
    return "{8421A38A-4757-4298-A5CB-9493C7726515}";
}

void CategoryEventLogsSystem::Parse(Table& /* table */, const std::string& /* data */)
{
    // TODO
}

std::string CategoryEventLogsSystem::Serialize()
{
    // TODO
    return std::string();
}

//
// CategoryGroupEventLog
//

const char* CategoryGroupEventLog::Name() const
{
    return "Event Logs";
}

Category::IconId CategoryGroupEventLog::Icon() const
{
    return IDI_BOOKS_STACK;
}

//
// CategoryUsers
//

const char* CategoryUsers::Name() const
{
    return "Users";
}

Category::IconId CategoryUsers::Icon() const
{
    return IDI_USER;
}

const char* CategoryUsers::Guid() const
{
    return "{838AD22A-82BB-47F2-9001-1CD9714ED298}";
}

void CategoryUsers::Parse(Table& table, const std::string& data)
{
    proto::Users message;

    if (!message.ParseFromString(data))
        return;

    table.AddColumns(ColumnList::Create()
                     .AddColumn("Parameter", 250)
                     .AddColumn("Value", 250));

    for (int index = 0; index < message.item_size(); ++index)
    {
        const proto::Users::Item& item = message.item(index);

        Group group = table.AddGroup(item.name());

        if (!item.full_name().empty())
            group.AddParam("Full Name", Value::String(item.full_name()));

        if (!item.comment().empty())
            group.AddParam("Description", Value::String(item.comment()));

        group.AddParam("Disabled", Value::Bool(item.is_disabled()));
        group.AddParam("Password Can't Change", Value::Bool(item.is_password_cant_change()));
        group.AddParam("Password Expired", Value::Bool(item.is_password_expired()));
        group.AddParam("Don't Expire Password", Value::Bool(item.is_dont_expire_password()));
        group.AddParam("Lockout", Value::Bool(item.is_lockout()));
        group.AddParam("Last Logon", Value::String(TimeToString(item.last_logon_time())));
        group.AddParam("Number Logons", Value::Number(item.number_logons()));
        group.AddParam("Bad Password Count", Value::Number(item.bad_password_count()));
    }
}

std::string CategoryUsers::Serialize()
{
    proto::Users message;

    for (UserEnumerator enumerator; !enumerator.IsAtEnd(); enumerator.Advance())
    {
        proto::Users::Item* item = message.add_item();

        item->set_name(enumerator.GetName());
        item->set_full_name(enumerator.GetFullName());
        item->set_comment(enumerator.GetComment());
        item->set_is_disabled(enumerator.IsDisabled());
        item->set_is_password_cant_change(enumerator.IsPasswordCantChange());
        item->set_is_password_expired(enumerator.IsPasswordExpired());
        item->set_is_dont_expire_password(enumerator.IsDontExpirePassword());
        item->set_is_lockout(enumerator.IsLockout());
        item->set_number_logons(enumerator.GetNumberLogons());
        item->set_bad_password_count(enumerator.GetBadPasswordCount());
        item->set_last_logon_time(enumerator.GetLastLogonTime());
    }

    return message.SerializeAsString();
}

//
// CategoryUserGroups
//

const char* CategoryUserGroups::Name() const
{
    return "User Groups";
}

Category::IconId CategoryUserGroups::Icon() const
{
    return IDI_USERS;
}

const char* CategoryUserGroups::Guid() const
{
    return "{B560FDED-5E88-4116-98A5-12462C07AC90}";
}

void CategoryUserGroups::Parse(Table& table, const std::string& data)
{
    proto::UserGroups message;

    if (!message.ParseFromString(data))
        return;

    table.AddColumns(ColumnList::Create()
                     .AddColumn("Group Name", 250)
                     .AddColumn("Description", 250));

    for (int index = 0; index < message.item_size(); ++index)
    {
        const proto::UserGroups::Item& item = message.item(index);

        Row row = table.AddRow();
        row.AddValue(Value::String(item.name()));
        row.AddValue(Value::String(item.comment()));
    }
}

std::string CategoryUserGroups::Serialize()
{
    proto::UserGroups message;

    for (UserGroupEnumerator enumerator; !enumerator.IsAtEnd(); enumerator.Advance())
    {
        proto::UserGroups::Item* item = message.add_item();

        item->set_name(enumerator.GetName());
        item->set_comment(enumerator.GetComment());
    }

    return message.SerializeAsString();
}

//
// CategoryActiveSessions
//

const char* CategoryActiveSessions::Name() const
{
    return "Active Sessions";
}

Category::IconId CategoryActiveSessions::Icon() const
{
    return IDI_USERS;
}

const char* CategoryActiveSessions::Guid() const
{
    return "{8702E4A1-C9A2-4BA3-BBDE-CFCB6937D2C8}";
}

void CategoryActiveSessions::Parse(Table& table, const std::string& data)
{
    proto::Sessions message;

    if (!message.ParseFromString(data))
        return;

    table.AddColumns(ColumnList::Create()
                     .AddColumn("User Name", 150)
                     .AddColumn("Domain", 100)
                     .AddColumn("ID", 50)
                     .AddColumn("State", 80)
                     .AddColumn("Client Name", 100)
                     .AddColumn("Logon Type", 100));

    for (int index = 0; index < message.item_size(); ++index)
    {
        const proto::Sessions::Item& item = message.item(index);

        Row row = table.AddRow();
        row.AddValue(Value::String(item.user_name()));
        row.AddValue(Value::String(item.domain_name()));
        row.AddValue(Value::Number(item.session_id()));
        row.AddValue(Value::String(ConnectStateToString(item.connect_state())));
        row.AddValue(Value::String(item.client_name()));
        row.AddValue(Value::String(item.winstation_name()));
    }
}

std::string CategoryActiveSessions::Serialize()
{
    proto::Sessions message;

    for (SessionEnumerator enumerator; !enumerator.IsAtEnd(); enumerator.Advance())
    {
        proto::Sessions::Item* item = message.add_item();

        item->set_user_name(enumerator.GetUserName());
        item->set_domain_name(enumerator.GetDomainName());
        item->set_session_id(enumerator.GetSessionId());
        item->set_connect_state(enumerator.GetConnectState());
        item->set_client_name(enumerator.GetClientName());
        item->set_winstation_name(enumerator.GetWinStationName());
    }

    return message.SerializeAsString();
}

// static
const char* CategoryActiveSessions::ConnectStateToString(proto::Sessions::ConnectState value)
{
    switch (value)
    {
        case proto::Sessions::CONNECT_STATE_ACTIVE:
            return "Active";

        case proto::Sessions::CONNECT_STATE_CONNECTED:
            return "Connected";

        case proto::Sessions::CONNECT_STATE_CONNECT_QUERY:
            return "Connect Query";

        case proto::Sessions::CONNECT_STATE_SHADOW:
            return "Shadow";

        case proto::Sessions::CONNECT_STATE_DISCONNECTED:
            return "Disconnected";

        case proto::Sessions::CONNECT_STATE_IDLE:
            return "Idle";

        case proto::Sessions::CONNECT_STATE_LISTEN:
            return "Listen";

        case proto::Sessions::CONNECT_STATE_RESET:
            return "Reset";

        case proto::Sessions::CONNECT_STATE_DOWN:
            return "Down";

        case proto::Sessions::CONNECT_STATE_INIT:
            return "Init";

        default:
            return "Unknown";
    }
}

//
// CategoryGroupUsers
//

const char* CategoryGroupUsers::Name() const
{
    return "Users and groups";
}

Category::IconId CategoryGroupUsers::Icon() const
{
    return IDI_USERS;
}

//
// CategoryGroupOS
//

const char* CategoryGroupOS::Name() const
{
    return "Operating System";
}

Category::IconId CategoryGroupOS::Icon() const
{
    return IDI_OS;
}

} // namespace aspia