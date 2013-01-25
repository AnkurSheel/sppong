// *****************************************************************************
//  ObjModelLoader   version:  1.0   Ankur Sheel  date: 2012/10/29
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************

#include "stdafx.h"
#include "ObjModelLoader.h"
#include "FileInput.hxx"
#include "Optional.h"
#include "Model.hxx"
#include "vertexstruct.h"
#include "GameDirectories.h"
#include "ResCache.hxx"
#include "ResourceManager.hxx"

using namespace Graphics;
using namespace Base;
using namespace Utilities;
using namespace std;

IObjModelLoader * cObjModelLoader::s_pModelLoader = NULL;

// *****************************************************************************
cObjModelLoader::cObjModelLoader()
{

}

// *****************************************************************************
cObjModelLoader::~cObjModelLoader()
{
}

// *****************************************************************************
void cObjModelLoader::VLoadModelFromFile(const cString & strModelFile, IModel * pModel)
{
	shared_ptr<IFileInput> pObjFile = shared_ptr<IFileInput>(IFileInput::CreateInputFile());
	
	//cString strModelPath = cGameDirectories::GameDirectories().strModelDirectory + strModelFile;
	//IResource * pResource = IResource::CreateResource(strModelPath);
	//shared_ptr<IResHandle> modelHandle = IResourceManager::GetInstance()->VGetResourceCache()->GetHandle(*pResource);

	if(pObjFile->Open(cGameDirectories::GameDirectories().strMediaDirectory + cGameDirectories::GameDirectories().strModelDirectory + strModelFile + ".spdo", std::ios_base::in))
	{
		cString strLine;
		vector<cString> vtokens;
		stModelDef def;
		int iCurrentVertexNo = 0;
		int iCurrentIndexNo = 0;
		int iCurrentSubsetNumber = -1;
		do
		{
			strLine = pObjFile->ReadLine();
			if(!strLine.IsEmpty())
			{
				strLine.TrimBoth();
				if(!strLine.IsEmpty())
				{
					vtokens.clear();
					strLine.Tokenize(' ', vtokens);
					// vertex Count
					if (vtokens[0] == "VertexCount")
					{
						def.iNumberOfVertices = GetIntValue(vtokens[1]);
						stTexVertex * pVertices = DEBUG_NEW stTexVertex[def.iNumberOfVertices];
						def.pVertices = pVertices;
					}
					//vertex data
					else if(vtokens[0] == "v")
					{
						def.pVertices[iCurrentVertexNo].m_fX = GetFloatValue(vtokens[1]);
						def.pVertices[iCurrentVertexNo].m_fY = GetFloatValue(vtokens[2]);
						def.pVertices[iCurrentVertexNo].m_fZ = GetFloatValue(vtokens[3]);
						def.pVertices[iCurrentVertexNo].m_fTex0 = GetFloatValue(vtokens[4]);
						def.pVertices[iCurrentVertexNo].m_fTex1 = GetFloatValue(vtokens[5]);
						iCurrentVertexNo++;
					}
					// total index Count
					else if (vtokens[0] == "TotalIndexCount")
					{
						def.iNumberOfIndices = GetIntValue(vtokens[1]);
						unsigned long * pIndices = DEBUG_NEW unsigned long[def.iNumberOfIndices];
						def.pIndices = pIndices;
					}
					// faces/triangles
					else if (vtokens[0] == "t")
					{
						def.pIndices[iCurrentIndexNo++] = GetIntValue(vtokens[1]);
						def.pIndices[iCurrentIndexNo++] = GetIntValue(vtokens[2]);
						def.pIndices[iCurrentIndexNo++] = GetIntValue(vtokens[3]);
					}
					// min pos of Bounding Box
					else if(vtokens[0] == "BBMin")
					{
						def.vBoundingBoxMinPos.x = GetFloatValue(vtokens[1]);
						def.vBoundingBoxMinPos.y = GetFloatValue(vtokens[2]);
						def.vBoundingBoxMinPos.z = GetFloatValue(vtokens[3]);
					}
					// max pos of Bounding Box
					else if(vtokens[0] == "BBMax")
					{
						def.vBoundingBoxMaxPos.x = GetFloatValue(vtokens[1]);
						def.vBoundingBoxMaxPos.y = GetFloatValue(vtokens[2]);
						def.vBoundingBoxMaxPos.z = GetFloatValue(vtokens[3]);
					}
					// new subset
					else if(vtokens[0] == "Subset")
					{
						stModelDef::stSubsetDef subset;
						def.vSubsetsDef.push_back(subset);
						iCurrentSubsetNumber++;
					}
					else if(vtokens[0] == "startindex")
					{
						def.vSubsetsDef[iCurrentSubsetNumber].iStartIndexNo = GetIntValue(vtokens[1]);
					}
					else if(vtokens[0] == "indexcount")
					{
						def.vSubsetsDef[iCurrentSubsetNumber].iNumberOfIndicesinSubset = GetIntValue(vtokens[1]);
					}
					// min pos of subset Bounding Box
					else if(vtokens[0] == "SBBMin")
					{
						def.vSubsetsDef[iCurrentSubsetNumber].vBoundingBoxMinPos.x = GetFloatValue(vtokens[1]);
						def.vSubsetsDef[iCurrentSubsetNumber].vBoundingBoxMinPos.y = GetFloatValue(vtokens[2]);
						def.vSubsetsDef[iCurrentSubsetNumber].vBoundingBoxMinPos.z = GetFloatValue(vtokens[3]);
					}
					// max pos of subset Bounding Box
					else if(vtokens[0] == "SBBMax")
					{
						def.vSubsetsDef[iCurrentSubsetNumber].vBoundingBoxMaxPos.x = GetFloatValue(vtokens[1]);
						def.vSubsetsDef[iCurrentSubsetNumber].vBoundingBoxMaxPos.y = GetFloatValue(vtokens[2]);
						def.vSubsetsDef[iCurrentSubsetNumber].vBoundingBoxMaxPos.z = GetFloatValue(vtokens[3]);
					}
					else if(vtokens[0] == "diffusecolor")
					{
						int r = GetIntValue(vtokens[1]);
						int b = GetIntValue(vtokens[2]);
						int g = GetIntValue(vtokens[3]);
						int a = GetIntValue(vtokens[4]);
						def.vSubsetsDef[iCurrentSubsetNumber].diffuseColor = cColor(r, g, b, a);
					}
					else if(vtokens[0] == "dTex")
					{
						def.vSubsetsDef[iCurrentSubsetNumber].strDiffuseTextureFilename = vtokens[1];
					}
				}
			}
		}
		while(!pObjFile->IsEOF() || !strLine.IsEmpty());
		pObjFile->Close();

		pModel->VOnInitialization(def);

		//SAFE_DELETE(pResource);
		SAFE_DELETE_ARRAY(def.pVertices);
		SAFE_DELETE_ARRAY(def.pIndices);
	}
}

// *****************************************************************************
float cObjModelLoader::GetFloatValue(const cString & strVal)
{
	tOptional<float> val = strVal.ToFloat();
	if (val.IsValid())
	{
		return *val;
	}
	return 0;
}

// *****************************************************************************
int cObjModelLoader::GetIntValue(const Base::cString & strVal)
{
	tOptional<int> val = strVal.ToInt();
	if (val.IsValid())
	{
		return *val;
	}
	return 0;

}
// *****************************************************************************
IObjModelLoader * IObjModelLoader::GetInstance()
{
	if(cObjModelLoader::s_pModelLoader == NULL)
		cObjModelLoader::s_pModelLoader = DEBUG_NEW cObjModelLoader();
	return cObjModelLoader::s_pModelLoader;
}

// *********************************************************************************
void IObjModelLoader::Destroy()
{
	SAFE_DELETE(cObjModelLoader::s_pModelLoader);
}
