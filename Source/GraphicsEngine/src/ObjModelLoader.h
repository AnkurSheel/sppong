// *************************************************************************
//  ObjModelLoader   version:  1.0   Ankur Sheel  date: 2012/10/29
//  ------------------------------------------------------------------------
//  
//  ------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *************************************************************************
// 
// *************************************************************************

#include "ObjModelLoader.hxx"

#include "vertexstruct.h"

namespace Utilities
{
	class IFileInput;
}

namespace Graphics
{
	// Create material structure
	struct stMaterial
	{
		Base::cString strMatName;

		// Surface's colors
		Base::cColor Diffuse;       // Transparency (Alpha) stored in 4th component
		//D3DXVECTOR3 Ambient;
		//D3DXVECTOR4 Specular;      // Specular power stored in 4th component

		//// Texture ID's to look up texture in SRV array
		//int DiffuseTextureID;
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
		: public IObjModelLoader
	{
		typedef std::map<Base::cString, stMaterial> MaterialMap;

	public:
		cObjModelLoader();
		~cObjModelLoader();
		void VLoadModelFromFile(const Base::cString & strModelFile, IModel * pModel);

	private:
		void LoadMaterialFile(const Base::cString & strMaterialFile);
		float GetFloatValue(const Base::cString & strVal);
		int GetIntValue(const Base::cString & strVal);

	private:
		MaterialMap		m_MaterialsMap;
	};
}