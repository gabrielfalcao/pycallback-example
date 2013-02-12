#include <stdio.h>
#include <string.h>
#include <Python.h>

#define color(code, format, ...) printf("\033[1;3"code"m"format"\033[0m", ##__VA_ARGS__)
#define gray(fmt, ...)           color("0", fmt, ##__VA_ARGS__)
#define red(fmt, ...)            color("1", fmt, ##__VA_ARGS__)
#define green(fmt, ...)          color("2", fmt, ##__VA_ARGS__)
#define yellow(fmt, ...)         color("3", fmt, ##__VA_ARGS__)
#define blue(fmt, ...)           color("4", fmt, ##__VA_ARGS__)
#define purple(fmt, ...)         color("5", fmt, ##__VA_ARGS__)
#define cyan(fmt, ...)           color("6", fmt, ##__VA_ARGS__)
#define white(fmt, ...)          color("7", fmt, ##__VA_ARGS__)


int main(int argc, char* argv[])
{
  PyObject *module = NULL;
  PyObject *module_name = NULL;
  PyObject *callback = NULL;
  PyObject *arguments = NULL;
  PyObject *retval = NULL;

  Py_SetProgramName(argv[0]);  /* optional but recommended */
  Py_Initialize();

  green("Will call a python callback with a string\n");
  module_name = PyString_FromString("progress");

  module = PyImport_Import(module_name);
  callback = PyObject_GetAttrString(module, "report_remote_reference");

  if (callback == NULL || !PyCallable_Check(callback)) {
    red("Please implement a function called 'report_remote_reference' inside the progress.py file\n");
    return 1;
  }
  arguments = PyTuple_New(1);
  PyTuple_SetItem(arguments, 0, PyString_FromString("foobar"));
  retval = PyObject_CallObject(callback, arguments);

  Py_DECREF(module_name);
  Py_DECREF(arguments);
  Py_DECREF(callback);
  Py_DECREF(module);
  Py_DECREF(retval);

  Py_Finalize();
  return 0;
}
