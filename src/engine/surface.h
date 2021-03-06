#ifndef _surface_h_
#define _surface_h_

#include <mask.h>
#include <point.h>
#include <rect.h>
#include <tref.h>

#include "pixel.h"
#include "VRAMManager.h"

class Color;
class Context;
class Engine;
class IEngineFont;
class PixelFormat;
class ZFile;

//////////////////////////////////////////////////////////////////////////////
//
// SurfaceTypes
//
//////////////////////////////////////////////////////////////////////////////

class SurfaceTypeBase {};
typedef TBitMask<SurfaceTypeBase, DWORD> SurfaceType;

class SurfaceType2D				: public SurfaceType { public: SurfaceType2D			() : SurfaceType(0x01) {} };
class SurfaceType3D				: public SurfaceType { public: SurfaceType3D			() : SurfaceType(0x02) {} };
class SurfaceTypeZBuffer		: public SurfaceType { public: SurfaceTypeZBuffer		() : SurfaceType(0x08) {} };
class SurfaceTypeVideo			: public SurfaceType { public: SurfaceTypeVideo			() : SurfaceType(0x10) {} };
class SurfaceTypeDummy			: public SurfaceType { public: SurfaceTypeDummy			() : SurfaceType(0x20) {} };
class SurfaceTypeRenderTarget	: public SurfaceType { public: SurfaceTypeRenderTarget	() : SurfaceType(0x40) {} };
class SurfaceTypeColorKey		: public SurfaceType { public: SurfaceTypeColorKey		() : SurfaceType(0x80) {} };
class SurfaceTypeSystemMemory	: public SurfaceType { public: SurfaceTypeSystemMemory	() : SurfaceType(0x100) {} };

//////////////////////////////////////////////////////////////////////////////
//
// SurfaceSite
//
//////////////////////////////////////////////////////////////////////////////

class Surface;
class SurfaceSite : public IObject {
public:
    virtual void UpdateSurface(Surface* psurface) {}
};

//////////////////////////////////////////////////////////////////////////////
//
// Surface
//
//////////////////////////////////////////////////////////////////////////////

class Surface : public IObject {
public:
    //
    // constructors
    //

    virtual TRef<Surface> Copy() = 0;
    virtual TRef<Surface> CreateCompatibleSurface(const WinPoint& size, SurfaceType stype, SurfaceSite* psite = NULL) = 0;

    //
    // Set Attributes
    //

    virtual void SetSite(SurfaceSite* psite)      = 0;
    virtual void SetName(const ZString& str)      = 0;
    virtual void SetPixelFormat(PixelFormat* ppf) = 0;

    //
    // Get Attributes
    //

    virtual Engine*         GetEngine()      = 0;
    virtual SurfaceType     GetSurfaceType() = 0;
    virtual const WinPoint& GetSize()        = 0;
    virtual PixelFormat*    GetPixelFormat() = 0;

	// KGJV 32B - GetName goes public
    virtual const ZString& GetName()         = 0;

    //
    // Context
    //

    virtual Context* GetContext()                      = 0;
    virtual void     ReleaseContext(Context* pcontext) = 0;

    //
    // Rendering attributes
    //

    virtual void            Offset(const WinPoint& offset)       = 0;
    virtual const WinPoint& GetOffset()                          = 0;
    virtual WinRect         GetClipRect()                        = 0;
    virtual void            SetClipRect(const WinRect& rect)     = 0;
    virtual void            RestoreClipRect(const WinRect& rect) = 0;

    //
    // Direct Surface manipulation
    //

	virtual TEXHANDLE		GetTexHandle()							  = 0;

    //
    // Drawing
    //

    virtual void BitBlt(const WinPoint& point, Surface* psurfaceSource, bool bLocalCopy = false )  = 0;
    virtual void BitBlt(const WinPoint& point, Surface* psurfaceSource, const WinRect& rectSource) = 0;
    virtual void BitBlt(const WinRect& point, Surface* psurfaceSource)                             = 0;
    virtual void BitBlt(const WinRect& point, Surface* psurfaceSource, const WinRect& rectSource)  = 0;
    virtual void BitBltFromCenter(const WinPoint& point, Surface* psurfaceSource)                  = 0;
	virtual void CopySubsetFromSrc(const WinPoint& point, Surface* psurfaceSourceArg, const WinRect& rectSourceArg) = 0;
  

    virtual void FillRect(const WinRect& rect, Pixel pixel)        = 0;
    virtual void FillRect(const WinRect& rect, const Color& color) = 0;
    virtual void FillSurface(Pixel pixel)                          = 0;
    virtual void FillSurface(const Color& color)                   = 0;

    //
    // Text
    //

    virtual void DrawString(
        IEngineFont* pfont, 
        const Color& color, 
        const WinPoint& point, 
        const ZString& str
    ) = 0;

    virtual void DrawStringWithShadow(
        IEngineFont* pfont, 
        const Color& color, 
        const Color& colorShadow,
        const WinPoint& point, 
        const ZString& str
    ) = 0;
};

#endif
