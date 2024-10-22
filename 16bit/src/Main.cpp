#include <pch.h>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

#include "CPU.h"

#include "UI/RenderControls.h"


	int main() {
		GLFWwindow* window;

		if (!glfwInit()) {
			std::cout << "[-] There was an error while initializing GLFW\n";
			return -1;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		int windowWidth = 700;
		int windowHeight = 700;

		window = glfwCreateWindow(windowWidth, windowHeight, "16 Bit CPU", NULL, NULL);
		if (!window) {
			std::cout << "[-] There was an error while creating the window\n";
			glfwTerminate();
			return -1;
		}

		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "[-] There was an error while initializing GLAD\n";
			return -1;
		}
		
		{
			float vertecies[] = {
					// Positions       /  Texture coordiantes//
				 -0.5f, -0.5f,                -0.5f, -0.5f,
				  0.5f, -0.0f,                 0.5f, -0.0f,
				  0.5f,  0.0f,                 0.5f,  0.0f,
				 -0.5f,  0.0f,                -0.5f,  0.0f,
				};


			unsigned int indicies[] = {
				0, 1, 2,
				0, 2, 3
			};

			GLCall(glEnable(GL_DEPTH_TEST));

			GLCall(glEnable(GL_BLEND));
			GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


			VertexArray va;
			VertexBuffer vb(vertecies, sizeof(vertecies));

			VertexBufferLayout layout;
			layout.Push<float>(2); // Positions
			layout.Push<float>(2); // TexCoords
			va.AddBuffer(vb, layout);

			IndexBuffer ib(indicies, sizeof(indicies)/sizeof(unsigned int));

			Shader shader("res/shaders/basic.vert", "res/shaders/basic.frag");
			shader.Bind();

			Renderer renderer;

			bool VSync = false;

			int width, height = 0;

			va.Unbind();
			vb.Unbind();
			ib.Unbind();
			shader.Unbind();

			CPU cpu;

			ImGui::CreateContext();

			ImGui_ImplGlfw_InitForOpenGL(window, true);
			ImGui_ImplOpenGL3_Init();
			ImGui::StyleColorsDark();

			ImGuiIO& io = ImGui::GetIO();

			while (!glfwWindowShouldClose(window)) {
				
				renderer.ClearColor(1.0f, 1.0f, 1.0f, 1.0f);
				GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

				cpu.Step(1);

				GLCall(glfwSwapInterval((int)VSync));

				glfwGetFramebufferSize(window, &width, &height);
				GLCall(glViewport(0, 0, width, height));

				float ratio = (float)width / height;

				shader.Bind();

				shader.SetUniform1i("u_Texture", 0);

				glm::mat4 Model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
				glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
				glm::mat4 Projection = glm::ortho(0.0f, (float)windowWidth, 0.0f, (float)windowHeight, 0.0f, 1.0f);

				renderer.Draw(va, ib, shader);				

				ImGui_ImplOpenGL3_NewFrame();
				ImGui_ImplGlfw_NewFrame();
				ImGui::NewFrame();

				ImGui::Begin("Panel");

				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
				
				ImGui::Text("Enable V-Sync");
				ImGui::SameLine();
				ImGui::Checkbox("##vsync", &VSync);

				ImGui::End();

				ImGui::Render();
				ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

				glfwSwapBuffers(window);
				glfwPollEvents();
			}
		}

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
		glfwTerminate();
		return 0;
	}