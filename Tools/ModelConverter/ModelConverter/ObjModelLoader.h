// *************************************************************************
//  ObjModelLoader   version:  1.0   Ankur Sheel  date: 2012/10/29
//  ------------------------------------------------------------------------
//  
//  ------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *************************************************************************
// 
// *************************************************************************

namespace Utilities
{
	class IFileInput;
}

namespace Graphics
{
	struct stObjFaceInfo
	{
		int iPosIndex;
		int iTexCoordIndex;

		stObjFaceInfo()
			:iPosIndex(0)
			, iTexCoordIndex(0)
		{
		}
	};
	
	struct stObjSubsetData
	{
		std::vector<stObjFaceInfo> vFaces;
		Base::cColor diffuseColor;
		Base::cString strDiffuseTextureFilename;
		int iStartIndexNo;

		stObjSubsetData()
			: iStartIndexNo(0)
		{
		}
	};

	struct stSPDOVertexData
	{
		Base::cVector3 vPos;
		Base::cVector3 vTex;
	};

	struct stSPDOSubsetData
	{
		std::vector<int> vIndexData;
		Base::cColor diffuseColor;
		Base::cString strDiffuseTextureFilename;
		int iStartIndexNo;

		stSPDOSubsetData()
			: iStartIndexNo(0)
		{
		}
	};

	struct stMaterial
	{
		Base::cString strMatName;

		// Surface's colors
		Base::cColor Diffuse;       // Transparency (Alpha) stored in 4th component
		//D3DXVECTOR3 Ambient;
		//D3DXVECTOR4 Specular;      // Specular power stored in 4th component

		// Textures
		Base::cString strDiffuseTextureFilename;
		//int AmbientTextureID;
		//int SpecularTextureID;
		//int AlphaTextureID;
		//int NormMapTextureID;

		// Booleans so we don't implement techniques we don't need
		//bool HasDiffTexture;
		//bool HasAmbientTexture;
		//bool HasSpecularTexture;
		//bool HasAlphaTexture;
		//bool HasNormMap;
		//bool IsTransparent;
	};

	class cObjModelLoader
	{
		typedef std::map<Base::cString, stMaterial> MaterialMap;

	public:
		cObjModelLoader();
		~cObjModelLoader();
		void ConvertObjFile(const Base::cString & strObjFile, const Base::cString & strOutputFile);

	private:
		void LoadMaterialFile(const Base::cString & strMaterialFile);
		float GetFloatValue(const Base::cString & strVal);
		int GetIntValue(const Base::cString & strVal);
		stObjFaceInfo ParseFaceInfo(const Base::cString & strFaceVal);

	private:
		MaterialMap						m_MaterialsMap;
		//std::vector<stObjSubsetData>	m_vSubset;
	};
}