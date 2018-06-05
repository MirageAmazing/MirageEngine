#include "Camera.h"

namespace Mirage{
	namespace Math {
	
		Camera::Camera(Vector3f viewLocation, Vector3f viewTarget, Vector3f viewUp, f32 surfaceWidth, f32 surfaceHeight){
			mViewLocation = viewLocation;
			mViewTarget = viewTarget;
			mViewUp = viewUp;
			mWidth = surfaceWidth;
			mSurfaceHeight = surfaceHeight;
			mAspect = mWidth / mSurfaceHeight;
			CalculateViewMatrix();
			CalculateProjectionMatrix(mProjectionType);
		}

		void Camera::SetViewLocation(Vector3f viewLocation){
			mViewLocation = viewLocation;
			CalculateViewMatrix();
		}
		void Camera::SetViewTarget(Vector3f viewTarget){
			mViewTarget = viewTarget;
			CalculateViewMatrix();
		}
		void Camera::SetViewUp(Vector3f viewUp){
			mViewUp = viewUp;
			CalculateViewMatrix();
		}

		void Camera::SetFOV(f32 fov){
			mFOV = fov;
			CalculateProjectionMatrix(eCameraProjectionType::Perspertive);
		}
		void Camera::SetWidth(f32 width){
			mWidth = width;
			mAspect = mWidth / mSurfaceHeight;
			CalculateProjectionMatrix(mProjectionType);
		}
		void Camera::SetHeight(f32 height){
			mSurfaceHeight = height;
			mAspect = mWidth / mSurfaceHeight;
			CalculateProjectionMatrix(mProjectionType);
		}
		void Camera::SetNF(f32 near, f32 far){
			mNear = near;
			mFar = far;
			CalculateProjectionMatrix(mProjectionType);
		}
		void Camera::SetLRTB(f32 left, f32 right, f32 bottom, f32 top){
			mLeft = left;
			mRight = right;
			mBottom = bottom;
			mTop = top;
			CalculateProjectionMatrix(eCameraProjectionType::Ortho);
		}
		void Camera::CalculateProjectionMatrix(eCameraProjectionType type){
			if (mProjectionType == eCameraProjectionType::Perspertive && mProjectionType == type)
				mProjectionMatrix = Matrix4x4f::Perspertive(mFOV, mAspect, mNear, mFar);
			else if (mProjectionType == eCameraProjectionType::Ortho  && mProjectionType == type)
				mProjectionMatrix = Matrix4x4f::Ortho(mLeft, mRight, mBottom, mTop, mNear, mFar);
		}

	}
}