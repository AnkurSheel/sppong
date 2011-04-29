// ***************************************************************
//  Random   version:  1.0   Ankur Sheel  date: 2011/04/16
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// adapted from Game Coding Complete 
// ***************************************************************
#ifndef RandomGenerator_hxx__
#define RandomGenerator_hxx__

namespace Utilities
{
	class IRandomGenerator
	{
	public:
		UTILITIES_API virtual ~IRandomGenerator() {}
		UTILITIES_API virtual unsigned int Random(unsigned int nMax) = 0;
		UTILITIES_API virtual float Random() = 0;
		UTILITIES_API virtual void SetRandomSeed(unsigned int nSeed) = 0 ;
		UTILITIES_API virtual unsigned int GetRandomSeed() = 0;
		UTILITIES_API virtual void Randomize() = 0;
		UTILITIES_API static IRandomGenerator * CreateRandomGenerator();
	};
}
#endif // RandomGenerator_hxx__
