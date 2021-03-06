/*L*************************************************************************************************
*
*  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
* 
*  By downloading, copying, installing or using the software you agree to this license. If you do 
*  not agree to this license, do not download, install, copy or use the software.
*
*                            Software License Agreement (BSD License)
*                               For Smart Surveillance Framework
*                                 http://ssig.dcc.ufmg.br/ssf/
*
*  Copyright (c) 2013, Smart Surveillance Interest Group, all rights reserved.
*  
*  Redistribution and use in source and binary forms, with or without modification, are permitted 
*  provided that the following conditions are met:
*
*    1. Redistributions of source code must retain the above copyright notice, this list of 
*       conditions and the following disclaimer.
*
*    2. Redistributions in binary form must reproduce the above copyright notice, this list of 
*       conditions and the following disclaimer in the documentation and/or other materials 
*       provided with the distribution.
*
*    3. Neither the name of the copyright holder nor the names of its contributors may be used to 
*       endorse or promote products derived from this software without specific prior written 
*       permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR 
*  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY 
*  AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
*  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
*  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
*  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
*  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
*  POSSIBILITY OF SUCH DAMAGE.
*************************************************************************************************L*/

#include "core/parameter.hpp"

#include <boost/lexical_cast.hpp>

#include "core/param_exception.hpp"


namespace ssf{

	Parameter::Parameter(void){
		this->mExpectedType = ParamType::STRING;
		this->mName = "";
		this->mDescription = "";
		this->mRequired = false;
	}

	Parameter::Parameter(const std::string& name, const int& defaultValue, const std::string& description /*= "no description."*/)
		: mName(name), mDescription(description){
		std::string convertString = std::to_string(defaultValue);
		this->mDefaultValue.push_back(convertString);
		this->mValue.push_back(convertString);
		this->mRequired = false;
		this->mExpectedType = ParamType::INT;
	}

	Parameter::Parameter(const std::string& name, const double& defaultValue, const std::string& description /*= "no description."*/)
		: mName(name), mDescription(description){

		//std::ostringstream out;
		//out << std::fixed << std::setprecision(5) << defaultValue;
		//std::string convertString = out.str();
		std::string convertString = std::to_string(defaultValue);
		this->mDefaultValue.push_back(convertString);
		this->mValue.push_back(convertString);
		this->mRequired = false;
		this->mExpectedType = ParamType::DOUBLE;
	}

	Parameter::Parameter(const std::string& name, const bool& defaultValue, const std::string& description /*= "no description."*/)
		: mName(name), mDescription(description){
		std::string convertString = defaultValue ? "true" : "false";
		this->mDefaultValue.push_back(convertString);
		this->mValue.push_back(convertString);
		this->mRequired = false;
		this->mExpectedType = ParamType::BOOL;
	}

	Parameter::Parameter(const std::string& name, const char* defaultValue, const std::string& description /*= "no description."*/)
		: mName(name), mDescription(description){
		std::string strValue(defaultValue);
		this->mDefaultValue.push_back(strValue);
		this->mValue.push_back(strValue);
		this->mRequired = false;
		this->mExpectedType = ParamType::STRING;
	}

	Parameter::Parameter(const std::string& name, const std::string& defaultValue, const std::string& description /*= "no description."*/)
		: mName(name), mDescription(description){
		this->mDefaultValue.push_back(defaultValue);
		this->mValue.push_back(defaultValue);
		this->mRequired = false;
		this->mExpectedType = ParamType::STRING;
	}

	Parameter::Parameter(const std::string& name, const FileHandle& defaultValue, const std::string& description /*= "no description."*/)
		: mName(name), mDescription(description){
		std::string convertString = defaultValue.absolutePath();
		this->mDefaultValue.push_back(convertString);
		this->mValue.push_back(convertString);
		this->mRequired = false;
		this->mExpectedType = ParamType::FILE_HANDLE;
	}

	Parameter::Parameter(const std::string& name, const DirectoryHandle& defaultValue, const std::string& description /*= "no description."*/)
		: mName(name), mDescription(description){
		std::string convertString = defaultValue.absolutePath();
		this->mDefaultValue.push_back(convertString);
		this->mValue.push_back(convertString);
		this->mRequired = false;
		this->mExpectedType = ParamType::DIRECTORY_HANDLE;
	}

	Parameter::Parameter(const std::string& name, const std::vector<int>& defaultValue, const std::string& description /*= "no description."*/)
		: mName(name), mDescription(description){
		for (auto value : defaultValue)
			this->mDefaultValue.push_back(std::to_string(value));
		this->mValue = mDefaultValue;
		this->mRequired = false;
		this->mExpectedType = ParamType::INT_VECTOR;
	}

	Parameter::Parameter(const std::string& name, const std::vector<double>& defaultValue, const std::string& description /*= "no description."*/)
		: mName(name), mDescription(description){
		for (auto value : defaultValue){
			std::string convertString = std::to_string(value);
			this->mDefaultValue.push_back(convertString);
		}
		this->mValue = mDefaultValue;
		this->mRequired = false;
		this->mExpectedType = ParamType::DOUBLE_VECTOR;
	}

	Parameter::Parameter(const std::string& name, const std::vector<std::string>& defaultValue, const std::string& description /*= "no description."*/)
		: mName(name), mDescription(description){
		this->mDefaultValue = defaultValue;
		this->mValue = defaultValue;
		this->mRequired = false;
		this->mExpectedType = ParamType::STRING_VECTOR;
	}

	Parameter::~Parameter(void){

	}

	Parameter::Parameter(const Parameter& rhs){
		this->mName = rhs.mName;
		this->mDescription = rhs.mDescription;
		this->mExpectedType = rhs.mExpectedType;
		this->mValue = rhs.mValue;
		this->mDefaultValue = rhs.mDefaultValue;
		this->mRequired = rhs.mRequired;
	}

