#pragma once
#include "Vector3.h"

namespace MirageMath
{
	template<class T>
	struct Rotater
	{
	public:
		Rotater(){
			pitch = 0;
			yaw = 0;
			roll = 0;
		}
		Rotater(T InPitch, T InYaw, T InRoll){
			pitch = InPitch;
			yaw = InYaw;
			roll = InRoll;
		}

		MEINLINE Rotater operator+(const Rotater& In) const{
			return Rotater(pitch + In.pitch, yaw + In.yaw, roll + In.roll);
		}
		MEINLINE Rotater operator-(const Rotater& In) const{
			return Rotater(pitch - In.pitch, yaw - In.yaw, roll - In.roll);
		}
		MEINLINE Rotater operator*(const T scale) const{
			return Rotater(pitch*scale, yaw*scale, roll*scale);
		}
		MEINLINE void operator+=(const Rotater& In)
		{
			pitch += In.pitch;
			yaw += In.yaw;
			roll += In.roll;
		}
		MEINLINE void operator-=(const Rotater& In)
		{
			pitch -= In.pitch;
			yaw -= In.yaw;
			roll -= In.roll;
		}
		MEINLINE Rotater operator*=(const T scale)
		{
			pitch *= scale;
			yaw *= scale;
			roll *= scale;

			return *this;
		}
		MEINLINE Rotater operator -() const
		{
			return Rotater(-pitch, -yaw, -roll);
		}
		bool operator == (const Rotater& In) const
		{
			return (pitch == In.pitch) && (yaw == In.yaw) && (roll == In.roll);
		}
		bool operator != (const Rotater& In) const
		{
			return (pitch != In.pitch) && (yaw != In.yaw) && (roll != In.roll);
		}

		MEINLINE Rotater Add(const T deltaPitch, const T deltaYaw, const T deltaRoll)
		{
			pitch += deltaPitch;
			yaw += deltaYaw;
			roll += deltaRoll;
			return *this;
		}
		MEINLINE Vector3f Eular() const
		{
			return Vector3f(roll, pitch, yaw);
		}

	public:
		static Rotater MakeFromEular(const Vector3f& eular) 
		{
			return Rotater(eular.y, eular.z, eular.x);
		}

	public:
		static const Rotater Zero;

	public:
		/*Rotation around the right axis(Y axis), looking up and down.*/
		T pitch = 0;
		/*Rotation around the up axis(Z axis), Running in circles.*/
		T yaw = 0;
		/*Rotation around the forward axis(X axis), Tilting your head.*/
		T roll = 0;
	};

	template<class T> const Rotater<T> Rotater<T>::Zero = Rotater<T>(0, 0, 0);

	using Rotaterf = Rotater<f32>;
	using RotaterF = Rotater<f64>;
}