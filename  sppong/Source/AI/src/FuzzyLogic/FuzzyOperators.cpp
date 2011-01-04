// ***************************************************************
//  FuzzyOperators   version:  1.0   Ankur Sheel  date: 04/05/2009
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2009 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#include "stdafx.h"
#include "FuzzyOperators.h"
#include "AIDefines.h"
#include "FuzzySetProxy.h"
#include "FuzzySet.h"
#include <math.h>

//----------------------------------------------------------------------------
// Construction and Destruction
//----------------------------------------------------------------------------
cFuzzyOperatorVery::~cFuzzyOperatorVery()
{
}
//----------------------------------------------------------------------------

cFuzzyOperatorVery::cFuzzyOperatorVery(const cFuzzyOperatorVery& instance)
: m_Set(instance.m_Set)
{
}
//----------------------------------------------------------------------------

cFuzzyOperatorVery::cFuzzyOperatorVery(cFuzzySetProxy& set)
: m_Set(set.m_Set)
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Clone
//----------------------------------------------------------------------------
cFuzzyTerm* cFuzzyOperatorVery::Clone()
{
	return(new cFuzzyOperatorVery(*this));
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Returns the DOM of the term
//----------------------------------------------------------------------------
float cFuzzyOperatorVery::GetDOM()
{
	float temp = m_Set->GetDOM();
	return (temp * temp);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// clears the dom
//----------------------------------------------------------------------------
void cFuzzyOperatorVery::ClearDOM()
{
	m_Set->ClearDOM();
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// or's with dom
//----------------------------------------------------------------------------
void cFuzzyOperatorVery::ORwithDOM(const float val)
{
	m_Set->ORwithDOM(val * val);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Construction and Destruction
//----------------------------------------------------------------------------
cFuzzyOperatorFairly::~cFuzzyOperatorFairly()
{
}
//----------------------------------------------------------------------------

cFuzzyOperatorFairly::cFuzzyOperatorFairly(const cFuzzyOperatorFairly& instance)
: m_Set(instance.m_Set)
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Construction and Destruction
//----------------------------------------------------------------------------
cFuzzyOperatorFairly::cFuzzyOperatorFairly(cFuzzySetProxy& set)
: m_Set(set.m_Set)
{
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Clone
//----------------------------------------------------------------------------
cFuzzyTerm * cFuzzyOperatorFairly::Clone()
{
	return(new cFuzzyOperatorFairly(*this));
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Returns the DOM of the term
//----------------------------------------------------------------------------
float cFuzzyOperatorFairly::GetDOM()
{
	return (sqrt(m_Set->GetDOM()));
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// clears the dom
//----------------------------------------------------------------------------
void cFuzzyOperatorFairly::ClearDOM()
{
	m_Set->ClearDOM();
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// or's with dom
//----------------------------------------------------------------------------
void cFuzzyOperatorFairly::ORwithDOM(const float val)
{
	m_Set->ORwithDOM(sqrt(val));
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Construction and Destruction
//----------------------------------------------------------------------------
cFuzzyOperatorAnd::cFuzzyOperatorAnd()
{
}

cFuzzyOperatorAnd::~cFuzzyOperatorAnd()
{
	std::vector<cFuzzyTerm*>::iterator curTerm;
	for(curTerm = m_Terms.begin(); curTerm != m_Terms.end(); curTerm++)
	{
		SAFE_DELETE(*curTerm);
	}
}
//----------------------------------------------------------------------------

cFuzzyOperatorAnd::cFuzzyOperatorAnd(const cFuzzyOperatorAnd& instance)
{
	std::vector<cFuzzyTerm*>::const_iterator curTerm;
	for(curTerm = instance.m_Terms.begin(); curTerm != instance.m_Terms.end(); 
																	curTerm++)
	{
		m_Terms.push_back((*curTerm)->Clone());
	}
}
//----------------------------------------------------------------------------

cFuzzyOperatorAnd::cFuzzyOperatorAnd(cFuzzyTerm& op1, cFuzzyTerm& op2)
{
   m_Terms.push_back(op1.Clone());
   m_Terms.push_back(op2.Clone());
}
//----------------------------------------------------------------------------

cFuzzyOperatorAnd::cFuzzyOperatorAnd(cFuzzyTerm& op1, cFuzzyTerm& op2, 
																cFuzzyTerm& op3)
{
	m_Terms.push_back(op1.Clone());
	m_Terms.push_back(op2.Clone());
	m_Terms.push_back(op3.Clone());
}
//----------------------------------------------------------------------------

cFuzzyOperatorAnd::cFuzzyOperatorAnd(cFuzzyTerm& op1, cFuzzyTerm& op2, 
												cFuzzyTerm& op3, cFuzzyTerm& op4)
{
	m_Terms.push_back(op1.Clone());
	m_Terms.push_back(op2.Clone());
	m_Terms.push_back(op3.Clone());
	m_Terms.push_back(op4.Clone());
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// clone
//----------------------------------------------------------------------------
cFuzzyTerm* cFuzzyOperatorAnd::Clone()
{
	return(new cFuzzyOperatorAnd(*this)) ;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// returns the dom
//----------------------------------------------------------------------------
float cFuzzyOperatorAnd::GetDOM()
{
	float smallest = 1000000.0f;
	float temp ;

	std::vector<cFuzzyTerm*>::iterator curTerm;
	for(curTerm = m_Terms.begin(); curTerm != m_Terms.end(); curTerm++)
	{
		temp = (*curTerm)->GetDOM();
		if(temp < smallest)
		{
			smallest = temp ;
		}
	}
	return smallest;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Clears the dom
//----------------------------------------------------------------------------
void cFuzzyOperatorAnd::ClearDOM()
{
	std::vector<cFuzzyTerm*>::iterator curTerm;
	for(curTerm = m_Terms.begin(); curTerm != m_Terms.end(); curTerm++)
	{
		(*curTerm)->ClearDOM();
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// or's with dom
//----------------------------------------------------------------------------
void cFuzzyOperatorAnd::ORwithDOM(const float val)
{
	std::vector<cFuzzyTerm*>::iterator curTerm;
	for(curTerm = m_Terms.begin(); curTerm != m_Terms.end(); curTerm++)
	{
		(*curTerm)->ORwithDOM(val);
	}
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Construction and Destruction
cFuzzyOperatorOr::~cFuzzyOperatorOr()
{
	std::vector<cFuzzyTerm*>::iterator curTerm;
	for(curTerm = m_Terms.begin(); curTerm != m_Terms.end(); curTerm++)
	{
		SAFE_DELETE(*curTerm);
	}
}
//----------------------------------------------------------------------------

cFuzzyOperatorOr::cFuzzyOperatorOr(const cFuzzyOperatorOr& instance)
{
	 std::vector<cFuzzyTerm*>::const_iterator curTerm;
   for (curTerm = instance.m_Terms.begin(); curTerm != instance.m_Terms.end();
																	++curTerm)
   {
     m_Terms.push_back((*curTerm)->Clone());
   }
}
//----------------------------------------------------------------------------

cFuzzyOperatorOr::cFuzzyOperatorOr(cFuzzyTerm& op1, cFuzzyTerm& op2)
{
	m_Terms.push_back(op1.Clone());
	m_Terms.push_back(op2.Clone());
}
//----------------------------------------------------------------------------

cFuzzyOperatorOr::cFuzzyOperatorOr(cFuzzyTerm& op1, cFuzzyTerm& op2, cFuzzyTerm& op3)
{
	m_Terms.push_back(op1.Clone());
	m_Terms.push_back(op2.Clone());
	m_Terms.push_back(op3.Clone());
}
//----------------------------------------------------------------------------

cFuzzyOperatorOr::cFuzzyOperatorOr(cFuzzyTerm& op1, cFuzzyTerm& op2, cFuzzyTerm& op3,
																cFuzzyTerm& op4)
{
	m_Terms.push_back(op1.Clone());
	m_Terms.push_back(op2.Clone());
	m_Terms.push_back(op3.Clone());
	m_Terms.push_back(op4.Clone());
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Clone
//----------------------------------------------------------------------------
cFuzzyTerm* cFuzzyOperatorOr::Clone()
{
	return (new cFuzzyOperatorOr(*this));
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// returns the dom
//----------------------------------------------------------------------------
float cFuzzyOperatorOr::GetDOM()
{
	float largest = -1.0f;
	float temp ;

	std::vector<cFuzzyTerm*>::iterator curTerm;
	for(curTerm = m_Terms.begin(); curTerm != m_Terms.end(); curTerm++)
	{
		temp = (*curTerm)->GetDOM();
		if(temp > largest)
		{
			largest = temp ;
		}
	}
	return largest;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// clears the dom
//----------------------------------------------------------------------------
void cFuzzyOperatorOr::ClearDOM()
{
	_ASSERT(0);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Or's with dom
//----------------------------------------------------------------------------
void cFuzzyOperatorOr::ORwithDOM(const float val)
{
	_ASSERT(0);
}
//----------------------------------------------------------------------------