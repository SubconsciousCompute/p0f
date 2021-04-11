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

int p0f_server(const string& socket)
{
    cout << "Starting client: " << socket << endl;
    return 0;
}

PYBIND11_MODULE(p0f, m)
{
    m.doc() = "p0f experimental plugin.";

    m.def("serve", &p0f_server, "start the server.");
}
