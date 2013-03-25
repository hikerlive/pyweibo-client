#include "sinaweibo.h"
#include <python.h>

PyObject* 
_getdata(PyObject* self, PyObject* args) {
	const char* result = getData();
	return Py_BuildValue("s", result);
}

static PyMethodDef Py4ExampleMethods[] = {
	{"getdata", _getdata, METH_VARARGS, "getdata N!"},
	{NULL, NULL}
};

void
init_py4example() {
	PyObject* m;
	m = Py_InitModule("_py4example", Py4ExampleMethods);
	if (m == NULL)
		return;
}