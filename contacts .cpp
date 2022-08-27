#include "contacts.h"
#include <fstream>
Contacts::Contacts(std::unordered_multimap<value_type, std::pair<phone_type, date_type>>::iterator start, std::unordered_multimap<value_type, std::pair<phone_type, date_type>>::iterator end)
{
	for (std::unordered_multimap<value_type, std::pair<phone_type, date_type>>::iterator iter = start; iter != end; ++iter) {
		data.insert(*iter);
	}
}

//Contacts::Contacts(std::initializer_list<std::unordered_multimap<value_type, std::pair<phone_type, date_type>, hash>> lst)
//{
//	//for (auto iter =lst.begin(); iter != lst.end(); ++iter) {
//	//	data.insert(*iter);
//	//}
//}

Contacts::Contacts(Contacts &obj)
{
	data = obj.data;
}
Contacts& Contacts::operator=(const Contacts &obj)
{
	data = obj.data;
	return *this;
}
bool Contacts::empty()
{
	return data.empty();
}
size_t Contacts::size()
{
	return data.size();
}
void Contacts::clear()
{
	data.clear();
}
void Contacts::swap(Contacts& book)
{
	Contacts abc = *this;
	(*this) = book;
	book = abc;
}
void Contacts::swap(Contacts& b1, Contacts& b2)
{
	Contacts abc = b1;
	b1 = b2;
	b2 = abc;
}
std::unordered_multimap<value_type, std::pair<phone_type, date_type>>::iterator Contacts::begin()
{
	return data.begin();
}
std::unordered_multimap<value_type, std::pair<phone_type, date_type>>::iterator Contacts::end()
{
	return data.end();
}

const std::unordered_multimap<value_type, std::pair<phone_type, date_type>>::iterator Contacts::cbegin() 
{
	return data.begin();
}

const std::unordered_multimap<value_type, std::pair<phone_type, date_type>>::iterator Contacts::cend()
{
	return data.end();
}

std::pair<phone_type, date_type>& Contacts::operator[](value_type key)
{
	for (auto i = data.begin(); i != data.end(); ++i) {
		if ((*i).first == key) {
			return (*i).second;
		}
	}
	data.emplace(key, std::make_pair("000","000"));
	for (auto i = data.begin(); i != data.end(); ++i) {
		if ((*i).first == key) {
			return (*i).second;
		}
	}
}

const std::pair<phone_type, date_type>& Contacts::at(value_type key) const
{
	for (auto i = data.begin(); i != data.end(); ++i) {
		if ((*i).first == key) {
			return (*i).second;
		}
	}
	std::cout << "Dont find obj with current key" << std::endl;
}

bool Contacts::fill_from_file(std::string name)
{
	std::ifstream file(name);
	if (file.is_open()) {
		while (!file.eof()) {
			std::string k1 = "", k2 = "", v1 = "", v2 = "";
			file >> k1; file >> k2; file >> v1; file >> v2;
			data.emplace(k1 + " " + k2, std::make_pair(v1, v2));
		}
		file.close();
		return 1;
	}
	else
		return 0;
}

