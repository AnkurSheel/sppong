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
#include "Optional.h"
#include "Vector3.h"
#include "FileInput.hxx"
#include "FileOutput.hxx"

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
void cObjModelLoader::ConvertObjFile(const Base::cString & strObjFile, const Base::cString & strOutputFile)
{
	shared_ptr<IFileInput> pObjFile = shared_ptr<IFileInput>(IFileInput::CreateInputFile());

	if(pObjFile->Open(strObjFile, std::ios_base::in))
	{
		cString strLine;
		vector<cString> vtokens;
		vector<cVector3> vVertexPositions;
		vector<cVector3> vVertexTexCoordinates;
		int iCurrentSubset = -1;
		int iStartIndexNo = 0;
		std::vector<stObjSubsetData>	vObjSubset;
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

						vVertexPositions.push_back(cVector3(x, y, z));
					}
					else if(vtokens[0] == "vt")
					{
						float u = GetFloatValue(vtokens[1]);
						float v = GetFloatValue(vtokens[2]);
						float w = 0.0f;
						if (vtokens.size() == 4)
						{
							w = GetFloatValue(vtokens[3]);
						}
						vVertexTexCoordinates.push_back(cVector3(u, v, w));
					}
					// faces/triangles
					else if (vtokens[0] == "f")
					{
						vObjSubset[iCurrentSubset].vFaces.push_back(ParseFaceInfo(vtokens[1]));
						vObjSubset[iCurrentSubset].vFaces.push_back(ParseFaceInfo(vtokens[2]));
						vObjSubset[iCurrentSubset].vFaces.push_back(ParseFaceInfo(vtokens[3]));
						iStartIndexNo += 3;
					}
					else if (vtokens[0] == "mtllib")
					{
						LoadMaterialFile(vtokens[1]);
					}
					else if (vtokens[0] == "usemtl")
					{
						MaterialMap::const_iterator curr = m_MaterialsMap.find(vtokens[1]);
						if (curr != m_MaterialsMap.end())
						{
							iCurrentSubset++;
							stObjSubsetData subset;
							subset.diffuseColor = curr->second.Diffuse;
							subset.iStartIndexNo = iStartIndexNo;
							subset.strDiffuseTextureFilename = curr->second.strDiffuseTextureFilename;
							vObjSubset.push_back(subset);
						}
					}
				}
			}
		}
		while(!pObjFile->IsEOF() || !strLine.IsEmpty());
		pObjFile->Close();

		vector<stSPDOSubsetData> vSubsetData;

		vector<stObjFaceInfo> vVertexIndex;
		vector<stSPDOVertexData> vVertexData;

		int totalVerts = 0;
		for(int i=0; i< vObjSubset.size(); i++)
		{
			stObjSubsetData objSubset = vObjSubset[i];
			stSPDOSubsetData subsetData;

			subsetData.diffuseColor = objSubset.diffuseColor;
			subsetData.iStartIndexNo = objSubset.iStartIndexNo;
			subsetData.strDiffuseTextureFilename = objSubset.strDiffuseTextureFilename;

			for(int j = 0; j< objSubset.vFaces.size(); j++)
			{
				stObjFaceInfo faceInfo = objSubset.vFaces[j];
				bool vertAlreadyExists = false;
				if(totalVerts >= 3)
				{
					for(int iCheck = 0; iCheck < totalVerts; iCheck++)
					{
						if(!vertAlreadyExists && faceInfo.iPosIndex == vVertexIndex[iCheck].iPosIndex
							&& faceInfo.iTexCoordIndex == vVertexIndex[iCheck].iTexCoordIndex)
						{
							subsetData.vIndexData.push_back(iCheck);		//Set index for this vertex
							vertAlreadyExists = true;		//If we've made it here, the vertex already exists
							break;
						}
					}
				}

				//If this vertex is not already in our vertex arrays, put it there
				if(!vertAlreadyExists)
				{
					vVertexIndex.push_back(faceInfo);
					subsetData.vIndexData.push_back(totalVerts);		//Set index for this vertex
					stSPDOVertexData spdoVertexData;
					spdoVertexData.vPos = vVertexPositions[faceInfo.iPosIndex];
					if (vVertexTexCoordinates.empty())
					{
						spdoVertexData.vTex = cVector3::Zero();
					}
					else
					{
						spdoVertexData.vTex = vVertexTexCoordinates[faceInfo.iTexCoordIndex];
					}
					vVertexData.push_back(spdoVertexData);
					totalVerts++;	//We created a new vertex
				}							
			}
			vSubsetData.push_back(subsetData);
		}

		shared_ptr<IFileOutput> pOutputFile = shared_ptr<IFileOutput>(IFileOutput::CreateOutputFile());

		if(pOutputFile->Open(strOutputFile, std::ios_base::out))
		{
			pOutputFile->WriteLine(cString(100, "VC %d\n\n", vVertexData.size()));
			for (int i=0; i<vVertexData.size(); i++)
			{
				pOutputFile->WriteLine(cString(100, "v %0.2f %0.2f %0.2f %0.2f %0.2f\n",
					vVertexData[i].vPos.m_dX, vVertexData[i].vPos.m_dY, vVertexData[i].vPos.m_dZ,
					vVertexData[i].vTex.m_dX, vVertexData[i].vTex.m_dY, vVertexData[i].vTex.m_dZ));
			}
			pOutputFile->WriteLine(cString(100, "\nSC %d\n", vSubsetData.size()));

			for(int i=0; i< vSubsetData.size(); i++)
			{
				pOutputFile->WriteLine(cString(100, "\nS %d\n\n", i));
				
				pOutputFile->WriteLine(cString(100, "si %d\n", vSubsetData[i].iStartIndexNo));
				pOutputFile->WriteLine(cString(100, "ic %d\n\n", vSubsetData[i].vIndexData.size()));

				for(int j=0; j<vSubsetData[i].vIndexData.size();)
				{
					pOutputFile->WriteLine("t ");
					pOutputFile->WriteLine(cString(100, "%d ", vSubsetData[i].vIndexData[j++]));
					pOutputFile->WriteLine(cString(100, "%d ", vSubsetData[i].vIndexData[j++]));
					pOutputFile->WriteLine(cString(100, "%d\n", vSubsetData[i].vIndexData[j++]));
				}
				pOutputFile->WriteLine(cString(100, "\ndc %d %d %d %d\n",
					vSubsetData[i].diffuseColor.m_iRed, vSubsetData[i].diffuseColor.m_iBlue,
					vSubsetData[i].diffuseColor.m_iGreen, vSubsetData[i].diffuseColor.m_iAlpha));

				pOutputFile->WriteLine("\n");
				if (!vSubsetData[i].strDiffuseTextureFilename.IsEmpty())
				{
					pOutputFile->WriteLine("dTex " + vSubsetData[i].strDiffuseTextureFilename + "\n");
				}
			}
		}
		pObjFile->Close();

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
					else if (vtokens[0] == "map_Kd")
					{
						MaterialMap::iterator curr = m_MaterialsMap.find(strCurrentMaterialName);
						if (curr != m_MaterialsMap.end())
						{
							(curr->second).strDiffuseTextureFilename = vtokens[1];

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
stObjFaceInfo cObjModelLoader::ParseFaceInfo(const Base::cString & strFaceVal)
{
	stObjFaceInfo faceInfo;

	vector<cString> vtokens;
	strFaceVal.Tokenize('/', vtokens);

	for (int i = 0; i<vtokens.size();i++)
	{
		int iVal = GetIntValue(vtokens[i]) - 1;
		if (i == 0)
		{
			faceInfo.iPosIndex = iVal;
		}
		else if (i == 1)
		{
			faceInfo.iTexCoordIndex = iVal;
		}
	}
	return faceInfo;
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
