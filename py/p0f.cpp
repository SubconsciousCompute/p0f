/***
 *        Created:  2021-04-11

 *         Author:  Dilawar Singh <dilawar@subcom.tech>
 *    Description:  Python module of p0f (experimental).
 */

#include "pybind11/pybind11.h"

namespace py = pybind11;
using namespace pybind11::literals;

#include <iostream>
using namespace std;


string socket_path_;


int p0f_server_start(const string& socket)
{
    socket_path_ = socket;
    cout << "Starting client: " << socket << endl;

    return 0;
}

int p0f_server_stop()
{
    if(socket_path_.empty())
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