std::pair<std::unordered_multimap<value_type, std::pair<phone_type, date_type>>::iterator, bool> Contacts::insert(value_type key, std::pair<phone_type, date_type> val)
{
	std::string num = val.first;
	bool f = 1;
	if ( num[0] == '8' && num[4] == ' ' && num[8] == ' '&& num.size() == 13) {
		for (size_t i = 0; i < 4; i++) {
			if (!(num[i] >= 48 && num[i] <= 57))
				f = 0;
		}
		for (size_t i = 5; i < 8; i++) {
			if (!(num[i] >= 48 && num[i] <= 57)) 
				f = 0;
		}
		for (size_t i = 9; i <= 12; i++) {
			if (!(num[i] >= 48 && num[i] <= 57)) 
				f = 0;
		}
		if (f) {
			num.erase(0,1);
			num.erase(3,1);
			num.erase(6,1);
			std::string s = "+7";
			num = s + num;
			val.first = num;
			//data.insert(std::make_pair(key,std::make_pair(num,val.second)));
			std::pair<std::unordered_multimap<value_type, std::pair <phone_type, date_type>>::iterator, bool> out;
			out.first = this->data.emplace(key, val);
			if ((*out.first).second == val) {
				out.second = 1;
				return out;
			}
			else {
				out.second = 0;
				return out;
			}
		}
	}
	if (num[2] == ' ' && num[0] == '+' && num[6] == ' ' && num[10] == ' ' && num[13] == ' '&& num.size() == 16) {
		for (size_t i = 0; i < 2; i++) {
			if (!(num[i] >= 48 && num[i] <= 57)) 
				f = 0;
		}
		for (size_t i = 3; i < 6; i++) {
			if (!(num[i] >= 48 && num[i] <= 57)) 
				f = 0;
		}
		for (size_t i = 7; i < 10; i++) {
			if (!(num[i] >= 48 && num[i] <= 57))
				f = 0;
		}
		for (size_t i = 11; i < 13; i++) {
			if (!(num[i] >= 48 && num[i] <= 57)) 
				f= 0;
		}
		for (size_t i = 14; i < 16; i++) {
			if (!(num[i] >= 48 && num[i] <= 57))
				f = 0;
		}
		if (f) {
			num.erase(2,1);num.erase(5,1);num.erase(8,1);num.erase(10,1);
			val.first = num;
			std::pair<std::unordered_multimap<value_type, std::pair <phone_type, date_type>>::iterator, bool> out;
			out.first = this->data.emplace(key, val);
			if ((*out.first).second == val) {
				out.second = 1;
				return out;
			}
			else {
				out.second = 0;
				return out;
			}
		}
	}
	if (num.size() == 12 && num[1] == ' ') {
		for (size_t i = 0; i < 1; i++) {
			if (!(num[i] >= 48 && num[i] <= 57)) 
				f = 0;
		}
		for (size_t i = 2; i < 12; i++) {
			if (!(num[i] >= 48 && num[i] <= 57)) 
				f = 0;
		}
		if (f) {
			num.erase(1,1);
			phone_type s = "+";
			val.first = s + num;
			std::pair<std::unordered_multimap<value_type, std::pair <phone_type, date_type>>::iterator, bool> out;
			out.first = this->data.emplace(key, val);
			if ((*out.first).second == val) {
				out.second = 1;
				return out;
			}
			else {
				out.second = 0;
				return out;
			}
		}
	}
	if (num.size() == 12 && num[3] == ' ' && num[7] == ' ') {
		for (size_t i = 0; i < 3; i++) {
			if (!(num[i] >= 48 && num[i] <= 57)) 
				f= 0;
		}
		for (size_t i = 4; i < 7; i++) {
			if (!(num[i] >= 48 &&num[i] <= 57)) 
				f = 0;
		}
		for (size_t i = 8; i < 12; i++) {
			if (!(num[i] >= 48 && num[i] <= 57)) 
				f = 0;
		}
		if (f) {
			num.erase(3);num.erase(7);
			phone_type s = "+7";
			val.first = s + num;
			std::pair<std::unordered_multimap<value_type, std::pair <phone_type, date_type>>::iterator, bool> out;
			out.first = this->data.emplace(key, val);
			if ((*out.first).second == val) {
				out.second = 1;
				return out;
			}
			else {
				out.second = 0;
				return out;
			}
		}
	}
	if (f) {
		std::pair<std::unordered_multimap<value_type, std::pair <phone_type, date_type>>::iterator, bool> out;
		out.first = this->data.emplace(key, val);
		if ((*out.first).second == val) {
			out.second = 1;
			return out;
		}
		else {
			out.second = 0;
			return out;
		}
	
	}
	else
		std::cout << "error enter info";
}

