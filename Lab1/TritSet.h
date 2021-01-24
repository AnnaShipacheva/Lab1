#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include "Trit.h"

using namespace std;
typedef unsigned int uint;
typedef unsigned long long ull;
static uint uMask = 0;
inline void getMask();



class TritSet {
private:
	vector<uint> arr;
	unsigned long long count;
	void setValue(ull index, trit value);
	trit getValue(ull index);
public:
	TritSet(unsigned long long amount);
	TritSet(TritSet &&a);
	~TritSet() = default;
	unsigned long long capacity();
	void shrink();
	void trim(ull lastIndex);
	size_t length();
	size_t cardinality(trit value);
	unordered_map<trit, size_t, hash<int>> cardinality();
	
	ull setSize();
	
	class trit_t {
	private:
		TritSet& m_set;
		ull m_index;
	public:
		trit_t(TritSet &s, ull n) : m_set(s), m_index(n) {}
		~trit_t() = default;

		TritSet& getSet() { return m_set; }
		ull getIndex() { return m_index; }


		trit_t& operator=(const trit& a);
		bool operator==(const trit& a);
		bool operator==(const trit_t& t);
	
	};
	friend ostream& operator<<(ostream& out, trit_t t);
	trit_t operator[](ull ind);
	TritSet operator& (TritSet& B);
	TritSet operator| (TritSet& B);
	TritSet operator!();
};
