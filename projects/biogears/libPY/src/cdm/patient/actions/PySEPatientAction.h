/**************************************************************************************
Copyright 2021 Applied Research Associates, Inc.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use
this file except in compliance with the License. You may obtain a copy of the License
at:
http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License.
**************************************************************************************/

#pragma once

#include <pybind11/pybind11.h>

#include <biogears/cdm/patient/actions/SEPatientAction.h>

class PySEPatientAction : public biogears::SEPatientAction {
public:
  /* Inherit the constructors */
  using biogears::SEPatientAction::SEPatientAction;

  /* Trampoline (need one for each virtual function) */
  char const* classname() const override;

  /* Trampoline (need one for each virtual function) */
  CDM::PatientActionData* Unload() const override;

  /* Trampoline (need one for each virtual function) */
  void ToString(std::ostream& str) const;
};