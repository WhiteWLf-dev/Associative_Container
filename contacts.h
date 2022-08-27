#pragma once
#include <iostream>
#include<unordered_map>
struct hash {
	size_t operator() (std::string word) const {
		const size_t p = 31, m = 1e9 + 7;
		size_t hash = 0;
		size_t p_pow = 1;
		const size_t n = word.length();
		for (int i = 0; i < n; ++i) {
			hash = (hash + (word[i] - 'a' + 1) * p_pow) % m;
			p_pow = (p_pow * p) % m;
		}
		return hash;
	}
};
using value_type = std::string;
using phone_type = std::string;
using date_type = std::string;
class Contacts {
private:
	std::unordered_multimap<value_type, std::pair <phone_type, date_type>, hash> data;
public:
	Contacts() = default;
	Contacts(std::unordered_multimap<value_type, std::pair <phone_type, date_type>>::iterator start, std::unordered_multimap <value_type, std::pair <phone_type, date_type>>::iterator end);
	Contacts(std::initializer_list <std::unordered_multimap < value_type, std::pair<phone_type, date_type>,hash>> lst);
	Contacts(Contacts &obj);

	Contacts& operator=(const Contacts &obj);
	
	bool empty();
	size_t size();
	void clear();
	void swap(Contacts &book);
	static void swap(Contacts &b1, Contacts &b2);
	std::unordered_multimap<value_type, std::pair <phone_type, date_type>>::iterator begin();
	std::unordered_multimap<value_type, std::pair <phone_type, date_type>>::iterator end();
	const std::unordered_multimap<value_type, std::pair <phone_type, date_type>>::iterator cbegin();
	const std::unordered_multimap<value_type, std::pair <phone_type, date_type>>::iterator cend();
	std::pair <phone_type, date_type>& operator[] (value_type key);
	const std::pair <phone_type, date_type>& at(value_type key) const;
	bool fill_from_file(std::string name);
	std::pair<std::unordered_multimap<value_type, std::pair <phone_type, date_type>>::iterator, bool> insert(value_type key, std::pair<phone_type, date_type> val);
	std::pair<std::unordered_multimap<value_type, std::pair <phone_type, date_type>>::iterator, bool> insert_or_assign(value_type key, std::pair<phone_type, date_type> val);
	std::unordered_multimap<value_type, std::pair <phone_type, date_type>>::iterator find(value_type key);
	std::pair<std::unordered_multimap<value_type, std::pair <phone_type, date_type>>::iterator, std::unordered_multimap<value_type, std::pair <phone_type, date_type>>::iterator> range(value_type key);
	bool erase(value_type key);
	void delete_duplicates();
};