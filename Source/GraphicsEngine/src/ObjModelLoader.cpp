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
		vector<int> vIndices;
		Base::cColor diffuseColor;

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
						vIndices.push_back(GetIntValue(vtokens[1]) - 1);
						vIndices.push_back(GetIntValue(vtokens[2]) - 1);
						vIndices.push_back(GetIntValue(vtokens[3]) - 1);
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
							stMaterial material = curr->second;
							diffuseColor = material.Diffuse;
						}
					}
				}
			}
		}
		while(!pObjFile->IsEOF() || !strLine.IsEmpty());
		pObjFile->Close();

		stTexVertex * pVertices = DEBUG_NEW stTexVertex[vVertexPositions.size()];
		for (int i=0; i<vVertexPositions.size(); i++)
		{
			pVertices[i].m_fX = vVertexPositions[i].m_dX;
			pVertices[i].m_fY = vVertexPositions[i].m_dY;
			pVertices[i].m_fZ = vVertexPositions[i].m_dZ;
		}

		unsigned long * pIndices = DEBUG_NEW unsigned long[vIndices.size()];
		for (int i=0;i<vIndices.size();i++)
		{
			pIndices[i] = vIndices[i];
		}

		stModelDef def;
		def.pVertices = pVertices;
		def.pIndices = pIndices;
		def.iNumberOfVertices = vVertexPositions.size();
		def.iNumberOfIndices = vIndices.size();
		def.diffuseColor = diffuseColor;

		pModel->VOnInitialization(def);

		SAFE_DELETE_ARRAY(pVertices);
		SAFE_DELETE_ARRAY(pIndices);
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
							float b = GetFloatValue(vtokens[2]);
							float g = GetFloatValue(vtokens[3]);
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
