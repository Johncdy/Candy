//
//  SamplesFramework.h
//  Candy_Samples
//
//  Created by Dongyang.Cai on 24/10/2016.
//
//

#ifndef SamplesFramework_h
#define SamplesFramework_h

#include "CEGUI/CEGUI.h"

class SamplesFramework {
public:
    SamplesFramework();
    
    virtual ~SamplesFramework();
    
    void init();
    
    void start();
    
    void end();
    
    /*!
     \brief
     Setup standard sample resource group directory locations.  Default uses
     the CEGUI::DefaultResourceProvider - override if the sample base app
     being implemented uses something else!
     */
    void initialiseResourceGroupDirectories();
    
    //! initialise the standard default resource groups used by the samples.
    void initialiseDefaultResourceGroups();
    
    /*!
     \brief
     Return the path prefix to use for datafiles.  The value returned
     is obtained via a environment variable named 'CEGUI_SAMPLE_DATAPATH'
     if the variable is not set, a default will be used depending on the
     build system in use.
     */
    const char* getDataPathPrefix() const;
    
private:
    //! Renderer to use.  This MUST be set in the subclass constructor.
    CEGUI::Renderer* d_renderer;
    //! ImageCodec to use.  Set in subclass constructor, may be 0.
    CEGUI::ImageCodec* d_imageCodec;
    //! ResourceProvider to use.  Set in subclass constructor, may be 0.
    CEGUI::ResourceProvider* d_resourceProvider;
    
    //! GeometryBuffer used for drawing the spinning CEGUI logo
    CEGUI::GeometryBuffer* d_logoGeometry;
};

#endif /* SamplesFramework_h */
