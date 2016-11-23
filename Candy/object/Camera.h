//
//  Camera.h
//  Candy
//
//  Created by Dongyang.Cai on 22/11/2016.
//
//

#ifndef Camera_h
#define Camera_h

#include "include/CandyMacros.h"
#include "object/node/Node.h"

NS_DY_BEGIN

NS_OBJECT_BEGIN

/**
 * Note:
 * Scene creates a default camera. And the default camera mask of Node is 1, therefore it can be seen by the default camera.
 * During rendering the scene, it draws the objects seen by each camera in the added order except default camera. The default camera is the last one being drawn with.
 * It's usually a good idea to render 3D objects in a separate camera.
 * And set the 3d camera flag to CameraFlag::USER1 or anything else except DEFAULT. Dedicate The DEFAULT camera for UI, because it is rendered at last.
 * You can change the camera order to get different result when depth test is not enabled.
 * For each camera, transparent 3d sprite is rendered after opaque 3d sprite and other 2d objects.
 */

/**
 Viewport is a normalized to FrameBufferObject
 But for default FBO, the size is absolute.
 */
struct ViewPort {
    ViewPort(float left, float bottom, float width, float height);
    
    float _left;
    float _bottom;
    float _width;
    float _height;
};

class Camera : public Node {
public:
    enum class Flag {
        DEFAULT = 1,
        USER1 = 1 << 1,
        USER2 = 1 << 2,
        USER3 = 1 << 3,
        USER4 = 1 << 4,
        USER5 = 1 << 5,
        USER6 = 1 << 6,
        USER7 = 1 << 7,
        USER8 = 1 << 8,
    };
    
    /**
     * The type of camera.
     */
    enum class Type {
        PERSPECTIVE = 1,
        ORTHOGRAPHIC = 2,
    };
    
    /**
     * Creates a perspective camera.
     *
     * @param fieldOfView The field of view for the perspective camera (normally in the range of 40-60 degrees).
     * @param aspectRatio The aspect ratio of the camera (normally the width of the viewport divided by the height of the viewport).
     * @param nearPlane The near plane distance.
     * @param farPlane The far plane distance.
     */
    static Camera* createPerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane);
    
    /**
     * Creates an orthographic camera.
     *
     * @param zoomX The zoom factor along the X-axis of the orthographic projection (the width of the ortho projection).
     * @param zoomY The zoom factor along the Y-axis of the orthographic projection (the height of the ortho projection).
     * @param nearPlane The near plane distance.
     * @param farPlane The far plane distance.
     */
    static Camera* createOrthographic(float zoomX, float zoomY, float nearPlane, float farPlane);
    
    /**
     * Get the visiting camera , the visiting camera shall be set on Scene::render
     */
    static const Camera* getVisitingCamera();
    
    /**
     * Get the default camera of the current running scene.
     */
    static const Camera* getDefaultCamera();
    
    /**
     * Gets the type of camera.
     *
     * @return The camera type.
     */
    Camera::Type getCameraType() const { return _type; }
    
    Camera::Flag getCameraFlag() const { return _flag; }
    
    void setCameraFlag(Camera::Flag flag) { _flag = flag; }
    
    static void setDefaultViewPort(const ViewPort& vp) { _defaultViewPort = vp; }
    
    static const ViewPort& getDefaultViewPort() { return _defaultViewPort; }
    
    /**
     * Gets the camera's projection matrix.
     *
     * @return The camera projection matrix.
     */
    const math::Mat4& getProjectionMatrix() const;
    
    /**
     * Gets the camera's view matrix.
     *
     * @return The camera view matrix.
     */
    const math::Mat4& getViewMatrix() const;
    
    /**get view projection matrix*/
    const math::Mat4& getViewProjectionMatrix() const;
    
    /**
     * set depth, camera with larger depth is drawn on top of camera with smaller depth, the depth of camera with CameraFlag::DEFAULT is 0, user defined camera is -1 by default
     */
    void setDepth(int8_t depth);
    
    /**
     * get depth, camera with larger depth is drawn on top of camera with smaller depth, the depth of camera with CameraFlag::DEFAULT is 0, user defined camera is -1 by default
     */
    int8_t getDepth() const { return _depth; }
    
    /**
     * Get the frustum's far plane.
     */
    float getFarPlane() const { return _farPlane; }
    
    /**
     * Get the frustum's near plane.
     */
    float getNearPlane() const { return _nearPlane; }
    
protected:
    Camera();
    ~Camera();
    
    bool initPerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane);
    
    bool initOrthographic(float zoomX, float zoomY, float nearPlane, float farPlane);
    
private:
    Camera::Type _type;
    Camera::Flag _flag;
    
    math::Mat4 _projection;
    
    int8_t _depth;
    float _fieldOfView;
    float _aspectRatio;
    float _farPlane;
    float _nearPlane;
    float _zoom[2];
    
    static Camera* _visitingCamera;
    static ViewPort _defaultViewPort;
};

NS_OBJECT_END

NS_DY_END

#endif /* Camera_h */
