/***
 *        Created:  2021-04-11

 *         Author:  Dilawar Singh <dilawar@subcom.tech>
 *    Description:  Python module of p0f (experimental).
 */

#include "pybind11/pybind11.h"
namespace py = pybind11;

#include <iostream>
using namespace std;

int p0f_start()
{
    cout << "Starting client." << endl;
    return 0;
}

PYBIND11_MODULE(p0f, m) 
{
    // m.doc() = "p0f experimental plugin.";

    // m.def("start", &p0f_start, "start the server.");

