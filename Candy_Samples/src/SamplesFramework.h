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
};

#endif /* SamplesFramework_h */
