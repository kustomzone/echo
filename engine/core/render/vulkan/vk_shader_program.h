#pragma once

#include "engine/core/render/interface/shaderprogram.h"
#include "vk_render_base.h"
#include "vk_gpu_buffer.h"

namespace Echo
{
	class VKShaderProgram : public ShaderProgram
	{
        typedef VkPipelineShaderStageCreateInfo VkPipelineSSCI;

    public:
		virtual ~VKShaderProgram();

        // bind
        virtual void bindUniforms() override;
        virtual void bindRenderable(Renderable* renderable) override;

    public:
        // parse uniforms
        void parseUniforms();

    public:
        // get shader stage create info
        const array<VkPipelineSSCI, 2>& getVkShaderStageCreateInfo() { return m_vkShaderStagesCreateInfo; }

	private:
		// create shader library
		virtual bool createShaderProgram(const String& vsContent, const String& psContent) override;

        // create uniform buffer
        void createVkUniformBuffer();

        // create descriptor and pipeline layouts
        void createVkDescriptorAndPipelineLayouts();

        // alloc uniform bytes
        void allocUniformBytes();

	private:
		bool			        m_isValid = false;
		VkShaderModule	        m_vkVertexShader;
		VkShaderModule	        m_vkFragmentShader;
        array<VkPipelineSSCI, 2>m_vkShaderStagesCreateInfo;
        vector<Byte>::type      m_vertexShaderUniformBytes;
        vector<Byte>::type      m_fragmentShaderUniformBytes;
        VKBuffer*               m_vkVertexShaderUniformBuffer = nullptr;
        VKBuffer*               m_vkFragmentShaderUniformBuffer = nullptr;
        VkDescriptorSetLayout   m_vkDescriptorSetLayout;
        VkPipelineLayout        m_vkPipelineLayout;
	};
}
