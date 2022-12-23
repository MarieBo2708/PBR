// Local includes
#include "Material.h"
#include "Shader.h"
#include "Texture.h"
#include "Context.h"
// GLM includes
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
// OPENGL includes
#include <GL/glew.h>
#include <GL/glut.h>

Material::~Material() {
	if (m_program != 0) {
		glDeleteProgram(m_program);
	}
}

void Material::init() {
	// TODO : Change shader by your
	m_program = load_shaders("shaders/unlit/vertex.glsl", "shaders/unlit/fragment.glsl");
	check();
	// TODO : set initial parameters
	m_color = {1.0, 1.0, 1.0, 1.0};
	//albedo_texture = loadTexture2DFromFilePath("data/albedo.png");
	//normal_texture = loadTexture2DFromFilePath("data/normal.png");
	//metallic_texture = loadTexture2DFromFilePath("data/metallic.png");
	//rough_texture = loadTexture2DFromFilePath("data/roughness.png");
	//ao_texture = loadTexture2DFromFilePath("data/ao.png");
	//positions_lumieres = glm::vec3(150.0, 300.0, 150.0);
	//couleurs_lumieres = glm::vec3(150.0, 150.0, 150.0);
	//position_camera = {150., 150., 150.};
	//position_vu = {0., 0., 0.};

	albedo = {0.5, 0., 0.};
	ao = 1.;
	metallic = 0.6;
	roughness = 0.4;
	camera_pos = Context::camera.position;
	lumiere_pos = {-10., 10., 10.};
	lumiere_coul = {300.0, 300.0, 300.0};

}

void Material::clear() {
	/*glDeleteTextures(1, &albedo_texture);
	glDeleteTextures(1, &normal_texture);
	glDeleteTextures(1, &metallic_texture);
	glDeleteTextures(1, &rough_texture);
	glDeleteTextures(1, &ao_texture);*/
}

void Material::bind() {
	check();
	glUseProgram(m_program);
	internalBind();
}

void Material::internalBind() {
	// bind parameters
	/*GLint color = getUniform("color");
	glUniform4fv(color, 1, glm::value_ptr(m_color));
	if (albedo_texture != -1) {
		glActiveTexture(GL_TEXTURE0+0);
		glUniform1i(getUniform("albedoMap"), GL_TEXTURE0+0);
		glBindTexture(GL_TEXTURE_2D, albedo_texture);
	}
	if(normal_texture != -1){
		glActiveTexture(GL_TEXTURE0+1);
		glUniform1i(getUniform("normalMap"), GL_TEXTURE0+1);
		glBindTexture(GL_TEXTURE_2D, normal_texture);
	}
	if(metallic_texture != -1){
		glActiveTexture(GL_TEXTURE0+2);
		glUniform1i(getUniform("metallicMap"), GL_TEXTURE0+2);
		glBindTexture(GL_TEXTURE_2D, metallic_texture);
	}
	if(rough_texture != -1){
		glActiveTexture(GL_TEXTURE0+3);
		glUniform1i(getUniform("roughnessMap"), GL_TEXTURE0+3);
		glBindTexture(GL_TEXTURE_2D, rough_texture);
	}
	if(ao_texture != -1){
		glActiveTexture(GL_TEXTURE0+4);
		glUniform1i(getUniform("aoMap"), GL_TEXTURE0+4);
		glBindTexture(GL_TEXTURE_2D, ao_texture);
	}

	GLuint l_p = getUniform("position_lumiere");
	GLuint c_p = getUniform("couleur_lumiere");
	glUniform3f(l_p, positions_lumieres[0], positions_lumieres[1], positions_lumieres[2]);
	glUniform3f(c_p, couleurs_lumieres[0], couleurs_lumieres[1], couleurs_lumieres[2]);
	GLuint cam_pos = getUniform("camera_position");
	glUniform3f(cam_pos, position_camera[0], position_camera[1], position_camera[2]);*/

	// TODO : Add your custom parameters here

	GLuint albedo_coeff = getUniform("albedo");
	glUniform3f(albedo_coeff, albedo[0], albedo[1], albedo[2]);

	GLuint ao_coeff = getUniform("ao");
	glUniform1f(ao_coeff, ao);

	GLuint metallic_coeff = getUniform("metallic");
	glUniform1f(metallic_coeff, metallic);

	GLuint roughness_coeff = getUniform("roughness");
	glUniform1f(roughness_coeff, roughness);

	GLuint cam = getUniform("position_camera");
	glUniform3f(cam, camera_pos[0], camera_pos[1], camera_pos[2]);

	GLuint lum_pos = getUniform("position_lumiere");
	glUniform3f(lum_pos, lumiere_pos[0], lumiere_pos[1], lumiere_pos[2]);

	GLuint lum_coul = getUniform("couleur_lumiere");
	glUniform3f(lum_coul, lumiere_coul[0], lumiere_coul[1], lumiere_coul[2]);

	
}

void Material::setMatrices(glm::mat4& projectionMatrix, glm::mat4& viewMatrix, glm::mat4& modelMatrix)
{
	check();
	glUniformMatrix4fv(getUniform("projection"), 1, false, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(getUniform("view"), 1, false, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(getUniform("model"), 1, false, glm::value_ptr(modelMatrix));
}

GLint Material::getAttribute(const std::string& in_attributeName) {
	check();
	return glGetAttribLocation(m_program, in_attributeName.c_str());
}

GLint Material::getUniform(const std::string& in_uniformName) {
	check();
	return glGetUniformLocation(m_program, in_uniformName.c_str());
}
