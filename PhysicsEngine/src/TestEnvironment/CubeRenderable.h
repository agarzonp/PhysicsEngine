#ifndef CUBE_RENDERABLE_H
#define CUBE_RENDERABLE_H

class CubeRenderable
{
	bool isVisible { false };
	glm::vec4 color { 1.0f, 1.0f, 1.0f, 1.0f };

public:
	CubeRenderable() = default;

	CubeRenderable(const glm::vec4& color_) 
		: color(color_) 
	{
	}

	const glm::vec4& Color() const { return color; }

	void SetVisible(bool visible) { isVisible = visible; }
	bool IsVisible() { return isVisible; }
};

#endif // !CUBE_RENDERABLE_H

