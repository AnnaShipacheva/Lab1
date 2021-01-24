#include "TritSet.h"
#include <cmath>
#include <utility>

inline void getMask()
{
	for (size_t i = 0; i < 8 * sizeof(uint); ++i)
	{
		if (i % 2 == 0)
			uMask |= 1u << i;
	}
}

TritSet::TritSet(unsigned long long amount)
{
	if (!uMask)
		getMask();
	vector<uint> a(ceil(2.0*amount / (8.0 * sizeof(uint))), uMask);

	arr = a;
	count=amount;
}

TritSet::TritSet(TritSet &&a)
{
	arr = move(a.arr);
	count = a.count;
}

unsigned long long TritSet::capacity(){return  ceil((count*2.0/8.0/sizeof(uint)));}

inline size_t getUintCap(){return 8 * sizeof(uint) / 2;}

void setBit(uint &a, uint shift, uint bValue)
{
	if (bValue)
		a |= 1u << shift;
	else
		a &= ~(1u << shift);

}
void TritSet::setValue(ull index, trit value)
{
	if (index < count)
	{
		ull indexV = index / (getUintCap());
		uint indexT = index % (getUintCap());
		uint intValue = value;
		setBit(arr[indexV], indexT * 2 + 1, intValue / 2);
		setBit(arr[indexV], (indexT * 2), intValue % 2);
	}
}

inline uint getBit(uint a, uint shift){return (a>>shift)&1u;}
trit TritSet::getValue(ull index)
{
	if (index >= count)
		return Unknown;
	ull indexV = index / (getUintCap());
	uint indexT = index % (getUintCap());
	uint Value = getBit(arr[indexV], indexT*2);
	Value |= getBit(arr[indexV], (indexT*2)+1) << 1;
	switch (Value)
	{
	case 0: return False;
	case 1: return Unknown;
	case 2: return True;
	default: return Unknown;
	}
}

ull TritSet::setSize(){return count;}

TritSet::trit_t TritSet::operator[] (ull ind)
{
	trit_t a(*this, ind);
	return a;
}

TritSet::trit_t& TritSet::trit_t::operator=(const trit& a)
{
	if (!uMask)
		getMask();
	if (a != Unknown && m_index >= m_set.count)
	{
		m_set.arr.resize(ceil((m_index + 1)*2.0 / (8.0 * sizeof(uint))));
		for (int i = m_set.capacity(); i < ceil((m_index + 1)*2.0 / (8.0 * sizeof(uint))); ++i)
			m_set.arr[i] = uMask;
		m_set.count = m_index + 1;
		m_set.setValue(m_index, a);
	} else if (m_index < m_set.count)
	{
		m_set.setValue(m_index, a);
	}
	return *this;
}

bool TritSet::trit_t::operator==(const trit& a)
{
	if (m_index >= m_set.count)
		return Unknown == a;
	else
		return m_set.getValue(m_index) == a;
}

bool TritSet::trit_t::operator==(const trit_t& t)
{
	if (m_index >= m_set.count)
		return false;
	return m_set.getValue(m_index) == t.m_set.getValue(m_index);
}

std::ostream& operator<<(std::ostream& out, TritSet::trit_t t)
{
	if (t.getIndex() >= t.getSet().count)
	{
		return out << Unknown;
	}
	return out << t.getSet().getValue(t.getIndex());
}

TritSet TritSet::operator&(TritSet& B)
{
	ull countMin = (*this).count < B.count ? (*this).count : B.count;
	ull countMax = (*this).count >= B.count ? (*this).count : B.count;
	trit t1, t2;
	ull i;
	TritSet C(countMax);
	for ( i = 0; i < countMin; ++i)
	{
		t1 = (*this).getValue(i);
		t2 = B.getValue(i);
		C.setValue(i, t1 & t2 );
	}
	for (; i < countMax; ++i) {
		t1 = B.getValue(i);
		t2 = Unknown;
		C.setValue(i, t1 & t2);
	}
	return move(C);
}

TritSet TritSet::operator|(TritSet& B)
{
	ull countMin = (*this).count < B.count ? (*this).count : B.count;
	ull countMax = (*this).count >= B.count ? (*this).count : B.count;
	trit t1, t2;
	ull i;
	TritSet C(countMax);
	for (i = 0; i < countMin; ++i)
	{
		t1 = (*this).getValue(i);
		t2 = B.getValue(i);
		C.setValue(i, t1 | t2);
	}
	for (; i < countMax; ++i) {
		t1 = B.getValue(i);
		t2 = Unknown;
		C.setValue(i, t1 | t2);
	}
	return move(C);
}

TritSet TritSet::operator!()
{
	trit t;
	ull i;
	TritSet C((*this).count);
	for (i = 0; i < C.count; ++i)
	{
		t = (*this).getValue(i);
		C.setValue(i, !t);
	}
	return move(C);
}

void TritSet::shrink()
{
	ull s = this->capacity();
	long long i;
	for (i = s - 1; i >= 0; --i) {
		if (arr[i] != uMask) {
			arr.resize(i + 1);
			break;
		}
	}
	if (i < 0)
	{
		arr.resize(0);
		count = 0;
	}
	else
	{
		uint b = arr[arr.size() - 1];
		for (i = getUintCap()-1; i >=0 ; --i) 
		{
			if (!(b&(1u << (i * 2))))
			{
				count = (arr.size() - 1)*getUintCap() + (i + 1);
				break;
			}
		}
		if (i < 0)
			count = (arr.size() - 1)*getUintCap();
	}
}

void TritSet::trim(ull lastIndex)
{
	if (lastIndex >= count)
		return;

	for (size_t i = 0; i < getUintCap() - (lastIndex%getUintCap()); ++i)
		setValue(lastIndex + i, Unknown);
	for (size_t i = (lastIndex / getUintCap() + 1); i < arr.size(); ++i)
		arr[i] = uMask;
}

size_t TritSet::length()
{
	for (int i=capacity()-1; i>=0;--i)
		if (arr[i] != uMask) {
			for (int j = getUintCap() - 1; j >= 0; --j) {
				if (getValue(i*getUintCap() + j) != Unknown) {
					return i * getUintCap() + j + 1;
				}
			} 
		}
	return 0;
}

size_t TritSet::cardinality(trit value)
{
	size_t len = length();
	size_t countValue = 0;
	for (size_t i=0; i<capacity();++i)
		for (size_t j = 0; j < getUintCap(); ++j) {
			if (i*getUintCap() + j >= len)
				return countValue;
			if (getValue(i*getUintCap() + j) == value)
				++countValue;
		}
	return countValue;
}

unordered_map<trit, size_t, hash<int>> TritSet::cardinality()
{
	unordered_map<trit, size_t, hash<int>> tritCounter;
	tritCounter.insert(make_pair<trit, size_t>(False, cardinality(False)));
	tritCounter.insert(make_pair<trit, size_t>(Unknown, cardinality(Unknown)));
	tritCounter.insert(make_pair<trit, size_t>(True, cardinality(True)));
	return move(tritCounter);
}