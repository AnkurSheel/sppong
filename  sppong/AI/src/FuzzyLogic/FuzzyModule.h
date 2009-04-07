// ***************************************************************
//  FuzzyModule   version:  1.0   Ankur Sheel  date: 04/05/2009
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2009 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef FUZZYMODULE_H
#define FUZZYMODULE_H

class cFuzzyTerm;
class cFuzzyVariable;
class cFuzzyRule;

#include <map>
#include <vector>

class cFuzzyModule
{
protected:
	struct compstr
	{
		bool operator () (const char * const str1, const char * const str2) const
		{
			return strcmp(str1, str2) < 0;	
		}
	};

	typedef std::map<const char * const, cFuzzyVariable*, compstr> VarMap;

public:
	enum DeFuzzifyMethod
	{
		Max_average
		,Centroid
	};
public:
	cFuzzyModule();
	virtual ~cFuzzyModule();
	cFuzzyVariable* CreateFLV(const char * const& varName);
	void AddRule(cFuzzyTerm* antecedent, cFuzzyTerm* consequent);
	float DeFuzzify(const char * const& key, const DeFuzzifyMethod method);
	void Fuzzify(const char * const& nameOfFLV, const float val);

protected:
	void SetConfidencesofConsequentsToZero();

protected:
	int m_iNumSamples;
	VarMap m_Variables;
	std::vector<cFuzzyRule* > m_Rules;
};
#endif
