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

#include <iostream>
#include <string>
#include <fstream>

#include "AMLInterface.h"
#include "AMLException.h"
#include "gtest/gtest.h"

using namespace std;

namespace AMLInterfaceTest
{
    // Helper Method
    bool isEqual(vector<string>& vecStr1, vector<string>& vecStr2)
    {
        if (vecStr1.size() != vecStr2.size())     return false;
        if (false == std::equal(vecStr1.begin(), vecStr1.end(), vecStr2.begin())) return false;

        return true;
    }

    bool isPresent(string str, vector<string> vector)
    {
        if (find(vector.begin(), vector.end(), str) != vector.end()) return true;

        return false;
    }

    // Test
    TEST(AMLData_setValueStrTest, Valid)
    {
        AMLData amlData;

        string key = "key";
        string value = "value";

        EXPECT_NO_THROW(amlData.setValue(key, value));
    }

    TEST(AMLData_setValueStrTest, Invalid_DuplicatedKey)
    {
        AMLData amlData;

        string key = "key";
        string value = "value";

        EXPECT_NO_THROW(amlData.setValue(key, value));
        EXPECT_THROW(amlData.setValue(key, value), AMLException);
    }

    TEST(AMLData_setValueStrArrTest, Valid)
    {
        AMLData amlData;

        string key = "key";
        vector<string> value = {"value"};

        EXPECT_NO_THROW(amlData.setValue(key, value));
    }

    TEST(AMLData_setValueStrArrTest, Invalid_DuplicatedKey)
    {
        AMLData amlData;

        string key = "key";
        vector<string> value = {"value"};

        EXPECT_NO_THROW(amlData.setValue(key, value));
        EXPECT_THROW(amlData.setValue(key, value), AMLException);
    }

    TEST(AMLData_setValueAMLDataTest, Valid)
    {
        AMLData amlData;

        string key = "key";
        AMLData value;

        EXPECT_NO_THROW(amlData.setValue(key, value));
    }

    TEST(AMLData_setValueAMLDataTest, Invalid_DuplicatedKey)
    {
        AMLData amlData;

        string key = "key";
        AMLData value;

        EXPECT_NO_THROW(amlData.setValue(key, value));
        EXPECT_THROW(amlData.setValue(key, value), AMLException);
    }

    TEST(AMLData_getValueStrTest, Valid)
    {
        AMLData amlData;

        string key = "key";
        string value = "value";

        EXPECT_NO_THROW(amlData.setValue(key, value));
        EXPECT_TRUE(value == amlData.getValueToStr(key));
    }

    TEST(AMLData_getValueStrTest, InvalidGetterType)
    {
        AMLData amlData;

        string key = "key";
        string value = "value";

        EXPECT_NO_THROW(amlData.setValue(key, value));

        vector<string> arrayVal;
        EXPECT_THROW(arrayVal = amlData.getValueToStrArr(key), AMLException);
    }

    TEST(AMLData_getValueStrArrTest, Valid)
    {
        AMLData amlData;

        string key = "key";
        vector<string> value = {"value"};

        EXPECT_NO_THROW(amlData.setValue(key, value));

        vector<string> getvalue = amlData.getValueToStrArr(key);
        EXPECT_TRUE(isEqual(value, getvalue));
    }

    TEST(AMLData_getValueStrArrTest, InvalidGetterType)
    {
        AMLData amlData;

        string key = "key";
        vector<string> value = {"value"};

        EXPECT_NO_THROW(amlData.setValue(key, value));

        string strVal;
        EXPECT_THROW(strVal = amlData.getValueToStr(key), AMLException);
    }