	Parameter& Parameter::operator=(const Parameter& rhs){
		if (this != &rhs){
			this->mName = rhs.mName;
			this->mDescription = rhs.mDescription;
			this->mExpectedType = rhs.mExpectedType;
			this->mValue = rhs.mValue;
			this->mDefaultValue = rhs.mDefaultValue;
			this->mRequired = rhs.mRequired;
		}
		return *this;
	}

	bool Parameter::operator<(const Parameter& rhs) const{
		if (this->mName < rhs.mName)
			return true;
		else 
			return (this->mValue < rhs.mValue);
	}

	bool Parameter::operator==(const Parameter& rhs) const{
		return (this->mValue == rhs.mValue && this->mName == rhs.mName);
	}

	bool Parameter::operator!=(const Parameter& rhs) const{
		return (this->mName != rhs.mName);
	}

	int Parameter::toInt() const{		
		int convert_value;
		try{
			double temp_value;
			temp_value = boost::lexical_cast<double>(this->mValue[0]);
			convert_value = boost::numeric_cast<int>(temp_value);
		}
		catch (std::exception e){
			if (this->mValue[0] == "true")
				return 1;

			if (this->mValue[0] == "false")
				return 0;
			throw ParamException(this->mName, "Is not possible convert this parameter to int.");
		}
		return convert_value;
	}

	double Parameter::toDouble() const{
		double convert_value;
		try{
			convert_value = boost::lexical_cast<double>(this->mValue[0]);
		}
		catch (std::exception e){
			if (this->mValue[0] == "true")
				return 1;

			if (this->mValue[0] == "false")
				return 0;
			throw ParamException(this->mName, "Is not possible convert this parameter to double.");
		}
		return convert_value;
	}

	bool Parameter::toBool() const{
		int tempValue;
		try{
			tempValue = this->toInt();
		}
		catch (std::exception e){
			if (this->mValue[0] == "false")
				return false;
		}
		return (tempValue != 0);
	}

	std::string Parameter::toString() const{
		return this->mValue[0];
	}

	FileHandle Parameter::toFileHandle() const{
		return FileHandle(this->mValue[0]);
	}

	DirectoryHandle Parameter::toDirectoryHandle() const{
		return DirectoryHandle(this->mValue[0]);
	}

	std::vector<int> Parameter::toIntVector() const{
		std::vector<int> retVector;		
		int convert_value;
		for (auto strValue : this->mValue){
			try{
				double temp_value;
				temp_value = boost::lexical_cast<double>(strValue);
				convert_value = boost::numeric_cast<int>(temp_value);
			}
			catch (std::exception e){
				if (strValue == "true")
					convert_value = 1;
				else if (strValue == "false")
					convert_value = 0;
				else
					throw ParamException(this->mName, "Is not possible convert this parameter to int.");
			}
			retVector.push_back(convert_value);
		}
		return retVector;
	}

	std::vector<double> Parameter::toDoubleVector() const{
		std::vector<double> retVector;		
		for (auto strValue : this->mValue){
			double convert_value;
			try{
				convert_value = boost::lexical_cast<double>(strValue);
			}
			catch (std::exception e){
				if (strValue == "true")
					convert_value = 1;
				else if (strValue == "false")
					convert_value = 0;
				else
					throw ParamException(this->mName, "Is not possible convert this parameter to double.");
			}
			retVector.push_back(convert_value);
		}
		return retVector;
	}

	std::vector<std::string> Parameter::toStringVector() const{
		return this->mValue;
	}

	bool Parameter::isInt(){
		return Parameter::isInt(this->mValue[0]);
	}

	bool Parameter::isDouble(){
		return Parameter::isDouble(this->mValue[0]);
	}

	bool Parameter::isIntVector(){
		return Parameter::isIntVector(this->mValue);
	}

	bool Parameter::isDoubleVector(){
		return Parameter::isDoubleVector(this->mValue);
	}

	bool Parameter::isInt(const std::string& stringValue){
		try{
			boost::lexical_cast<int>(stringValue);
		}
		catch (std::exception e){
			if (stringValue == "true" || stringValue == "false")
				return true;
			return false;
		}
		return true;
	}

	bool Parameter::isDouble(const std::string& stringValue){
		try{
			boost::lexical_cast<double>(stringValue);
		}
		catch (std::exception e){
			if (stringValue == "true" || stringValue == "false")
				return true;
			return false;
		}
		return true;
	}

	bool Parameter::isIntVector(const std::vector<std::string> vectorStringValue){
		for (auto singleValue : vectorStringValue){
			if (!Parameter::isInt(singleValue))
				return false;
		}
		return true;
	}
	bool Parameter::isDoubleVector(const std::vector<std::string> vectorStringValue){
		for (auto singleValue : vectorStringValue){
			if (!Parameter::isDouble(singleValue))
				return false;
		}
		return true;
	}


	std::string Parameter::name() const{
		return this->mName;
	}

	void Parameter::restoreToDefaultValue(){
		this->mValue = this->mDefaultValue;
	}

	ssf::ParamType Parameter::expectedType() const{
		return this->mExpectedType;
	}

	void Parameter::setExpectedType(const ParamType& expectedType){
		this->mExpectedType = expectedType;
	}

	std::string Parameter::description() const{
		return this->mDescription;
	}

	void Parameter::setDescription(const std::string& description){
		this->mDescription = description;
	}

	bool Parameter::isRequired() const{
		return this->mRequired;
	}

	void Parameter::setRequired(const bool& required){
		this->mRequired = required;
	}

}