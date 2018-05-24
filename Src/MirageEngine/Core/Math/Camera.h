#pragma once
#include "Core\Math\Vector3.h"
#include "Core\Math\Matrix.h"
#include <tuple>

namespace MirageMath
{
	enum class eCameraProjectionType
	{
		Perspertive,
		Ortho,
	};

	class Camera
	{
	public:
		Camera(Vector3f viewLocation, Vector3f viewTarget, Vector3f viewUp, f32 surfaceWidth, f32 surfaceHeight)
		{
			mViewLocation = viewLocation;
			mViewTarget = viewTarget;
			mViewUp = viewUp;
			mWidth = surfaceWidth;
			mSurfaceHeight = surfaceHeight;
			mAspect = mWidth / mSurfaceHeight;
			CalculateViewMatrix();
			CalculateProjectionMatrix(mProjectionType);
		}

		void SetViewLocation(Vector3f viewLocation)
		{
			mViewLocation = viewLocation;
			CalculateViewMatrix();
		}
		void SetViewTarget(Vector3f viewTarget)
		{
			mViewTarget = viewTarget;
			CalculateViewMatrix();
		}
		void SetViewUp(Vector3f viewUp)
		{
			mViewUp = viewUp;
			CalculateViewMatrix();
		}

		void SetFOV(f32 fov) 
		{
			mFOV = fov; 
			CalculateProjectionMatrix(eCameraProjectionType::Perspertive);
		}
		void SetWidth(f32 width) 
		{
			mWidth = width;
			mAspect = mWidth / mSurfaceHeight;
			CalculateProjectionMatrix(mProjectionType);
		}
		void SetHeight(f32 height) 
		{
			mSurfaceHeight = height;
			mAspect = mWidth / mSurfaceHeight;
			CalculateProjectionMatrix(mProjectionType);
		}
		void SetNF(f32 near, f32 far)
		{
			mNear = near;
			mFar = far;
			CalculateProjectionMatrix(mProjectionType);
		}
		void SetLRTB(f32 left, f32 right, f32 bottom, f32 top)
		{
			mLeft = left;
			mRight = right;
			mBottom = bottom;
			mTop = top;
			CalculateProjectionMatrix(eCameraProjectionType::Ortho);
		}
		
		MEINLINE void SetProjectionType(eCameraProjectionType projectionType)
		{
			mProjectionType = projectionType;
		}

		MEINLINE Matrix4x4f& GetViewMatrix() { return mViewMatrix; }
		MEINLINE Matrix4x4f& GetProjectionMatrix() { return mProjectionMatrix; }
		MEINLINE Vector3f GetViewLocation() { return mViewLocation; }
		MEINLINE Vector3f GetViewTarget() { return mViewTarget; }
		MEINLINE Vector3f GetViewUp() { return mViewUp; }
		MEINLINE f32 GetFOV() { return mFOV; }
		MEINLINE std::tuple<f32, f32> GetNF()
		{
			return std::make_tuple(mNear, mFar);
		}
		MEINLINE std::tuple<f32, f32, f32, f32> GetLRTB()
		{
			return std::make_tuple(mLeft, mRight, mBottom, mTop);
		}
		MEINLINE eCameraProjectionType GetProjectionType() { return mProjectionType; }

	private:
		void CalculateProjectionMatrix(eCameraProjectionType type = eCameraProjectionType::Perspertive)
		{
			if (mProjectionType == eCameraProjectionType::Perspertive && mProjectionType == type)
				mProjectionMatrix = Matrix4x4f::Perspertive(mFOV, 1, mNear, mFar);
			else if (mProjectionType == eCameraProjectionType::Ortho  && mProjectionType == type)
				mProjectionMatrix = Matrix4x4f::Ortho(mLeft, mRight, mBottom, mTop, mNear, mFar);
		}
		MEINLINE void CalculateViewMatrix()
		{
			mViewMatrix = Matrix4x4f::LookAt(mViewLocation, mViewTarget, mViewUp);
		}
		
	private:
		Vector3f mViewLocation, mViewTarget, mViewUp;

		// Default project type is perspertive.
		eCameraProjectionType mProjectionType = eCameraProjectionType::Perspertive;

		f32 mFOV=60;
		f32 mNear=0,  mFar=1000;
		f32 mLeft=-1,  mRight=1,  mTop=1,  mBottom=-1;
		f32 mWidth=800,  mSurfaceHeight=600;
		f32 mAspect = 1;

		Matrix4x4f mViewMatrix;
		Matrix4x4f mProjectionMatrix;
	};
}