    TEST(AMLData_getKeys, Valid)
    {
        AMLData amlData;

        string key1 = "key1";
        string value1 = "value1";

        string key2 = "key2";
        vector<string> value2 = {"value2"};

        string key3 = "key3";
        AMLData value3;

        EXPECT_NO_THROW(amlData.setValue(key1, value1));
        EXPECT_NO_THROW(amlData.setValue(key2, value2));
        EXPECT_NO_THROW(amlData.setValue(key3, value3));

        vector<string> keys = amlData.getKeys();

        EXPECT_TRUE(isPresent(key1, keys));
        EXPECT_TRUE(isPresent(key2, keys));
        EXPECT_TRUE(isPresent(key3, keys));
        EXPECT_FALSE(isPresent("key4", keys));
    }

    TEST(AMLData_getValueType, Valid)
    {
        AMLData amlData;

        string key1 = "key1";
        string value1 = "value1";

        string key2 = "key2";
        vector<string> value2 = {"value2"};

        string key3 = "key3";
        AMLData value3;

        EXPECT_NO_THROW(amlData.setValue(key1, value1));
        EXPECT_NO_THROW(amlData.setValue(key2, value2));
        EXPECT_NO_THROW(amlData.setValue(key3, value3));

        EXPECT_TRUE(amlData.getValueType(key1) == AMLValueType::String);
        EXPECT_TRUE(amlData.getValueType(key2) == AMLValueType::StringArray);
        EXPECT_TRUE(amlData.getValueType(key3) == AMLValueType::AMLData);
    }

    TEST(AMLData_getValueType, InvalidKey)
    {
        AMLData amlData;

        string key1 = "key1";
        string value1 = "value1";

        string key2 = "key2";
        vector<string> value2 = {"value2"};

        string key3 = "key3";
        AMLData value3;

        EXPECT_NO_THROW(amlData.setValue(key1, value1));
        EXPECT_NO_THROW(amlData.setValue(key2, value2));
        EXPECT_NO_THROW(amlData.setValue(key3, value3));

        EXPECT_THROW(amlData.getValueType("key4"), AMLException);
    }

    // AMLObject Test
    TEST(AMLObjectTest, ConstructWithId)
    {
        string deviceId = "deviceId";
        string timeStamp = "timeStamp";
        string id = "id";

        AMLObject amlObj(deviceId, timeStamp, id);

        EXPECT_TRUE(amlObj.getDeviceId() == deviceId);
        EXPECT_TRUE(amlObj.getTimeStamp() == timeStamp);
        EXPECT_TRUE(amlObj.getId() == id);
    }

    TEST(AMLObjectTest, ConstructWithoutId)
    {
        string deviceId = "deviceId";
        string timeStamp = "timeStamp";

        AMLObject amlObj(deviceId, timeStamp);

        EXPECT_TRUE(amlObj.getDeviceId() == deviceId);
        EXPECT_TRUE(amlObj.getTimeStamp() == timeStamp);

        string id = deviceId + "_" + timeStamp;
        EXPECT_TRUE(amlObj.getId() == id);
    }

    TEST(AMLObjectTest, addData)
    {
        AMLData amlData;
        EXPECT_NO_THROW(amlData.setValue("key", "value"));

        AMLData amlData2;
        EXPECT_NO_THROW(amlData2.setValue("key2", "value2"));

        AMLObject amlObj("deviceId", "timeStamp");

        string dataName = "dataName";

        EXPECT_NO_THROW(amlObj.addData(dataName, amlData));
        EXPECT_THROW(amlObj.addData(dataName, amlData2), AMLException);
    }

    TEST(AMLObjectTest, getData)
    {
        AMLData amlData;
        string key = "key";
        string value = "value";
        EXPECT_NO_THROW(amlData.setValue(key, value));

        AMLObject amlObj("deviceId", "timeStamp");

        string dataName = "dataName";

        EXPECT_NO_THROW(amlObj.addData(dataName, amlData));

        AMLData amlData_get;
        EXPECT_NO_THROW(amlData_get = amlObj.getData(dataName));
        EXPECT_TRUE(value == amlData_get.getValueToStr(key));

        EXPECT_THROW(amlObj.getData("invalid_dataName"), AMLException);
    }
}