//
//  SamplesFramework.cpp
//  Candy_Samples
//
//  Created by Dongyang.Cai on 24/10/2016.
//
//

#include "SamplesFramework.h"

#include "CEGUI/RendererModules/OpenGL/GLRenderer.h"

#ifdef __APPLE__
#   include <Carbon/Carbon.h>
#endif

using namespace CEGUI;

SamplesFramework::SamplesFramework()
: d_renderer(nullptr)
, d_resourceProvider(nullptr)
, d_imageCodec(nullptr)
{
    
}

SamplesFramework::~SamplesFramework()
{
    
}

void SamplesFramework::init()
{
    d_renderer = &CEGUI::OpenGLRenderer::create();
    // start up CEGUI system using objects created in subclass constructor.
    CEGUI::System::create(*d_renderer, d_resourceProvider, 0, d_imageCodec);
    
    // initialise the required dirs for the DefaultResourceProvider
    CEGUI::DefaultResourceProvider* rp =
        static_cast<CEGUI::DefaultResourceProvider*>
            (CEGUI::System::getSingleton().getResourceProvider());
    
    const char* dataPathPrefix = getDataPathPrefix();
    char resourcePath[PATH_MAX];
    
    CEGUI::Font& font = FontManager::getSingleton().createFromFile("DejaVuSans-12.font");
}

void SamplesFramework::start()
{
    
}

void SamplesFramework::end()
{
    
}

const char* SamplesFramework::getDataPathPrefix() const
{
    static char dataPathPrefix[PATH_MAX];
    
#ifdef __APPLE__
    CFURLRef datafilesURL = CFBundleCopyResourceURL(CFBundleGetMainBundle(),
                                                    CFSTR("datafiles"),
                                                    0, 0);
    CFURLGetFileSystemRepresentation(datafilesURL, true,
                                     reinterpret_cast<UInt8*>(dataPathPrefix),
                                     PATH_MAX);
    CFRelease(datafilesURL);
#else
    char* envDataPath = 0;
    
    // get data path from environment var
    envDataPath = getenv(DATAPATH_VAR_NAME);
    
    // set data path prefix / base directory.  This will
    // be either from an environment variable, or from
    // a compiled in default based on original configure
    // options
    if (envDataPath != 0)
        strcpy(dataPathPrefix, envDataPath);
    else
        strcpy(dataPathPrefix, "../datafiles");
#endif
    
    return dataPathPrefix;
}