std::pair<std::unordered_multimap<value_type, std::pair<phone_type, date_type>>::iterator, bool> Contacts::insert_or_assign(value_type key, std::pair<phone_type, date_type> val)
{
	std::string num = val.first;
	bool f = 1;
	if (num[0] == '8' && num[4] == ' ' && num[8] == ' ' && num.size() == 13) {
		for (size_t i = 0; i < 4; i++) {
			if (!(num[i] >= 48 && num[i] <= 57))
				f = 0;
		}
		for (size_t i = 5; i < 8; i++) {
			if (!(num[i] >= 48 && num[i] <= 57))
				f = 0;
		}
		for (size_t i = 9; i <= 12; i++) {
			if (!(num[i] >= 48 && num[i] <= 57))
				f = 0;
		}
		if (f) {
			num.erase(0,1); num.erase(3,1); num.erase(6,1);
			std::string s = "+7";
			num = s + num;
			val.first = num;
			//data.insert(std::make_pair(key,std::make_pair(num,val.second)));
			std::pair<std::unordered_multimap<value_type, std::pair <phone_type, date_type>>::iterator, bool> out;
			out.first = this->data.emplace(key, val);
			if ((*out.first).second == val) {
				out.second = 1;
				return out;
			}
			else {
				(*out.first).second = val;
				out.second = 0;
				return out;
			}
		}
	}
	if (num[2] == ' ' && num[0] == '+' && num[6] == ' ' && num[10] == ' ' && num[13] == ' ' && num.size() == 16) {
		for (size_t i = 0; i < 2; i++) {
			if (!(num[i] >= 48 && num[i] <= 57))
				f = 0;
		}
		for (size_t i = 3; i < 6; i++) {
			if (!(num[i] >= 48 && num[i] <= 57))
				f = 0;
		}
		for (size_t i = 7; i < 10; i++) {
			if (!(num[i] >= 48 && num[i] <= 57))
				f = 0;
		}
		for (size_t i = 11; i < 13; i++) {
			if (!(num[i] >= 48 && num[i] <= 57))
				f = 0;
		}
		for (size_t i = 14; i < 16; i++) {
			if (!(num[i] >= 48 && num[i] <= 57))
				f = 0;
		}
		if (f) {
			num.erase(2,1); num.erase(5,1); num.erase(8,1); num.erase(10,1);
			val.first = num;
			std::pair<std::unordered_multimap<value_type, std::pair <phone_type, date_type>>::iterator, bool> out;
			out.first = this->data.emplace(key, val);
			if ((*out.first).second == val) {
				out.second = 1;
				return out;
			}
			else {
				(*out.first).second = val;
				out.second = 0;
				return out;
			}
		}
	}
	if (num.size() == 12 && num[1] == ' ') {
		for (size_t i = 0; i < 1; i++) {
			if (!(num[i] >= 48 && num[i] <= 57))
				f = 0;
		}
		for (size_t i = 2; i < 12; i++) {
			if (!(num[i] >= 48 && num[i] <= 57))
				f = 0;
		}
		if (f) {
			num.erase(1,1);
			phone_type s = "+";
			val.first = s + num;
			std::pair<std::unordered_multimap<value_type, std::pair <phone_type, date_type>>::iterator, bool> out;
			out.first = this->data.emplace(key, val);
			if ((*out.first).second == val) {
				out.second = 1;
				return out;
			}
			else {
				(*out.first).second = val;
				out.second = 0;
				return out;
			}
		}
	}
	if (num.size() == 12 && num[3] == ' ' && num[7] == ' ') {
		for (size_t i = 0; i < 3; i++) {
			if (!(num[i] >= 48 && num[i] <= 57))
				f = 0;
		}
		for (size_t i = 4; i < 7; i++) {
			if (!(num[i] >= 48 && num[i] <= 57))
				f = 0;
		}
		for (size_t i = 8; i < 12; i++) {
			if (!(num[i] >= 48 && num[i] <= 57))
				f = 0;
		}
		if (f) {
			num.erase(3,1); num.erase(7,1);
			phone_type s = "+7";
			val.first = s + num;
			std::pair<std::unordered_multimap<value_type, std::pair <phone_type, date_type>>::iterator, bool> out;
			out.first = this->data.emplace(key, val);
			if ((*out.first).second == val) {
				out.second = 1;
				return out;
			}
			else {
				(*out.first).second = val;
				out.second = 0;
				return out;
			}
		}
	}
	if (f) {
		std::pair<std::unordered_multimap<value_type, std::pair <phone_type, date_type>>::iterator, bool> out;
		out.first = this->data.emplace(key, val);
		if ((*out.first).second == val) {
			out.second = 1;
			return out;
		}
		else {
			(*out.first).second = val;
			out.second = 0;
			return out;
		}

	}
	else
		std::cout << "error enter info";
}

