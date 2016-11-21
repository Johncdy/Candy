//
//  RenderCommand.h
//  Candy
//
//  Created by Dongyang.Cai on 19/11/2016.
//
//

#ifndef RenderCommand_h
#define RenderCommand_h

#include "include/CandyMacros.h"

#include "math/Mat4.h"

NS_DY_BEGIN

NS_RENDERER_BEGIN

class RenderCommand {
public:
    /**Enum the type of render command. */
    enum class Type {
        /** Reserved type.*/
        UNKNOW_COMMAND,
        /** Quad command, used for draw quad.*/
        QUAD_COMMAND,
        /**Custom command, used for calling callback for rendering.*/
        CUSTOM_COMMAND,
        /**Batch command, used for draw batches in texture atlas.*/
        BATCH_COMMAND,
        /**Group command, which can group command in a tree hierarchy.*/
        GROUP_COMMAND,
        /**Mesh command, used to draw 3D meshes.*/
        MESH_COMMAND,
        /**Primitive command, used to draw primitives such as lines, points and triangles.*/
        PRIMITIVE_COMMAND,
        /**Triangles command, used to draw triangles.*/
        TRIANGLES_COMMAND,
    };
    
    /**
     Init function, will be called by all the render commands.
     @param globalZOrder The global order of command, used for rendercommand sorting.
     @param modelViewTransform Modelview matrix when submitting the render command.
     @param flags Flag used to indicate whether the command should be draw at 3D mode or not.
     */
    void init(float globalZOrder, const math::Mat4& modelViewTransform, uint32_t flags);
    
    /** Get global Z order. */
    float getGlobalOrder() const { return _globalOrder; }
    
    /** Returns the Command type. */
    Type getType() { return _type; }
    
    /** Returns whether is transparent. */
    bool isTransparent() const { return _isTransparent; }
    
    /** Set transparent flag. */
    void setTransparent(bool isTransparent) { _isTransparent = isTransparent; }
    
    /**
     Get skip batching status, if a rendering is skip batching, it will be forced to be rendering separately.
     */
    bool isSkipBatching() const {return _isSkipBatching; }
    
    /**Set skip batching.*/
    void setSkipBatching(bool value) { _isSkipBatching = value; }
    
    /**Whether the command should be rendered at 3D mode.*/
    bool is3D() const { return _is3D; }
    
    /**Set the command rendered in 3D mode or not.*/
    void set3D(bool value) { _is3D = value; }
    
    /**Get the depth by current model view matrix.*/
    float getDepth() const { return _depth; }
    
protected:
    /** Constructor.*/
    RenderCommand();
    /** Destructor.*/
    virtual ~RenderCommand();
    //used for debug but it is not implemented.
    void printID();
    
    /**Type used in order to avoid dynamic cast, faster. */
    Type _type;
    /** Commands are sort by global Z order. */
    float _globalOrder;
    /** Transparent flag. */
    bool _isTransparent;
    /**
     QuadCommand and TrianglesCommand could be auto batched if there material ID is the same, however, if
     a command is skip batching, it would be forced to draw in a separate function call, and break the batch.
     */
    bool _isSkipBatching;
    /** Is the command been rendered on 3D pass. */
    bool _is3D;
    /** Depth from the model view matrix.*/
    float _depth;
};


NS_RENDERER_END

NS_DY_END

#endif /* RenderCommand_h */
