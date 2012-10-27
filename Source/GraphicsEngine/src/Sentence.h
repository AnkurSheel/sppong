// *************************************************************************
//  Sentence   version:  1.0   Ankur Sheel  date: 2012/10/10
//  ------------------------------------------------------------------------
//  
//  ------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *************************************************************************
// 
// *************************************************************************
#ifndef Sentence_h__
#define Sentence_h__

#include "Sentence.hxx"

namespace Base
{
	class cString;
}

namespace Graphics
{
	class cMyFont;
}

namespace Graphics
{
	class cSentence
		: public ISentence
	{
	public:
		cSentence() ;
		~cSentence() ;
	
	private:
		void VRender(const ICamera * const pCamera);
		void VSetPosition(const Base::cVector2 & vPosition);
		void VGetText(Base::cString & strText) const;
		void VSetText(const Base::cString & strText);
		void VSetTextColor(const Base::cColor & colorText);
		float VGetWidth() const ;
		float VGetWidth(const Base::cString & strText) const;
		float VGetHeight() const;
		void VSetHeight(const float fTextHeight);
		/********************************************//**
		 * return True if the vertex buffer was created successfully
		 *
		 * Creates the vertex buffer using the vertex data
		 ***********************************************/
		bool CreateVertexBuffer();
		bool CreateIndexBuffer( );
		/********************************************//**
		 * @param[in] pCamera The camera which contains the current view matrix
		 * return True if the vertex buffer was updated successfully
		 * 
		 * Recalculates the coordinates and updates the vertex data if the position has changed
		 ***********************************************/
		bool RecalculateVertexData(const ICamera * const pCamera);
		void Cleanup();
		bool VInitialize(shared_ptr<IMyFont> pFont, 
			const Base::cString & strText, const Base::cColor & textColor);

	private:
		ID3D11Buffer * 						m_pVertexBuffer;	/*!< The vertex buffer */
		ID3D11Buffer *						m_pIndexBuffer;		/*!< The index buffer */
		Base::cString						m_strText;			/*!< The text that has to be displayed */
		shared_ptr<cMyFont>					m_pFont;
		D3DXVECTOR4							m_TextColor;		/*!< The text color */
		int									m_iVertexCount;		/*!< The number of vertices that have to be displayed */
		int									m_iIndexCount;		/*!< The number of indices that have to be displayed */
		Base::cVector2						m_vPosition;		/*!< The current position of the sprite */
		bool								m_bIsDirty;			/*!< True if the vertex data needs to be recalculated */
		float								m_fWidth;
		float								m_fScale;
	};
}
#endif // Sentence_h__