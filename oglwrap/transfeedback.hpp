/** @file transfeedback.hpp
    @brief Implements transform feedback functionality.
*/

#ifndef TRANSFORMFEEDBACK_HPP
#define TRANSFORMFEEDBACK_HPP

namespace oglwrap {

/// A wrapper class for transform feedback.
/** Transform Feedback is the process of altering the rendering pipeline so that primitives
  * processed by a Vertex Shader and optionally a Geometry Shader will be written to buffer
  * objects. This allows one to preserve the post-transform rendering state of an object and
  * resubmit this data multiple times. */
/// @see glGenTransformFeedbacks, glDeleteTransformFeedbacks
class TransformFeedback : protected RefCounted {
    /// The handle for the TransformFeedback
    ObjectExt<glGenTransformFeedbacks, glDeleteTransformFeedbacks> handle;
    enum TFBstate{none, working, paused} state;
public:
    /// Generates a transform feedback.
    TransformFeedback() : state(none) {}

    /// Creates a transform feedback and activates it. It will work till the variable's lifetime.
    /// @param mode - The primitive type the TFB should use.
    /// @see glGenTransformFeedbacks
    TransformFeedback(TFB_PrimType mode) : state(working) {
        bind();
        begin(mode);
    }

    /// Deletes the transform feedback, if only one instance of it exists.
    /** Also ends it if it's active. In this case it will change the currently active TFB. */
    /// @see glDeleteTransformFeedbacks
    ~TransformFeedback() {
        if(!handle.isDeletable())
            return;
        if(state != none) {
            bind();
            end();
        }
    }

    /// Binds the transform feedback.
    /// @see glBindTransformFeedback
    void bind() const {
        gl( BindTransformFeedback(GL_TRANSFORM_FEEDBACK, handle) );
    }

    /// Unbinds the currently bound transform feedback.
    /// @see glBindTransformFeedback
    void unbind() const {
        gl( BindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0) );
    }

    /// Begins the transform feedback mode.
    /// @param mode - The primitive type the TFB should use.
    /// @see glBeginTransformFeedback
    void begin(TFB_PrimType mode) {
        state = working;
        gl( BeginTransformFeedback(mode) );
    }

    /// Ends the transform feedback mode.
    /// @see glEndTransformFeedback
    void end() {
        state = none;
        gl( EndTransformFeedback() );
    }

    /// Pauses transform feedback operations on the currently active transform feedback object.
    /// @see glPauseTransformFeedback
    void pause() {
        state = paused;
        gl( PauseTransformFeedback() );
    }

    /// Resumes transform feedback operations on the currently active transform feedback object.
    /// @see glResumeTransformFeedback
    void resume() {
        state = working;
        gl( ResumeTransformFeedback() );
    }
};

};

#endif