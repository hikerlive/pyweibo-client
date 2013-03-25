#include <pyweibo.h>
#include <Python.h>

static PyObject*
_login(PyObject* self, PyObject* args) {
	const char *username;
	const char *password;
	
	if (!PyArg_ParseTuple(args, "ss", &username, &password))
		return NULL;
		
	Py_BEGIN_ALLOW_THREADS
	login(username, password);
	Py_END_ALLOW_THREADS
	
	Py_RETURN_NONE;
}
static PyObject*
_logout(PyObject* self, PyObject* args) {
	const char *username;
	const char *password;
	
	if (!PyArg_ParseTuple(args, "ss", &username, &password))
		return NULL;
		
	Py_BEGIN_ALLOW_THREADS
	logout(username, password);
	Py_END_ALLOW_THREADS
	
	Py_RETURN_NONE;
}
static PyObject*
_get_weibo_tree(PyObject* self, PyObject* args) {
	const char *cursor_id = 0;
	int count = 0;
	char* j_weibos = 0;
	int len = 0;
	weibo_handle_t handle = 0;
	PyObject *result = 0;
	
	if (!PyArg_ParseTuple(args, "si", &cursor_id, &count))
		return NULL;
	
	Py_BEGIN_ALLOW_THREADS
	handle = get_weibo_tree(cursor_id, count, &j_weibos, &len);	
	Py_END_ALLOW_THREADS
	result = Py_BuildValue("s", j_weibos);
	free_weibo_handle(handle);
	
	return result;
}
static PyObject*
_get_weibo(PyObject* self, PyObject* args) {
	const char* msgid = 0;
	char* j_weibo = 0;
	int len = 0;
	weibo_handle_t handle = 0;
	PyObject *result = 0;
	
	if (!PyArg_ParseTuple(args, "s", &msgid))
		return NULL;
		
	Py_BEGIN_ALLOW_THREADS
	handle = get_weibo(msgid, &j_weibo, &len);
	Py_END_ALLOW_THREADS
	result = Py_BuildValue("s", j_weibo);
	free_weibo_handle(handle);
	
	return result;
}

static PyMethodDef Py4WeiboMethods[] = {
	{"login", _login, METH_VARARGS, "login"},
	{"logout", _logout, METH_VARARGS, "logout"},
	{"get_weibo_tree", _get_weibo_tree, METH_VARARGS, "get weibo by tree"},
	{"get_weibo", _get_weibo, METH_VARARGS, "get weibo by id"},
	{NULL, NULL, 0, NULL}
};

void
init_py4weibo() {
	PyObject* m;
	m = Py_InitModule("_py4weibo", Py4WeiboMethods);
	if (m == NULL)
		return;
}