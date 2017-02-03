//
//  SamplesFramework.h
//  Candy_Samples
//
//  Created by Dongyang.Cai on 24/10/2016.
//
//

#ifndef SamplesFramework_h
#define SamplesFramework_h

#include "include/Candy.h"

#include "object/Layer.h"
#include "object/Scene.h"

#include "CEGUI/CEGUI.h"

class SamplesFramework : public candy::object::Layer {
public:
    
    SamplesFramework();
    
    virtual ~SamplesFramework();
    
    bool init();
    
    void start();
    
    void end();
    
    DY_CREATE_FUNC(SamplesFramework);
    
    static candy::object::Scene* scene();
    
    // CEGUI
    /*!
     \brief
     Setup standard sample resource group directory locations.  Default uses
     the CEGUI::DefaultResourceProvider - override if the sample base app
     being implemented uses something else!
     */
    void initialiseResourceGroupDirectories();
    
    //! initialise the standard default resource groups used by the samples.
    void initialiseDefaultResourceGroups();
    
    //! event handler function that draws the logo and FPS overlay elements.
    bool sampleOverlayHandler(const CEGUI::EventArgs& args);
    
    /*!
     \brief
     Render a single display frame.  This should be called by subclasses to
     perform rendering.
     
     This function handles all per-frame updates, calls beginRendering, then
     renders the CEGUI output, and finally calls endRendering.
     
     \param elapsed
     Number of seconds elapsed since last frame.
     */
    void renderSingleFrame(const float elapsed);
    
    void renderGUIContexts();
    
    /*!
     \brief
     Return the path prefix to use for datafiles.  The value returned
     is obtained via a environment variable named 'CEGUI_SAMPLE_DATAPATH'
     if the variable is not set, a default will be used depending on the
     build system in use.
     */
    const char* getDataPathPrefix() const;
    
    //! function that updates the logo rotation as needed.
    void updateLogo(const float elapsed);
    
private:
    //! Renderer to use.  This MUST be set in the subclass constructor.
    CEGUI::Renderer* d_renderer;
    //! ImageCodec to use.  Set in subclass constructor, may be 0.
    CEGUI::ImageCodec* d_imageCodec;
    //! ResourceProvider to use.  Set in subclass constructor, may be 0.
    CEGUI::ResourceProvider* d_resourceProvider;
    
    //! GeometryBuffer used for drawing the spinning CEGUI logo
    CEGUI::GeometryBuffer* d_logoGeometry;
    //! whether to spin the logo
    bool d_spinLogo;
};

#endif /* SamplesFramework_h */
