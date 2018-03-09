/*******************************************************************************
 * Copyright 2018 Samsung Electronics All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *******************************************************************************/

#include <string>
#include <map>
#include <vector>

#include "AMLInterface.h"
#include "AMLException.h"

using namespace std;

/*
 * "id" is automatically created using "deviceId" and "timeStamp".
 * e.g.) "deviceId" : "Robot", "timeStamp" : "001" -> "id" : "Robot_001"
 */
AMLObject::AMLObject(const std::string& deviceId, const std::string& timeStamp)
 : m_deviceId(deviceId), m_timeStamp(timeStamp), m_id(deviceId + "_" + timeStamp)
{
}

AMLObject::AMLObject(const std::string& deviceId, const std::string& timeStamp, const std::string& id)
 : m_deviceId(deviceId), m_timeStamp(timeStamp), m_id(id)
{
}

AMLObject::~AMLObject(void)
{
}

void AMLObject::addData(const std::string& name, const AMLData& data)
{
    // Try to insert a new element into the map and if the key already exists, throw an exeption.
    if (!m_amlDatas.insert(make_pair(name, data)).second)
    {
        throw AMLException(Exception::KEY_ALREADY_EXIST);
    }
}

AMLData AMLObject::getData(const std::string& name) const
{
    map<string, AMLData>::iterator iter = m_amlDatas.find(name);
    if (iter == m_amlDatas.end())
    {
        // The name does not exist.
        throw AMLException(Exception::KEY_NOT_EXIST);
    }

    return iter->second;
}

vector<string> AMLObject::getDataNames() const
{
    vector<string> dataNames;
    for (auto const& iter : m_amlDatas)
    {
        dataNames.push_back(iter.first);
    }

    return dataNames;
}

std::string AMLObject::getDeviceId() const
{
    return m_deviceId;
}

std::string AMLObject::getTimeStamp() const
{
    return m_timeStamp;
}

std::string AMLObject::getId() const
{
    return m_id;
}