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
#include <string>

#include <biogears/cdm/patient/conditions/SEPatientCondition.h>
#include <biogears/exports.h>
#include <biogears/schema/cdm/PatientConditions.hxx>

namespace biogears {
class SEScalar0To1;
namespace io {
  class PatientConditions;
}
class BIOGEARS_API SEDehydration : public SEPatientCondition {
  friend io::PatientConditions;

public:
  SEDehydration();
  virtual ~SEDehydration();

  virtual void Clear(); //clear memory

  virtual bool IsValid() const;

  virtual bool Load(const CDM::DehydrationData& in);
  virtual CDM::DehydrationData* Unload() const;

protected:
  virtual void Unload(CDM::DehydrationData& data) const;

public:
  virtual std::string GetName() const { return "Dehydration"; }
  virtual const char* GetName_cStr() const { return "Dehydration"; }

  virtual bool HasDehydrationFraction() const;
  virtual SEScalar0To1& GetDehydrationFraction();

  virtual void ToString(std::ostream& str) const;

protected:
  SEScalar0To1* m_DehydrationFraction;
};
}