void connects(std::unordered_multimap<value_type, std::pair <phone_type, date_type>, hash>& lhs, const std::unordered_multimap<value_type, std::pair <phone_type, date_type>>& rhs) {
	std::unordered_multimap<value_type, std::pair <phone_type, date_type>, hash>::iterator lhsItr = lhs.begin();
	std::unordered_multimap<value_type, std::pair <phone_type, date_type>>::const_iterator rhsItr = rhs.begin();

	while (lhsItr != lhs.end() && rhsItr != rhs.end()) {
		if (rhsItr->first < lhsItr->first) {
			lhs.insert(lhsItr, *rhsItr);
			++rhsItr;
		}
		else if (rhsItr->first == lhsItr->first) {
			lhsItr->second = rhsItr->second;
			++lhsItr; ++rhsItr;
		}
		else
			++lhsItr;

	}
	lhs.insert(rhsItr, rhs.end());
}
void connects(std::unordered_multimap<value_type, std::pair <phone_type, date_type>, hash>& lhs, const std::unordered_multimap<value_type, std::pair <phone_type, date_type>,hash>& rhs) {
	std::unordered_multimap<value_type, std::pair <phone_type, date_type>, hash>::iterator lhsItr = lhs.begin();
	std::unordered_multimap<value_type, std::pair <phone_type, date_type>,hash>::const_iterator rhsItr = rhs.begin();

	while (lhsItr != lhs.end() && rhsItr != rhs.end()) {
		if (rhsItr->first < lhsItr->first) {
			lhs.insert(lhsItr, *rhsItr);
			++rhsItr;
		}
		else if (rhsItr->first == lhsItr->first) {
			lhsItr->second = rhsItr->second;
			++lhsItr; ++rhsItr;
		}
		else
			++lhsItr;

	}
	lhs.insert(rhsItr, rhs.end());
}
Contacts::Contacts(std::initializer_list<std::unordered_multimap<value_type, std::pair<phone_type, date_type>,hash>> lst)
{
	for (auto i = lst.begin(); i != lst.end(); i++) {
		connects(data, *i);
	}
}

std::unordered_multimap<value_type, std::pair<phone_type, date_type>>::iterator Contacts::find(value_type key)
{
	return data.find(key);
}

std::pair<std::unordered_multimap<value_type, std::pair<phone_type, date_type>>::iterator, std::unordered_multimap<value_type, std::pair<phone_type, date_type>>::iterator> Contacts::range(value_type key)
{
	return data.equal_range(key);
}

bool Contacts::erase(value_type key)
{
	return data.erase(key);
}

void Contacts::delete_duplicates()
{
	std::unordered_multimap<value_type, std::pair <phone_type, date_type>, hash> data1;
	while (data.size() > 0)
	{
		auto element = *(data.begin());
		data1.insert(make_pair(element.first, element.second));
		data.erase(element.first);
	}
	data = data1;
	
}
