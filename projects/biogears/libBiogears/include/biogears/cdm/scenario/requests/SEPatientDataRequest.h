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
#include <biogears/cdm/scenario/requests/SEDataRequest.h>
#include <biogears/schema/cdm/Scenario.hxx>

namespace biogears {
class SEDataRequestManager;
namespace io {
  class Scenario;
}
class BIOGEARS_API SEPatientDataRequest : public SEDataRequest {
  friend class SEDataRequestManager;
  friend io::Scenario;


public:
  SEPatientDataRequest(const SEDecimalFormat* dfault = nullptr);
  virtual ~SEPatientDataRequest();

  virtual void Clear() override; //clear memory
  size_t HashCode() const override;
  virtual bool Load(const CDM::PatientDataRequestData& in);
  virtual CDM::PatientDataRequestData* Unload() const override;

protected:
  virtual void Unload(CDM::PatientDataRequestData& data) const;

public:
protected:
};
}