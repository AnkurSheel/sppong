#pragma once

namespace Utilities
{
	class cResource;
}
namespace Utilities
{
	class IResourceFile
	{
	public:
		virtual ~IResourceFile() {}
		virtual bool Open()=0;
		virtual int GetResourceSize(const cResource &r) = 0;
		virtual void GetResource(const cResource &r, char *buffer) = 0;
	};
}