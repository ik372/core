/**************************************************************************************
Copyright 2015 Applied Research Associates, Inc.
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
#include <biogears/cdm/patient/actions/SEPatientAction.h>
#include <biogears/schema/cdm/PatientActions.hxx>

namespace biogears {
namespace io {
  class PatientActions;
}
class BIOGEARS_API SEAtrialFibrillation : public SEPatientAction {
  friend io::PatientActions;

public:
  SEAtrialFibrillation();
  virtual ~SEAtrialFibrillation() override;

  static constexpr const char* TypeTag() { return "SEAtrialFibrillation"; };
  const char* classname() const override { return TypeTag(); }

  virtual void Clear() override; //clear memory

  virtual bool IsValid() const override;
  virtual bool IsActive() const override;
  virtual void SetActive(bool b);

  virtual bool Load(const CDM::AtrialFibrillationData& in);
  virtual CDM::AtrialFibrillationData* Unload() const override;

  virtual void ToString(std::ostream& str) const override;

  bool operator==(const SEAtrialFibrillation& rhs) const;
  bool operator!=(const SEAtrialFibrillation& rhs) const;

protected:
  virtual void Unload(CDM::AtrialFibrillationData& data) const;

protected:
  CDM::enumOnOff::value m_State;
};
}