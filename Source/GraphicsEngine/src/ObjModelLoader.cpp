// *************************************************************************
//  ObjModelLoader   version:  1.0   Ankur Sheel  date: 2012/10/29
//  ------------------------------------------------------------------------
//  
//  ------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *************************************************************************
// 
// *************************************************************************

#include "stdafx.h"
#include "ObjModelLoader.h"
#include "FileInput.hxx"
#include "Optional.h"
#include "Model.hxx"

using namespace Graphics;
using namespace Base;
using namespace Utilities;
using namespace std;

// *************************************************************************
cObjModelLoader::cObjModelLoader()
{

}

// *************************************************************************
cObjModelLoader::~cObjModelLoader()
{
	m_MaterialsMap.clear();
}

// *************************************************************************
void cObjModelLoader::VLoadModelFromFile(const cString & strModelFile, IModel * pModel)
{
	shared_ptr<IFileInput> pObjFile = shared_ptr<IFileInput>(IFileInput::CreateInputFile());
	
	if(pObjFile->Open(strModelFile, std::ios_base::in))
	{
		cString strLine;
		vector<cString> vtokens;
		vector<cVector3> vVertexPositions;
		int iCurrentSubset = -1;
		int iStartIndexNo = 0;
		do
		{
			strLine = pObjFile->ReadLine();
			if(!strLine.IsEmpty())
			{
				if (strLine[0] == '#')
				{
					continue;
				}
				strLine.TrimBoth();
				if(!strLine.IsEmpty())
				{
					vtokens.clear();
					strLine.Tokenize(' ', vtokens);
					// vertices
					if (vtokens[0] == "v")
					{
						float x = GetFloatValue(vtokens[1]);
						float y = GetFloatValue(vtokens[2]);
						float z = GetFloatValue(vtokens[3]);
						
						// invert z coordinate vertice
						//z = z * -1.0f;

						vVertexPositions.push_back(cVector3(x,y,z));
					}
					// faces/triangles
					else if (vtokens[0] == "f")
					{
						m_vSubset[iCurrentSubset].vIndices.push_back(GetIntValue(vtokens[1]) - 1);
						m_vSubset[iCurrentSubset].vIndices.push_back(GetIntValue(vtokens[2]) - 1);
						m_vSubset[iCurrentSubset].vIndices.push_back(GetIntValue(vtokens[3]) - 1);
						iStartIndexNo += 3;
					}
					else if (vtokens[0] == "mtllib")
					{
						LoadMaterialFile("resources\\" +vtokens[1]);
					}
					else if (vtokens[0] == "usemtl")
					{
						MaterialMap::const_iterator curr = m_MaterialsMap.find(vtokens[1]);
						if (curr != m_MaterialsMap.end())
						{
							iCurrentSubset++;
							stSubsetData subset;
							subset.diffuseColor = curr->second.Diffuse;
							subset.iStartIndexNo = iStartIndexNo;
							m_vSubset.push_back(subset);
						}
					}
				}
			}
		}
		while(!pObjFile->IsEOF() || !strLine.IsEmpty());
		pObjFile->Close();

		stModelDef def;

		stTexVertex * pVertices = DEBUG_NEW stTexVertex[vVertexPositions.size()];
		for (int i=0; i<vVertexPositions.size(); i++)
		{
			pVertices[i].m_fX = vVertexPositions[i].m_dX;
			pVertices[i].m_fY = vVertexPositions[i].m_dY;
			pVertices[i].m_fZ = vVertexPositions[i].m_dZ;
		} 

		def.pVertices = pVertices;
		def.iNumberOfVertices = vVertexPositions.size();

		for (int i=0;i<m_vSubset.size();i++)
		{
			int size = m_vSubset[i].vIndices.size();
			unsigned long * pIndices = DEBUG_NEW unsigned long[size];
			for (int j=0; j<size; j++)
			{
				pIndices[j] = m_vSubset[i].vIndices[j];
			}
			stModelDef::stSubsetDef subsetDef;
			subsetDef.pIndices = pIndices;
			subsetDef.iNumberOfIndices = size;
			subsetDef.diffuseColor = m_vSubset[i].diffuseColor;
			def.vSubsetsDef.push_back(subsetDef);
		}
		pModel->VOnInitialization(def);

		SAFE_DELETE_ARRAY(pVertices);
		for (int i=0;i<m_vSubset.size();i++)
		{
			SAFE_DELETE_ARRAY(def.vSubsetsDef[i].pIndices);
		}
		
		m_MaterialsMap.clear();
	}
}

// *************************************************************************
void cObjModelLoader::LoadMaterialFile(const Base::cString & strMaterialFile)
{
	shared_ptr<IFileInput> pMtlFile = shared_ptr<IFileInput>(IFileInput::CreateInputFile());

	if(pMtlFile->Open(strMaterialFile, std::ios_base::in))
	{
		cString strLine;
		vector<cString> vtokens;
		cString strCurrentMaterialName;

		do
		{
			strLine = pMtlFile->ReadLine();
			if(!strLine.IsEmpty())
			{
				if (strLine[0] == '#')
				{
					continue;
				}
				strLine.TrimBoth();
				if(!strLine.IsEmpty())
				{
					vtokens.clear();
					strLine.Tokenize(' ', vtokens);
					// vertices
					if (vtokens[0] == "newmtl")
					{
						stMaterial material;
						strCurrentMaterialName = vtokens[1];
						material.strMatName = strCurrentMaterialName;
						m_MaterialsMap.insert(std::make_pair(strCurrentMaterialName, material));
					}
					else if (vtokens[0] == "Kd")
					{
						MaterialMap::iterator curr = m_MaterialsMap.find(strCurrentMaterialName);
						if (curr != m_MaterialsMap.end())
						{
							float r = GetFloatValue(vtokens[1]);
							float g = GetFloatValue(vtokens[2]);
							float b = GetFloatValue(vtokens[3]);
							(curr->second).Diffuse = cColor(r, g, b, 1.0f);

						}
						
					}
				}
			}
		}
		while(!pMtlFile->IsEOF() || !strLine.IsEmpty());
		pMtlFile->Close();
	}
}

// *************************************************************************
float cObjModelLoader::GetFloatValue(const cString & strVal)
{
	tOptional<float> val = strVal.ToFloat();
	if (val.IsValid())
	{
		return *val;
	}
	return 0;
}

// *************************************************************************
int cObjModelLoader::GetIntValue(const Base::cString & strVal)
{
	tOptional<int> val = strVal.ToInt();
	if (val.IsValid())
	{
		return *val;
	}
	return 0;

}
// *************************************************************************
IObjModelLoader * IObjModelLoader::GetObjModelLoader()
{
	return DEBUG_NEW cObjModelLoader();
}
