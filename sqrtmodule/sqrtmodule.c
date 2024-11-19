#define PY_SSIZE_T_CLEAN
#include<Python.h>

int closestSquare(double);
double power(double, int);
int factorial(int);
double mysqrt(double x, int n);

  static PyObject *
sqrt_system(PyObject *self, PyObject *args)
{
  double x;
  int n;

  if (!PyArg_ParseTuple(args, "di", &x, &n))
  {
    return NULL;
  }

  double output = mysqrt(x, n);

  return PyFloat_FromDouble(output);
}

static PyMethodDef SqrtMethods[] = {
  {"sqrt", sqrt_system, METH_VARARGS, "Approximate square root using Taylor's theorem"},
    {NULL, NULL, 0, NULL}
  };

  static struct PyModuleDef sqrtmodule = {
    PyModuleDef_HEAD_INIT,
    "sqrtmodule",
    NULL,
    -1,
    SqrtMethods
  };

  PyMODINIT_FUNC PyInit_sqrt(void) {
    return PyModule_Create(&sqrtmodule);
  }



  int closestSquare(double x)
  {
    int previousSquare = 0;
    int nextSquare = 0;

    while (nextSquare * nextSquare < x)
    {
      previousSquare = nextSquare++;
    }

    return (nextSquare * nextSquare - x) > (x - previousSquare * previousSquare) ? previousSquare : nextSquare;
  }

  double power(double base, int exp)
  {
    int negative = 0;
    if (exp < 0)
    {
      exp *= -1;
      negative = 1;
    }

    double output = 1;

    for (int i = 0; i < exp; i++)
    {
      output *= base;
    }

    return negative ? (1.0 / output) : output;
  }

  int factorial(int n)
  {
    return n > 2 ? n * factorial(n - 1) : n;
  }

  double mysqrt(double x, int n)
  {
    int cs = closestSquare(x);
    double approx = cs;

    double coefficient = 0.5;

    for (int k = 1; k <= n; k++)
    {
      approx += power(x - cs * cs, k) / factorial(k) * coefficient * power(cs, 1 - 2 * k);
      coefficient *= (1 - 2 * k) / 2.0;
    }

    return approx;
  }
