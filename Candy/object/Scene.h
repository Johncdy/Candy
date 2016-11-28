//
//  Scene.h
//  Candy
//
//  Created by Dongyang.Cai on 25/11/2016.
//
//

#ifndef Scene_h
#define Scene_h

#include "include/CandyMacros.h"

#include "object/Camera.h"
#include "object/node/Node.h"

#include "renderer/Renderer.h"

#include <vector>

NS_DY_BEGIN

NS_OBJECT_BEGIN

class Scene : public Node {
public:
    static Scene* create();
    
    /** Get all cameras.
     *
     * @return The vector of all cameras, ordered by camera depth.
     * @js NA
     */
    const std::vector<Camera*>& getCameras();
    
    /** Get the default camera.
     * @js NA
     * @return The default camera of scene.
     */
    Camera* getDefaultCamera() const { return _defaultCamera; }
    
    /** Render the scene.
     * @param renderer The renderer use to render the scene.
     * @js NA
     */
    virtual void render(renderer::Renderer* renderer, const math::Mat4& eyeTransform, const math::Mat4* eyeProjection = nullptr);
    
protected:
    Scene();
    ~Scene();
    
    virtual bool init() override;
    
private:
    //weak ref, default camera created by scene, _cameras[0]
    Camera* _defaultCamera;
    //weak ref to Camera
    std::vector<Camera*> _cameras;
    // order is dirty, need sort
    bool _isCameraOrderDirty;
};

NS_OBJECT_END

NS_DY_END

#endif /* Scene_h */
