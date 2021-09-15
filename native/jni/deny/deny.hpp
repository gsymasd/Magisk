#pragma once

#include <pthread.h>
#include <string_view>
#include <functional>
#include <map>

#include <daemon.hpp>

#define SIGTERMTHRD SIGUSR1
#define ISOLATED_MAGIC "isolated"

// CLI entries
int enable_hide(bool late_props);
int disable_deny();
int add_list(int client);
int rm_list(int client);
void ls_list(int client);

// Process monitoring
extern pthread_t monitor_thread;
[[noreturn]] void proc_monitor();

// Utility functions
bool deny_enforced();
bool is_deny_target(int uid, std::string_view process, int max_len = 1024);
void crawl_procfs(const std::function<bool(int)> &fn);
void rebuild_uid_map();

// Revert
void revert_daemon(int pid, int client);
void revert_unmount(int pid = -1);

// props
void hide_sensitive_props();
void hide_late_sensitive_props();

enum : int {
    ENFORCE_DENY,
    DISABLE_DENY,
    ADD_LIST,
    RM_LIST,
    LS_LIST,
    DENY_STATUS,
};

enum : int {
    DENY_IS_ENFORCED = DAEMON_LAST + 1,
    DENY_NOT_ENFORCED,
    DENYLIST_ITEM_EXIST,
    DENYLIST_ITEM_NOT_EXIST,
    DENYLIST_INVALID_PKG,
    DENY_NO_NS,
};
