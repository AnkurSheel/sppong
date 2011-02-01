#define DegtoRad(x)(x* D3DX_PI/180)

#define SAFE_DELETE(p) \
{ \
	if(p) \
	{ \
		delete (p) ; \
		(p)=NULL ; \
	} \
}

#define SAFE_DELETE_ARRAY(p) \
{ \
	if(p) \
	{ \
		delete [](p) ; \
		(p)=NULL ; \
	} \
}

#define SAFE_RELEASE(p) \
{ \
	if(p) \
	{ \
		(p)->Release() ; \
		(p)=NULL ; \
	} \
}

const int MAX_FILENAME_WIDTH = 256;