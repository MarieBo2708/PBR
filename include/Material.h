#ifndef MATERIAL_H_DEFINED
#define MATERIAL_H_DEFINED
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <stdexcept>

struct Material {
	// Shader program
	GLuint m_program;

	// Material parameters
	glm::vec4 m_color;
	/*GLuint albedo_texture;
	GLuint normal_texture;
	GLuint metallic_texture;
	GLuint rough_texture;
	GLuint ao_texture;
	glm::vec3 positions_lumieres;
	glm::vec3 couleurs_lumieres;
	glm::vec3 position_camera;
	glm::vec3 position_vu;*/

	glm::vec3 albedo, camera_pos, lumiere_pos, lumiere_coul;
	float ao, metallic, roughness;

	inline void check() {
		if (m_program == 0) {
			throw std::runtime_error("Shader program not initialized");
		}
	}

	Material(): m_program(0) {

	}

	virtual ~Material();

	virtual void init();

	virtual void clear();

	void bind();

	virtual void internalBind();

	void setMatrices(glm::mat4& projectionMatrix, glm::mat4& viewMatrix, glm::mat4& modelMatrix);

	GLint getAttribute(const std::string& in_attributeName);

	GLint getUniform(const std::string& in_uniformName);
};

#endif
