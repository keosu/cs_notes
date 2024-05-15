#include <pybind11/functional.h>
#include <pybind11/pybind11.h>

using PyCallbackFunc = std::function<void(pybind11::object)>;
 

// 通过Context类型包装，适配CallbackFunc回调接口
void test_pycallback(pybind11::object userData, PyCallbackFunc cb) { 
  pybind11::gil_scoped_acquire gil;
  cb(userData);
}

PYBIND11_MODULE(CallBack, m) {
  m.doc() = "pybind11 callback demo";
  m.def("test_pycallback", &test_pycallback);
}
