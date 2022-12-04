#include "Camera.hpp"

namespace engine
{
	Camera::Camera()
		: eye(0.0f, 0.5f, -1.0f), center(0.0f, 0.0f, 0.0f), up(0.0f, 1.0f, 0.0f)
	{
		this->updateAngles();
	}

	void Camera::move(Position position)
	{
		this->eye += position;
		this->updateCenter();
	}

	void Camera::moveAccordingToDirection(Position position)
	{
		Direction direction;
		direction.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
		direction.y = sin(glm::radians(this->pitch));
		direction.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
		this->eye += position.z * direction;
		direction.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch - 90.f));
		direction.y = sin(glm::radians(this->pitch - 90.f));
		direction.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch - 90.f));
		this->eye += position.y * direction;
		// Pitch equal 0
		direction.x = cos(glm::radians(this->yaw - 90.f));
		direction.y = 0.0f;
		direction.z = sin(glm::radians(this->yaw - 90.f));
		this->eye += position.x * direction;
		this->updateCenter();
	}

	void Camera::setPosition(Position position)
	{
		this->eye = position;
		this->updateCenter();
	}

	void Camera::setTarget(Position position)
	{
		this->center = position;
		updateAngles();
	}

	Position Camera::getPosition() const
	{
		return this->eye;
	}

	Matrix Camera::getViewMatrix()
	{
		Matrix view = glm::lookAt(this->eye, this->center, this->up);
		return view;
	}

	const Position& Camera::getViewPosition() const
	{
		return this->eye;
	}

	void Camera::rotate(Angle yaw, Angle pitch)
	{
		this->yaw += yaw;
		this->pitch += pitch;

		if (this->pitch > 89.0f)
			this->pitch = 89.0f;
		if (this->pitch < -89.0f)
			this->pitch = -89.0f;

		this->updateCenter();
	}

	void Camera::updateCenter()
	{
		Direction direction;
		direction.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
		direction.y = sin(glm::radians(this->pitch));
		direction.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
		center = eye + direction;
	}

	void Camera::updateAngles()
	{
		Direction direction = glm::normalize(center - eye);
		this->pitch = glm::degrees(asin(direction.y));
		this->yaw = glm::degrees(acos(direction.x / cos(glm::radians(this->pitch))));
	}
}