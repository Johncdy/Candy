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
, d_logoGeometry(nullptr)
, d_spinLogo(false)
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
    
    initialiseDefaultResourceGroups();
    initialiseResourceGroupDirectories();

    // setup for spinning logo
    d_logoGeometry = &d_renderer->createGeometryBuffer();
    d_logoGeometry->setPivot(CEGUI::Vector3f(91.5f, 44.5f, 0));
    
    const CEGUI::Rectf scrn(d_renderer->getDefaultRenderTarget().getArea());
    d_logoGeometry->setClippingRegion(scrn);
    d_logoGeometry->setTranslation(CEGUI::Vector3f(10.0f, scrn.getSize().d_height - 89.0f, 0.0f));
    
    // create logo imageset and draw the image (we only ever draw this once)
    CEGUI::ImageManager::getSingleton().addFromImageFile("cegui_logo", "logo.png");
    CEGUI::ImageManager::getSingleton().get("cegui_logo").render(*d_logoGeometry, CEGUI::Rectf(0, 0, 183, 89), 0, CEGUI::ColourRect(0xFFFFFFFF));

    // clearing this queue actually makes sure it's created(!)
    CEGUI::System::getSingleton().getDefaultGUIContext().clearGeometry(CEGUI::RQ_OVERLAY);
    
    // subscribe handler to render overlay items
    CEGUI::System::getSingleton().getDefaultGUIContext().subscribeEvent(CEGUI::RenderingSurface::EventRenderQueueStarted, CEGUI::Event::Subscriber(&SamplesFramework::sampleOverlayHandler, this));
    
}

void SamplesFramework::start()
{
    
}

void SamplesFramework::end()
{
    
}

void SamplesFramework::initialiseDefaultResourceGroups()
{
    // initialise the required dirs for the DefaultResourceProvider
    CEGUI::DefaultResourceProvider* rp =
    static_cast<CEGUI::DefaultResourceProvider*>
    (CEGUI::System::getSingleton().getResourceProvider());
    
    const char* dataPathPrefix = getDataPathPrefix();
    char resourcePath[PATH_MAX];
    
    // for each resource type, set a resource group directory
    sprintf(resourcePath, "%s/%s", dataPathPrefix, "schemes/");
    rp->setResourceGroupDirectory("schemes", resourcePath);
    sprintf(resourcePath, "%s/%s", dataPathPrefix, "imagesets/");
    rp->setResourceGroupDirectory("imagesets", resourcePath);
    sprintf(resourcePath, "%s/%s", dataPathPrefix, "fonts/");
    rp->setResourceGroupDirectory("fonts", resourcePath);
    sprintf(resourcePath, "%s/%s", dataPathPrefix, "layouts/");
    rp->setResourceGroupDirectory("layouts", resourcePath);
    sprintf(resourcePath, "%s/%s", dataPathPrefix, "looknfeels/");
    rp->setResourceGroupDirectory("looknfeels", resourcePath);
    sprintf(resourcePath, "%s/%s", dataPathPrefix, "lua_scripts/");
    rp->setResourceGroupDirectory("lua_scripts", resourcePath);
    sprintf(resourcePath, "%s/%s", dataPathPrefix, "xml_schemas");
    rp->setResourceGroupDirectory("xml_schemas", resourcePath);
    sprintf(resourcePath, "%s/%s", dataPathPrefix, "animations");
    rp->setResourceGroupDirectory("animations", resourcePath);
}

void SamplesFramework::initialiseResourceGroupDirectories()
{
    CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
    CEGUI::Font::setDefaultResourceGroup("fonts");
    CEGUI::Scheme::setDefaultResourceGroup("schemes");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
    CEGUI::WindowManager::setDefaultResourceGroup("layouts");
    CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");
    CEGUI::AnimationManager::setDefaultResourceGroup("animations");
    
    // setup default group for validation schemas
    CEGUI::XMLParser *parser = CEGUI::System::getSingleton().getXMLParser();
    if (parser->isPropertyPresent("SchemaDefaultResourceGroup")) {
        parser->setProperty("SchemaDefaultResourceGroup", "schemas");
    }
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

bool SamplesFramework::sampleOverlayHandler(const CEGUI::EventArgs& args)
{
    if (static_cast<const CEGUI::RenderQueueEventArgs&>(args).queueID != CEGUI::RQ_OVERLAY)
        return false;
    
    // draw the logo
    d_logoGeometry->draw();
    
    return true;
}

void SamplesFramework::renderSingleFrame(const float elapsed)
{
    CEGUI::System& gui_system(CEGUI::System::getSingleton());
    
    gui_system.injectTimePulse(elapsed);
    updateLogo(elapsed);
    
    CEGUI::Renderer* gui_renderer(gui_system.getRenderer());
    gui_renderer->beginRendering();
    
    renderGUIContexts();
    
    gui_renderer->endRendering();
    CEGUI::WindowManager::getSingleton().cleanDeadPool();

}

void SamplesFramework::renderGUIContexts()
{
    CEGUI::System& gui_system(CEGUI::System::getSingleton());
    gui_system.getDefaultGUIContext().draw();
}

void SamplesFramework::updateLogo(const float elapsed)
{
    if (!d_spinLogo)
        return;
    
    static float rot = 0.0f;
    d_logoGeometry->setRotation(CEGUI::Quaternion::eulerAnglesDegrees(rot, 0, 0));
    rot = fmodf(rot + 180.0f * elapsed, 360.0f);
}
