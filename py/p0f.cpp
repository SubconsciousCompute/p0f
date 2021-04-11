/***
 *        Created:  2021-04-11

 *         Author:  Dilawar Singh <dilawar@subcom.tech>
 *    Description:  Python module of p0f (experimental).
 */

#include <signal.h>
#include <string.h>
#include <unistd.h>

#include <fcntl.h>
#include <sys/stat.h>

#include <exception>

#include "../src/types.h"
#include "pybind11/pybind11.h"

namespace py = pybind11;
using namespace pybind11::literals;

#include <iostream>
using namespace std;

string socket_path_;
bool stop_soon_ = false;

extern "C"
{
    extern void http_init(void);

    extern void read_config(u8* fname);
}

void
abort_handler(int sig)
{
    if (stop_soon_)
        exit(1);
    stop_soon_ = true;
}

int
p0f_server_start(const string& api_sock,
                 size_t api_max_conn = 100,
                 const string& fp_file = "p0f.fp")
{
    socket_path_ = api_sock;

    cout << "--- p0f " VERSION
            " by Michal Zalewski <lcamtuf@coredump.cx> ---\n\n"
         << endl;

    if (getuid() != geteuid())
        throw std::runtime_error(
          "Please don't make me setuid. See README for more.\n");

    if (api_max_conn > 100)
        throw py::value_error("Outlandish value specified for api_max_conn.");

    cout << "Starting client: " << api_sock << endl;
    tzset();
    setlocale(LC_TIME, "C");

    // close_spare_fds();

    // get_hash_seed(); // todo:

    http_init();

    char* _fp_file = new char[fp_file.size() + 1];
    strcpy(_fp_file, fp_file.c_str());
    read_config((u8*)_fp_file);
    delete[] _fp_file;

    // prepare_pcap(); // todo
    // prepare_bpf();  // todo

    // if (log_file) open_log();
    // if (! api_sock.empty()) open_api();

    s32 null_fd = open("/dev/null", O_RDONLY);
    if (null_fd < 0)
        throw std::runtime_error("Cannot open '/dev/null'.");

    // bool switch_user = false;
    // if (switch_user)
    // drop_privs();

    // fork_off();

    signal(SIGHUP, SIG_IGN); // we are in daemon mode.
    signal(SIGINT, abort_handler);
    signal(SIGTERM, abort_handler);

    return 0;
}

int
p0f_server_stop()
{
    if (socket_path_.empty())
        cerr << "No socket found." << endl;

    cout << "Stoping client: " << socket_path_ << endl;
    return 0;
}

PYBIND11_MODULE(p0f, m)
{
    m.doc() = "p0f experimental plugin.";

    m.def("start", &p0f_server_start, "start the server.");
    m.def("stop", &p0f_server_stop, "stop the server.");

    m.attr("__version__") = VERSION;
}
