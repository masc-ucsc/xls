// Copyright 2020 The XLS Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "absl/base/casts.h"
#include "absl/status/statusor.h"
#include "absl/strings/ascii.h"
#include "pybind11/functional.h"
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"
#include "xls/common/status/status_macros.h"
#include "xls/common/status/statusor_pybind_caster.h"
#include "xls/dslx/concrete_type.h"
#include "xls/dslx/deduce.h"
#include "xls/dslx/dslx_builtins.h"
#include "xls/dslx/import_routines.h"
#include "xls/dslx/interp_bindings.h"
#include "xls/dslx/python/callback_converters.h"
#include "xls/dslx/python/cpp_ast.h"
#include "xls/dslx/python/errors.h"

namespace py = pybind11;

namespace xls::dslx {

PYBIND11_MODULE(cpp_dslx_builtins, m) {
  ImportStatusModule();

  {
    std::set<std::string> parametric_builtin_names;
    for (const auto& item : GetParametricBuiltins()) {
      parametric_builtin_names.insert(item.first);
    }
    m.attr("PARAMETRIC_BUILTIN_NAMES") = std::move(parametric_builtin_names);
  }
  {
    std::unordered_set<std::string> value;
    for (const std::string& item : GetUnaryParametricBuiltinNames()) {
      value.insert(item);
    }
    m.attr("UNARY_PARAMETRIC_BUILTIN_NAMES") = std::move(value);
  }
}

}  // namespace xls::dslx
