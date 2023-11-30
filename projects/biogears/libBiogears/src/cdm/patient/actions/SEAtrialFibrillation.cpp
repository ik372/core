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

#include <biogears/cdm/patient/actions/SEAtrialFibrillation.h>

namespace biogears {
SEAtrialFibrillation::SEAtrialFibrillation()
  : SEPatientAction()
{
  m_State = CDM::enumOnOff::Off;
}
//-------------------------------------------------------------------------------
SEAtrialFibrillation::~SEAtrialFibrillation()
{
  Clear();
}
//-------------------------------------------------------------------------------
void SEAtrialFibrillation::Clear()
{
  SEPatientAction::Clear();
  m_State = CDM::enumOnOff::Off;
}
//-------------------------------------------------------------------------------
bool SEAtrialFibrillation::IsValid() const
{
  return SEPatientAction::IsValid();
}
//-------------------------------------------------------------------------------
bool SEAtrialFibrillation::IsActive() const
{
  return IsValid() && m_State == CDM::enumOnOff::On;
}
//-------------------------------------------------------------------------------
void SEAtrialFibrillation::SetActive(bool b)
{
  m_State = b ? CDM::enumOnOff::On : CDM::enumOnOff::Off;
}
//-------------------------------------------------------------------------------
bool SEAtrialFibrillation::Load(const CDM::AtrialFibrillationData& in)
{
  SEPatientAction::Load(in);
  m_State = in.State();
  return true;
}
//-------------------------------------------------------------------------------
CDM::AtrialFibrillationData* SEAtrialFibrillation::Unload() const
{
  CDM::AtrialFibrillationData* data(new CDM::AtrialFibrillationData());
  Unload(*data);
  return data;
}
//-------------------------------------------------------------------------------
void SEAtrialFibrillation::Unload(CDM::AtrialFibrillationData& data) const
{
  SEPatientAction::Unload(data);
  data.State(m_State);
}
//-------------------------------------------------------------------------------
void SEAtrialFibrillation::ToString(std::ostream& str) const
{
  str << "Patient Action : Atrial Fibrillation";
  if (HasComment())
    str << "\n\tComment: " << m_Comment;
  str << "\n\tState: " << IsActive();
  str << std::flush;
}
//-------------------------------------------------------------------------------
bool SEAtrialFibrillation::operator==(const SEAtrialFibrillation& rhs) const
{
  return m_Comment == rhs.m_Comment;
}
//-------------------------------------------------------------------------------
bool SEAtrialFibrillation::operator!=(const SEAtrialFibrillation& rhs) const
{
  return !(*this == rhs);
}
}